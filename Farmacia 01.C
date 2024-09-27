#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noGenerico
{ // ESTRUTURA DE GENERICOS
    int generico;
    struct noGenerico *prox;
} noGenerico;

typedef struct noRemedio
{ // ESTRUTURA DE REMEDIOS
    char remedio[30];
    struct noRemedio *prox;
    struct noGenerico *proxGenerico;
} noRemedio;

int vazia(noRemedio *LISTA)
{
    return LISTA == NULL || LISTA->prox == NULL;
}

void inserirRemedio(noRemedio *LISTA)
{
    noRemedio *novo = (noRemedio *)malloc(sizeof(noRemedio));
    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    printf("\nNome do Remedio: ");
    scanf("%s", novo->remedio);
    novo->prox = NULL;
    novo->proxGenerico = NULL; // Inicializando o PRATELEIRA como NULL

    if (vazia(LISTA))
    {
        LISTA->prox = novo;
    }
    else
    {
        noRemedio *temp = LISTA->prox;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void imprimir(noRemedio *LISTA)
{
    noRemedio *temp = LISTA->prox;
    int contador = 0;
    while (temp != NULL)
    {
        printf("Posicao %d: %s\n----------\n", contador, temp->remedio);
        temp = temp->prox;
        contador++;
    }
}

void removerRemedio(noRemedio *LISTA)
{
    if (vazia(LISTA))
    {
        printf("Lista vazia! Nao ha o que remover.\n");
        return;
    }

    int posicao = 0;
    int cont = 0;
    printf("Qual posicao do remedio que voce quer remover?: ");
    scanf("%d", &posicao);

    noRemedio *ant = LISTA;
    noRemedio *suc = LISTA->prox;

    while (cont < posicao && suc != NULL)
    {
        ant = suc;
        suc = suc->prox;
        cont++;
    }

    if (suc == NULL)
    {
        printf("Posicao %d nao encontrada.\n", posicao);
        return;
    }

    ant->prox = suc->prox;
    free(suc);
    printf("\n==========REMOVIDO_POSICAO: %d============\n", posicao);
}

void iniciaLista(noRemedio *LISTA)
{
    LISTA->prox = NULL;
}

void iniciaPrateleira(noGenerico *PRATELEIRA)
{
    PRATELEIRA->prox = NULL;
}

void liberarLista(noRemedio *LISTA)
{
    noRemedio *atual = LISTA->prox;
    noRemedio *prox;

    while (atual != NULL)
    {
        prox = atual->prox;

        // Libera todos os genericos da Prateleira
        noGenerico *genericoAtual = atual->proxGenerico;
        while (genericoAtual != NULL)
        {
            noGenerico *moedaProx = genericoAtual->prox;
            free(genericoAtual);
            genericoAtual = moedaProx;
        }

        free(atual);
        atual = prox;
    }

    free(LISTA); // Libera a estrutura inicial
}

void pushGenerico(noGenerico **PRATELEIRA)
{
    char nomeGenerico;
    printf("\nQual o nome do generico a ser inserido?: ");
    scanf("%s", &nomeGenerico);
    noGenerico *novo = (noGenerico *)malloc(sizeof(noGenerico));
    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novo->generico = nomeGenerico;
    novo->prox = *PRATELEIRA;
    *PRATELEIRA = novo;

    printf("\nGenerico adicionado: %d\n", novo->generico);
}

void imprimirGenerico(noGenerico *PRATELEIRA)
{
    noGenerico *temp = PRATELEIRA;

    while (temp != NULL)
    {
        printf("\n%d", temp->generico);
        temp = temp->prox;
    }
    printf("\n=============FIM_IMPRESSAO==============");
}

void removerGenerico(noGenerico **PRATELEIRA)
{
    if (*PRATELEIRA == NULL)
    {
        printf("Prateleira vazia, nao ha genericos para remover.\n");
        return;
    }

    noGenerico *temp = *PRATELEIRA;
    *PRATELEIRA = temp->prox;
    free(temp);
    printf("generico removido com sucesso.\n");
}

void acessarPrateleira(noRemedio *LISTA)
{
    int posicaoPrateleira;
    int contador = 0;
    noRemedio *AUX = LISTA->prox;

    printf("\n\nQual PRATELEIRA deseja acessar?:\n---------------------------\n");
    imprimir(LISTA);
    printf("---------------------------\nPosicao?: ");
    scanf("%d", &posicaoPrateleira);

    while (contador < posicaoPrateleira && AUX != NULL)
    {
        AUX = AUX->prox;
        contador++;
    }

    if (AUX == NULL)
    {
        printf("Posicao nao encontrada.\n");
        return;
    }

    noGenerico **PRATELEIRA = &AUX->proxGenerico; // Usa o Prateleira de genericos

    if (*PRATELEIRA == NULL)
    {
        *PRATELEIRA = NULL;
    }

    printf("\n====ACESSANDO_COFRE: %s====", AUX->remedio);

    do
    {
        printf("\n\n====MENU_DE_COFRE: %s====\n1. Adicionar generico \n2. Retirar generico \n3. Apresentar todos os genericos \n0. Voltar.\nOpicao?: ", AUX->remedio);
        scanf("%d", &posicaoPrateleira);

        switch (posicaoPrateleira)
        {
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
        }

    } while (posicaoPrateleira != 0);
}

int main() // MENU PRINCIPAL
{
    int opcao;

    noRemedio *LISTA = (noRemedio *)malloc(sizeof(noRemedio));
    if (LISTA == NULL)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    iniciaLista(LISTA);

    do
    {
        printf("\n\n===MENU_DE_OPCOES===\n1. Adicionar remedio \n2. Retirar remedio \n3. Apresentar todos os remedios \n4. Acessar prateleira de remedios...: \n0. Sair.\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
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
