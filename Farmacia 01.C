#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct noGenerico {
    char generico[30]; 
    struct noGenerico *prox;
    struct noGenerico *prev; // Ponteiro para o nó anterior
} noGenerico;

typedef struct noRemedio {
    char remedio[30];
    struct noRemedio *prox;
    noGenerico *proxGenerico; 
} noRemedio;

int vazia(noRemedio *LISTA) {
    return LISTA == NULL || LISTA->prox == NULL;
}

void inserirRemedio(noRemedio *LISTA) {
    noRemedio *novo = (noRemedio *)malloc(sizeof(noRemedio));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    printf("\nNome do Remedio: ");
    scanf("%29s", novo->remedio); // Limite para evitar overflow
    novo->prox = NULL;
    novo->proxGenerico = NULL; // Inicializando o PRATELEIRA como NULL

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

void imprimir(noRemedio *LISTA) {
    noRemedio *temp = LISTA->prox;
    int contador = 0;
    while (temp != NULL) {
        printf("Posicao %d: %s\n----------\n", contador, temp->remedio);
        temp = temp->prox;
        contador++;
    }
}

void removerRemedio(noRemedio *LISTA) {
    if (vazia(LISTA)) {
        printf("Lista vazia! Nao ha o que remover.\n");
        return;
    }

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

    ant->prox = suc->prox;
    free(suc);
    printf("\n==========REMOVIDO_POSICAO: %d============\n", posicao);
}

void iniciaLista(noRemedio *LISTA) {
    LISTA->prox = NULL;
}

void liberarLista(noRemedio *LISTA) {
    noRemedio *atual = LISTA->prox;
    while (atual != NULL) {
        noRemedio *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(LISTA); // Libera a estrutura inicial
}

void pushGenerico(noGenerico **PRATELEIRA) {
    char nomeGenerico[30];
    printf("\nQual o nome do generico a ser inserido?: ");
    scanf("%29s", nomeGenerico);
    
    noGenerico *novo = (noGenerico *)malloc(sizeof(noGenerico));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    
    strcpy(novo->generico, nomeGenerico);
    novo->prox = *PRATELEIRA;
    novo->prev = NULL; // Inicializa o anterior como NULL

    if (*PRATELEIRA != NULL) {
        (*PRATELEIRA)->prev = novo; // Conecta o anterior
    }
    *PRATELEIRA = novo;

    printf("\nGenerico adicionado: %s\n", novo->generico);
}

void imprimirGenerico(noGenerico *PRATELEIRA) {
    noGenerico *temp = PRATELEIRA;
    while (temp != NULL) {
        printf("\n%s", temp->generico);
        temp = temp->prox;
    }
    printf("\n=============FIM_IMPRESSAO==============");
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
        printf("Posicao %d: %s\n", contador, temp->generico);
        temp = temp->prox;
        contador++;
    }
    printf("===========================\n");
}

void removerGenerico(noGenerico **PRATELEIRA) {
    if (*PRATELEIRA == NULL) {
        printf("Prateleira vazia, nao ha genericos para remover.\n");
        return;
    }

    listarGenericos(*PRATELEIRA); // Exibe as posições dos genéricos

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
        atual->prev->prox = atual->prox; // Conecta o anterior ao próximo
    } else {
        *PRATELEIRA = atual->prox; // Se for o primeiro, atualiza o início
    }

    if (atual->prox != NULL) {
        atual->prox->prev = atual->prev; // Conecta o próximo ao anterior
    }

    free(atual);
    printf("Generico removido com sucesso.\n");
}




void acessarPrateleira(noRemedio *LISTA) {
    int posicaoPrateleira;
    printf("\n\nQual PRATELEIRA deseja acessar?:\n---------------------------\n");
    imprimir(LISTA);
    printf("---------------------------\nPosicao?: ");
    scanf("%d", &posicaoPrateleira);

    noRemedio *AUX = LISTA->prox;
    for (int contador = 0; contador < posicaoPrateleira && AUX != NULL; contador++) {
        AUX = AUX->prox;
    }

    if (AUX == NULL) {
        printf("Posicao nao encontrada.\n");
        return;
    }

    noGenerico **PRATELEIRA = &AUX->proxGenerico; // Usa o Prateleira de genericos

    printf("\n====ACESSANDO_COFRE: %s====", AUX->remedio);
    listarGenericos(*PRATELEIRA); // Adiciona chamada para listar genéricos

    int opcao;
    do {
        printf("\n\n====MENU_DE_COFRE: %s====\n1. Adicionar generico \n2. Retirar generico \n3. Apresentar todos os genericos \n4. Remover generico \n0. Voltar.\nOpicao?: ", AUX->remedio);
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\n==========INSERINDO_GENERICOS_PRATELEIRA: %s==========\n", AUX->remedio);
            pushGenerico(PRATELEIRA);
            break;
        case 2:
            printf("\n==========REMOVENDO_GENERICOS_PRATELEIRA: %s==========\n", AUX->remedio);
            removerGenerico(PRATELEIRA);
            break;
        case 3:
            printf("\n==========IMPRIMINDO_GENERICOS_PRATELEIRA: %s==========\n", AUX->remedio);
            imprimirGenerico(*PRATELEIRA);
            break;
        case 4:
            printf("\n==========REMOVENDO_GENERICOS_PRATELEIRA: %s==========\n", AUX->remedio);
            removerGenerico(PRATELEIRA);
            break;
        }
    } while (opcao != 0);
}






int main() {
    noRemedio *LISTA = (noRemedio *)malloc(sizeof(noRemedio));
    if (LISTA == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    iniciaLista(LISTA);

    int opcao;
    do {
        printf("\n\n===MENU_DE_OPCOES===\n1. Adicionar remedio \n2. Retirar remedio \n3. Apresentar todos os remedios \n4. Acessar prateleira de remedios...: \n0. Sair.\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            inserirRemedio(LISTA);
            break;
        case 2:
            removerRemedio(LISTA);
            break;
        case 3:
            printf("\n==========IMPRIMINDO_LISTA==========\n");
            imprimir(LISTA);
            break;
        case 4:
            acessarPrateleira(LISTA);
            break;
        }
    } while (opcao != 0);

    liberarLista(LISTA);
    LISTA = NULL; 
    printf("Fim do programa, obrigado.");
    return 0;
}
