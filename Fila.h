#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX 100

typedef int tp_item;

typedef struct {
    tp_item item[MAX];
    int ini,fim;

}tp_fila;


void inicializa_fila(tp_fila *p) {
    p->ini = f->fim = MAX-1;
}

int filaVazia(tp_pilha *f){
    if(f->ini == f->fim) return 1;
    return 0;
}

int proximo (int pos){
    if(pos== MAX-1) return 0;
    return ++pos;
}

int filaCheia (tp_fila *f){
    if(proximo(f->fim)==f->ini)
        return 1;
    return 0;
}

int insereFila (tp_pilha *f, tp_item e){
    if(filhaCheia(f))
        return 0;
    f->fim = proximo(f->fim);
    f->item[f->fim]=e;
    return 1;
}

int removeFila (tp_fila *f, tp_item *e){
    if(filaVazia(f))
        return 0;
    f->ini = proximo(f->ini);
    *e = f->item[f->ini];
    return 1;
}

int imprimeFila (tp_fila f){
    tp_item e;
    while(!filaVazia(&f)){
        removeFila(&f, &e);
        printf("\n%d", e);
    }
}

int tamanhoFila(tp_fila *f){
    if (filaVazia(f)) return 0;
    if (f->ini < f->fim) return f->fim - f->ini;
    return MAX - 1 - f->ini + f->fim + 1;
}

int tamanhoFila1(tp_filha f){
    int cont=0;
    tp_item e;
    while(!filaVazia(&f)){
        removeFila(&f, &e);
        cont++;
    }
    return cont; }

#endif