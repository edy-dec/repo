#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Masina
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct Masina Masina;

struct Node
{
	Masina data;
	struct Node* stanga;
	struct Node* dreapta;
};

typedef struct Node Node;


Masina citireMasinaDinFisier(FILE* file)
{
	char buffer[100];
	char* sep = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);

	return m1;
}


void afisareMasina(Masina masina)
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Node* creareNod(Masina m)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = m;
	newNode->stanga = NULL;
	newNode->dreapta = NULL;
	return newNode;

}

Node* inserare(Node* root, Masina m)
{
	if (root == NULL)return creareNod(m);

	Node* queue[100];
	int front = 0, rear = 0;
	queue[rear++] = root;

	while (front < rear)
	{
		Node* temp = queue[front++];

		if (temp->stanga == NULL)
		{
			temp->stanga = creareNod(m);
			break;
		}
		else
		{
			queue[rear++] = temp->stanga;
		}

		if (temp->dreapta == NULL)
		{
			temp->dreapta = creareNod(m);
			break;
		}
		else
		{
			queue[rear++] = temp->dreapta;
		}
	}
	return root;
}



void inOrder(Node* nod)
{
	if (nod == NULL) return;
	inOrder(nod->stanga);
	afisareMasina(nod->data);
	inOrder(nod->dreapta);
}


int cautareDupaPret(Node* root, float pretCautat)
{
	if (root == NULL) return 0;

	if (root->data.pret == pretCautat)
		return 1;

	int rezultat_stanga = cautareDupaPret(root->stanga, pretCautat);
	int rezultat_dreapta = cautareDupaPret(root->dreapta, pretCautat);

	return rezultat_stanga || rezultat_dreapta;

}

int main() {
	FILE* f = fopen("masini.txt", "r");
	if (!f) {
		perror("Fisierul nu poate fi deschis");
		return -1;
	}

	Node* root = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		if (m.id != -1) {
			root = inserare(root, m);
		}
	}

	fclose(f);

	printf("Traversare inordine:\n");
	inOrder(root);

	//9, 3, 2700, Passat, Ionescu, I

	return 0;
}
