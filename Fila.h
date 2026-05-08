#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados para o Jogador
typedef struct {
    int id;
    char nome[50];
    int posicao;
} Jogador;

typedef Jogador tp_item;

// No da fila encadeada
typedef struct tp_no_fila {
    tp_item info;
    struct tp_no_fila *prox;
} tp_no_fila;

// Fila com ponteiros para inicio e fim
typedef struct {
    tp_no_fila *ini, *fim;
} tp_fila;

tp_fila *inicializa_fila() {
    tp_fila *fila = (tp_fila*) malloc(sizeof(tp_fila));
    fila->ini = fila->fim = NULL;
    return fila;
}

int filaVazia(tp_fila *fila) {
    if (fila->ini == NULL) return 1;
    return 0;
}

int insereFila(tp_fila *fila, tp_item e) {
    tp_no_fila *novo = (tp_no_fila*) malloc(sizeof(tp_no_fila));
    if (novo == NULL) return 0;

    novo->info = e;
    novo->prox = NULL;

    if (filaVazia(fila)) {
        fila->ini = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
    return 1;
}

int removeFila(tp_fila *fila, tp_item *e) {
    tp_no_fila *aux;
    if (filaVazia(fila)) return 0;

    *e = fila->ini->info;
    aux = fila->ini;

    if (fila->ini == fila->fim)
        fila->ini = fila->fim = NULL;
    else
        fila->ini = aux->prox;

    free(aux);
    return 1;
}

int tamanhoFila(tp_fila *fila) {
    int cont = 0;
    tp_no_fila *aux = fila->ini;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

#endif