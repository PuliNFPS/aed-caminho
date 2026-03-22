#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <string.h>

#define MAX 100

// 1. Estrutura de dados para o Jogador
typedef struct {
    int id;
    char nome[50];
    int posicao; // Casa atual no tabuleiro
} Jogador;

// 2. Adaptando o tipo do item da Fila para receber o Jogador
typedef Jogador tp_item;

typedef struct {
    tp_item item[MAX];
    int ini, fim;
} tp_fila;

// --- FUNÇÕES DA FILA CORRIGIDAS ---

void inicializa_fila(tp_fila *f) {
    f->ini = f->fim = MAX - 1; // Corrigido: usando apenas o ponteiro 'f'
}

int filaVazia(tp_fila *f) { // Corrigido: era tp_pilha
    if(f->ini == f->fim) return 1;
    return 0;
}

int proximo(int pos) {
    if(pos == MAX - 1) return 0;
    return ++pos;
}

int filaCheia(tp_fila *f) {
    if(proximo(f->fim) == f->ini)
        return 1;
    return 0;
}

int insereFila(tp_fila *f, tp_item e) { // Corrigido: era tp_pilha
    if(filaCheia(f))
        return 0;
    f->fim = proximo(f->fim);
    f->item[f->fim] = e;
    return 1;
}

int removeFila(tp_fila *f, tp_item *e) {
    if(filaVazia(f))
        return 0;
    f->ini = proximo(f->ini);
    *e = f->item[f->ini];
    return 1;
}

int tamanhoFila(tp_fila *f) {
    if (filaVazia(f)) return 0;
    if (f->ini < f->fim) return f->fim - f->ini;
    return MAX - 1 - f->ini + f->fim + 1;
}

#endif