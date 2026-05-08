#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de dados para a Pergunta
typedef struct {
    char texto[200];     // Enunciado
    char alt[4][100];    // Alternativas A, B, C, D
    char correta;        // Letra correta: 'A', 'B', 'C' ou 'D'
    int nivel;           // 1=Facil, 2=Medio, 3=Dificil
    int unidade;         // 1, 2 ou 3
} Pergunta;

typedef Pergunta tp_item_pilha;

// No da pilha encadeada
typedef struct tp_no_pilha {
    tp_item_pilha info;
    struct tp_no_pilha *prox;
} tp_no_pilha;

// Pilha com ponteiro para o topo
typedef struct {
    tp_no_pilha *topo;
} tp_pilha;

tp_pilha *inicializa_pilha() {
    tp_pilha *pilha = (tp_pilha*) malloc(sizeof(tp_pilha));
    pilha->topo = NULL;
    return pilha;
}

int pilha_vazia(tp_pilha *pilha) {
    if (pilha->topo == NULL) return 1;
    return 0;
}

int push(tp_pilha *pilha, tp_item_pilha e) {
    tp_no_pilha *novo = (tp_no_pilha*) malloc(sizeof(tp_no_pilha));
    if (novo == NULL) return 0;
    novo->info = e;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    return 1;
}

int pop(tp_pilha *pilha, tp_item_pilha *e) {
    tp_no_pilha *aux;
    if (pilha_vazia(pilha)) return 0;
    *e = pilha->topo->info;
    aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    return 1;
}

int top(tp_pilha *pilha, tp_item_pilha *e) {
    if (pilha_vazia(pilha)) return 0;
    *e = pilha->topo->info;
    return 1;
}

int altura_pilha(tp_pilha *pilha) {
    int cont = 0;
    tp_no_pilha *aux = pilha->topo;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

#endif