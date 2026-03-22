#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX 50

typedef int
tp_item;

typedef struct {
    int topo;
    tp_item item[MAX];
} tp_pilha;

void inicializa_pilha(tp_pilha *p) {
    p-> topo = -1;

}

int pilha_vazia(tp_pilha *p){
    if (p->topo == -1) return 1;
    return 0;
}

int pilha_cheia(tp_pilha *p){
    if (p->topo == MAX-1){
        return 1;
    } else {
        return 0;
    }
}

int push(tp_pilha *p, tp_item e){
    if (pilha_cheia(p)==1) return 0;
    p-> topo++;
    p-> item[p->topo]=e;
    return 1;
}

int pop(tp_pilha *p, tp_item *e){
    if (pilha_vazia(p)== 1) return 0;
    *e=p->item[p->topo];
    p->topo--;
    return 1;
}

int top(tp_pilha *p, tp_item *e){
    if (pilha_vazia(p)) return 0;
    *e=p->item[p->topo];
    return 1;
}

void imprime_pilha(tp_pilha p){
    tp_item e;
    printf("\n");
    while (!pilha_vazia(&p)){
        pop(&p, &e);
        printf("%d ", e);
    }
}

int altura_pilha(tp_pilha *p){
    return p->topo+1;

}

void preenche_pilha(tp_pilha *p){
    for (int i = 1; i<=10; i++){
        push(p, i);
    }
}

void impar(tp_pilha *p1) {
    tp_pilha aux;
    inicializa_pilha(&aux);
    tp_item valor;


    while (pilha_vazia(p1) != 1) {
        pop(p1, &valor);
        if (valor % 2 == 0) {
            push(&aux, valor);
        }
    }

    while (pilha_vazia(&aux) != 1) {
        pop(&aux, &valor);
        push(p1, valor);
    }
}

int pilhas_identicas(tp_pilha p1, tp_pilha p2) {
    tp_item e1, e2;

    if (altura_pilha(&p1) != altura_pilha(&p2)) return 0;

    while (pilha_vazia(&p1) != 1) {
        pop(&p1, &e1);
        pop(&p2, &e2);
        if (e1 != e2) return 0;
    }
    return 1;
}


int empilhar_pilhas(tp_pilha *p1, tp_pilha *p2) {
    tp_pilha aux;
    inicializa_pilha(&aux);
    tp_item e;

    if (altura_pilha(p1) + altura_pilha(p2) > MAX) return 0;
    while (!pilha_vazia(p2)) {
        pop(p2, &e);
        push(&aux, e);
    }
    while (pilha_vazia(&aux) != 1) {
        pop(&aux, &e);
        push(p1, e);
    }
    return 1;
}

#endif