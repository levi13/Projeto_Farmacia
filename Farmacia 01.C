#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noGenerico {
    char generico[30];
    float valor; // Mudança de double para float
    char fabricante[30];
    struct noGenerico *prox;
    struct noGenerico *prev;
} noGenerico;

typedef struct noRemedio {
    char remedio[30];
    float valor; // Mudança de double para float
    char fabricante[30];
    struct noRemedio *prox;
    noGenerico *proxGenerico;
} noRemedio;

int vazia(noRemedio *LISTA) {
    return LISTA == NULL || LISTA->prox == NULL;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
}

void inserirRemedio(noRemedio *LISTA) {
    noRemedio *novo = (noRemedio *)malloc(sizeof(noRemedio));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    printf("\nNome do Remedio: ");
    limparBuffer(); // Limpa o buffer antes da leitura
    fgets(novo->remedio, 30, stdin);
    novo->remedio[strcspn(novo->remedio, "\n")] = '\0'; // Remove o '\n'

    printf("Valor do Remedio: ");
    scanf("%f", &novo->valor); // Mudança para float

    printf("Fabricante do Remedio: ");
    limparBuffer(); // Limpa o buffer antes de ler o fabricante
    fgets(novo->fabricante, 30, stdin);
    novo->fabricante[strcspn(novo->fabricante, "\n")] = '\0'; // Remove o '\n'

    novo->prox = NULL;
    novo->proxGenerico = NULL;

    if (vazia(LISTA)) {
        LISTA->prox = novo;
    } else {
        noRemedio *temp = LISTA->prox;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void pushGenerico(noGenerico **PRATELEIRA) {
    char nomeGenerico[30];
    float valorGenerico;
    char fabricanteGenerico[30];

    printf("\nQual o nome do generico a ser inserido?: ");
    limparBuffer(); // Limpa o buffer antes da leitura
    fgets(nomeGenerico, 30, stdin);
    nomeGenerico[strcspn(nomeGenerico, "\n")] = '\0'; // Remove o '\n'

    printf("Valor do generico: ");
    scanf("%f", &valorGenerico); // Mudança para float

    printf("Fabricante do generico: ");
    limparBuffer(); // Limpa o buffer antes de ler o fabricante
    fgets(fabricanteGenerico, 30, stdin);
    fabricanteGenerico[strcspn(fabricanteGenerico, "\n")] = '\0'; // Remove o '\n'

    noGenerico *novo = (noGenerico *)malloc(sizeof(noGenerico));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    strcpy(novo->generico, nomeGenerico);
    novo->valor = valorGenerico;
    strcpy(novo->fabricante, fabricanteGenerico);
    novo->prox = *PRATELEIRA;
    novo->prev = NULL;

    if (*PRATELEIRA != NULL) {
        (*PRATELEIRA)->prev = novo;
    }
    *PRATELEIRA = novo;

    printf("\nGenerico adicionado: %s\n", novo->generico);
}

int main() {
    noRemedio *LISTA = (noRemedio *)malloc(sizeof(noRemedio));
    LISTA->prox = NULL;

    int opcao;
    do {
        printf("\nMENU\n");
        printf("1. Inserir remedio\n");
        printf("2. Listar remedios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirRemedio(LISTA);
                break;
            case 2:
                // Adicionar função de listar remédios aqui
                break;
        }
    } while (opcao != 0);

    // Liberar memória ao final
    return 0;
}
