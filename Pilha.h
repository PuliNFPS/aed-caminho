#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX_PILHA 50

// 1. Estrutura de dados para a Pergunta
typedef struct {
    int id;
    char texto[150];
    int unidade;     // 1, 2 ou 3
    int dificuldade; // 1 = Fácil, 2 = Médio, 3 = Difícil
} Pergunta;

// 2. Adaptando o tipo do item da Pilha para receber a Pergunta
typedef Pergunta tp_item_pilha;

typedef struct {
    int topo;
    tp_item_pilha item[MAX_PILHA];
} tp_pilha;

// --- FUNÇÕES DA PILHA CORRIGIDAS ---

void inicializa_pilha(tp_pilha *p) {
    p->topo = -1;
}

int pilha_vazia(tp_pilha *p) {
    if (p->topo == -1) return 1;
    return 0;
}

int pilha_cheia(tp_pilha *p) {
    if (p->topo == MAX_PILHA - 1) return 1;
    return 0;
}

int push(tp_pilha *p, tp_item_pilha e) {
    if (pilha_cheia(p) == 1) return 0;
    p->topo++;
    p->item[p->topo] = e;
    return 1;
}

int pop(tp_pilha *p, tp_item_pilha *e) {
    if (pilha_vazia(p) == 1) return 0;
    *e = p->item[p->topo];
    p->topo--;
    return 1;
}

int top(tp_pilha *p, tp_item_pilha *e) {
    if (pilha_vazia(p)) return 0;
    *e = p->item[p->topo];
    return 1;
}

int altura_pilha(tp_pilha *p) {
    return p->topo + 1;
}

#endif