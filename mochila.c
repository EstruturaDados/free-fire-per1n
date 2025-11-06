#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0;
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    Item item;
    printf("\nNome do item: ");
    scanf(" %[^\n]", item.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", item.tipo);
    printf("Quantidade: ");
    scanf("%d", &item.quantidade);
    mochilaVetor[numItensVetor++] = item;
    printf("Item inserido com sucesso!\n");
}

void listarItensVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    printf("\nITENS (VETOR):\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("%d. %s - %s (x%d)\n", i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void removerItemVetor() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < numItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            numItensVetor--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado: %s - %s (x%d)\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return i;
        }
    }
    printf("\nItem não encontrado.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
    return -1;
}

void ordenarVetorPorNome() {
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nVetor ordenado por nome!\n");
}

void buscarBinariaVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    char nome[30];
    printf("\nNome do item a buscar (binária): ");
    scanf(" %[^\n]", nome);
    int inicio = 0, fim = numItensVetor - 1;
    comparacoesBinaria = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) {
            printf("\nItem encontrado: %s - %s (x%d)\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoesBinaria);
            return;
        } else if (cmp > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nItem não encontrado.\n");
    printf("Comparações: %d\n", comparacoesBinaria);
}

void inserirItemLista(No** inicio) {
    Item item;
    printf("\nNome do item: ");
    scanf(" %[^\n]", item.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", item.tipo);
    printf("Quantidade: ");
    scanf("%d", &item.quantidade);
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item inserido na lista!\n");
}

void listarItensLista(No* inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }
    printf("\nITENS (LISTA):\n");
    No* atual = inicio;
    while (atual != NULL) {
        printf("- %s - %s (x%d)\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerItemLista(No** inicio) {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);
    No *atual = *inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Item não encontrado!\n");
        return;
    }
    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Item removido da lista!\n");
}

void buscarSequencialLista(No* inicio) {
    char nome[30];
    comparacoesSequencial = 0;
    printf("\nNome do item a buscar: ");
    scanf(" %[^\n]", nome);
    No* atual = inicio;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s - %s (x%d)\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("\nItem não encontrado.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
}

int main() {
    int estrutura, opcao;
    No* inicio = NULL;
    printf("SISTEMA DE MOCHILA\n");
    printf("1 - Vetor\n2 - Lista Encadeada\n> ");
    scanf("%d", &estrutura);
    do {
        printf("\nMENU\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        if (estrutura == 1) printf("5 - Ordenar e buscar (binária)\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (estrutura == 1) inserirItemVetor();
                else inserirItemLista(&inicio);
                break;
            case 2:
                if (estrutura == 1) removerItemVetor();
                else removerItemLista(&inicio);
                break;
            case 3:
                if (estrutura == 1) listarItensVetor();
                else listarItensLista(inicio);
                break;
            case 4:
                if (estrutura == 1) {
                    char nome[30];
                    printf("\nNome do item a buscar: ");
                    scanf(" %[^\n]", nome);
                    buscarSequencialVetor(nome);
                } else buscarSequencialLista(inicio);
                break;
            case 5:
                if (estrutura == 1) {
                    ordenarVetorPorNome();
                    buscarBinariaVetor();
                } else printf("\nOpção inválida para lista encadeada!\n");
                break;
        }
    } while (opcao != 0);
    printf("\nPrograma finalizado.\n");
    return 0;
}