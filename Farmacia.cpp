#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Remedio {
    char nome[50];
    char fabricante[50];
    float valor;
    struct Remedio* proximo;
} Remedio;

Remedio* criarRemedio(char nome[], char fabricante[], float valor) {
    Remedio* novo = (Remedio*)malloc(sizeof(Remedio));
    
    strcpy(novo->nome, nome);
    strcpy(novo->fabricante, fabricante);
    novo->valor = valor;
    novo->proximo = NULL;

    return novo;
}

Remedio* inserirInicio(Remedio* head, char nome[], char fabricante[], float valor) {
    Remedio* novo = criarRemedio(nome, fabricante, valor);
    novo->proximo = head;
    return novo;
}

void exibirLista(Remedio* head) {
    Remedio* atual = head;
    
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Fabricante: %s\n", atual->fabricante);
        printf("Valor: R$ %.2f\n\n", atual->valor);
        atual = atual->proximo;
    }
}

int main() {
    Remedio* lista = NULL;
    
    lista = inserirInicio(lista, "Paracetamol", "Fabricante A", 10.50);
    lista = inserirInicio(lista, "Ibuprofeno", "Fabricante B", 15.75);
    lista = inserirInicio(lista, "Dipirona", "Fabricante C", 8.90);

    printf("Lista de Medicamentos:\n\n");
    exibirLista(lista);

    return 0;
}
