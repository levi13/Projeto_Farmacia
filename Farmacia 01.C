#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noGenerico {
    char generico[30];
    float valor;
    char fabricante[30];
    struct noGenerico *prox;
    struct noGenerico *prev;
} noGenerico;

typedef struct noRemedio {
    char remedio[30];
    float valor;
    char fabricante[30];
    struct noRemedio *prox;
    noGenerico *proxGenerico;
} noRemedio;

// Funções auxiliares
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int vazia(noRemedio *LISTA) {
    return LISTA == NULL || LISTA->prox == NULL;
}

void iniciaLista(noRemedio *LISTA) {
    LISTA->prox = NULL;
}

// Funções de inserção
void inserirRemedio(noRemedio *LISTA) {
    noRemedio *novo = (noRemedio *)malloc(sizeof(noRemedio));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    printf("\nNome do Remedio: ");
    limparBuffer();
    fgets(novo->remedio, 30, stdin);
    novo->remedio[strcspn(novo->remedio, "\n")] = '\0';

    printf("Valor do Remedio: ");
    scanf("%f", &novo->valor);

    printf("Fabricante do Remedio: ");
    limparBuffer();
    fgets(novo->fabricante, 30, stdin);
    novo->fabricante[strcspn(novo->fabricante, "\n")] = '\0';

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
    limparBuffer();
    fgets(nomeGenerico, 30, stdin);
    nomeGenerico[strcspn(nomeGenerico, "\n")] = '\0';

    printf("Valor do generico: ");
    scanf("%f", &valorGenerico);

    printf("Fabricante do generico: ");
    limparBuffer();
    fgets(fabricanteGenerico, 30, stdin);
    fabricanteGenerico[strcspn(fabricanteGenerico, "\n")] = '\0';

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

// Funções de impressão
void imprimir(noRemedio *LISTA) {
    noRemedio *temp = LISTA->prox;
    int contador = 0;
    while (temp != NULL) {
        printf("Posicao %d: %s\nValor: %.2f\nFabricante: %s\n----------\n", 
                contador, temp->remedio, temp->valor, temp->fabricante);
        temp = temp->prox;
        contador++;
    }
}

void listarGenericos(noGenerico *PRATELEIRA) {
    if (PRATELEIRA == NULL) {
        printf("Nenhum generico cadastrado.\n");
        return;
    }

    noGenerico *temp = PRATELEIRA;
    int contador = 0;
    printf("Lista de Genericos:\n");
    while (temp != NULL) {
        printf("Posicao %d: %s\nValor: %.2f\nFabricante: %s\n", contador, temp->generico, temp->valor, temp->fabricante);
        temp = temp->prox;
        contador++;
    }
    printf("FIM_LISTA\n");
}

// Funções de remoção
void liberarGenericos(noGenerico *PRATELEIRA) {
    noGenerico *atual = PRATELEIRA;
    while (atual != NULL) {
        noGenerico *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

void liberarLista(noRemedio *LISTA) {
    noRemedio *atual = LISTA->prox;
    while (atual != NULL) {
        liberarGenericos(atual->proxGenerico);
        noRemedio *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(LISTA);
}

void removerGenerico(noGenerico **PRATELEIRA) {
    if (*PRATELEIRA == NULL) {
        printf("Prateleira vazia, nao ha genericos para remover.\n");
        return;
    }

    listarGenericos(*PRATELEIRA);

    int posicao = 0;
    printf("Qual posicao do generico que voce quer remover?: ");
    scanf("%d", &posicao);

    noGenerico *atual = *PRATELEIRA;
    int cont = 0;

    while (cont < posicao && atual != NULL) {
        atual = atual->prox;
        cont++;
    }

    if (atual == NULL) {
        printf("Posicao %d nao encontrada.\n", posicao);
        return;
    }

    if (atual->prev != NULL) {
        atual->prev->prox = atual->prox;
    } else {
        *PRATELEIRA = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->prev = atual->prev;
    }

    free(atual);
    printf("Generico removido da posicao %d.\n", posicao);
}

void removerRemedio(noRemedio *LISTA) {
    if (vazia(LISTA)) {
        printf("Lista vazia! Nao ha o que remover.\n");
        return;
    }

    imprimir(LISTA);

    int posicao = 0;
    printf("Qual posicao do remedio que voce quer remover?: ");
    scanf("%d", &posicao);

    noRemedio *ant = LISTA;
    noRemedio *suc = LISTA->prox;
    int cont = 0;

    while (cont < posicao && suc != NULL) {
        ant = suc;
        suc = suc->prox;
        cont++;
    }

    if (suc == NULL) {
        printf("Posicao %d nao encontrada.\n", posicao);
        return;
    }

    liberarGenericos(suc->proxGenerico);
    ant->prox = suc->prox;
    free(suc);
    printf("\nREMOVIDO_POSICAO: %d\n", posicao);
}

void acessarPrateleira(noRemedio *LISTA) {
    if (vazia(LISTA)) {
        printf("Lista de remedios vazia.\n");
        return;
    }

    noRemedio *AUX = LISTA->prox;
    int opcao = 0;

    do {
        printf("\nACESSANDO_PRATELEIRA\n");
        printf("Escolha um remedio:\n");
        int contador = 0;
        while (AUX != NULL) {
            printf("%d. %s\n", contador, AUX->remedio);
            AUX = AUX->prox;
            contador++;
        }
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao < 0 || contador <= opcao) {
            printf("Opcao invalida.\n");
            continue;
        }

        AUX = LISTA->prox;
        contador = 0;

        while (AUX != NULL && contador != opcao) {
            AUX = AUX->prox;
            contador++;
        }

        if (AUX != NULL) {
            noGenerico *PRATELEIRA = AUX->proxGenerico;
            do {
                printf("\nACESSANDO_GENERICOS: %s\n", AUX->remedio);
                printf("1. Inserir generico\n");
                printf("2. Remover generico\n");
                printf("3. Listar genericos\n");
                printf("0. Voltar\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        pushGenerico(&PRATELEIRA);
                        break;
                    case 2:
                        removerGenerico(&PRATELEIRA);
                        break;
                    case 3:
                        listarGenericos(PRATELEIRA);
                        break;
                }
            } while (opcao != 0);

            AUX->proxGenerico = PRATELEIRA;
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    noRemedio *LISTA = (noRemedio *)malloc(sizeof(noRemedio));
    iniciaLista(LISTA);

    int opcao;
    do {
        printf("\nMENU\n");
        printf("1. Inserir remedio\n");
        printf("2. Remover remedio\n");
        printf("3. Listar remedios\n");
        printf("4. Acessar prateleira de genericos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirRemedio(LISTA);
                break;
            case 2:
                removerRemedio(LISTA);
                break;
            case 3:
                imprimir(LISTA);
                break;
            case 4:
                acessarPrateleira(LISTA);
                break;
        }
    } while (opcao != 0);

    liberarLista(LISTA);

    return 0;
}
