#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void exibirMenu() {
    printf("===== MOCHILA - CODIGO DA ILHA =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome (busca binaria)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;
}

void removerItem() {
    char nome[50];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];
            numItens--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

void insertionSort(CriterioOrdenacao criterio) {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool cond = false;
            if (criterio == NOME)
                cond = strcmp(chave.nome, mochila[j].nome) < 0;
            else if (criterio == TIPO)
                cond = strcmp(chave.tipo, mochila[j].tipo) < 0;
            else if (criterio == PRIORIDADE)
                cond = chave.prioridade > mochila[j].prioridade; // maior prioridade primeiro

            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    if (criterio == NOME) ordenadaPorNome = true;
    else ordenadaPorNome = false;

    printf("Itens ordenados!\n");
}

void menuDeOrdenacao() {
    int opc;
    printf("Ordenar por:\n1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1: insertionSort(NOME); break;
        case 2: insertionSort(TIPO); break;
        case 3: insertionSort(PRIORIDADE); break;
        default: printf("Opção inválida!\n");
    }
}

void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila deve estar ordenada por nome!\n");
        return;
    }

    char nome[50];
    printf("Nome para buscar: ");
    scanf(" %[^\n]", nome);

    int ini = 0, fim = numItens - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("%s - %s - %d - prioridade %d\n",
                   mochila[meio].nome,
                   mochila[meio].tipo,
                   mochila[meio].quantidade,
                   mochila[meio].prioridade);
            return;
        } else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item não encontrado.\n");
}

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}