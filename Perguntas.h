#ifndef PERGUNTAS_H
#define PERGUNTAS_H

#include <string.h>
#include <stdlib.h>
#include "Pilha.h"

#define NUM_UNIDADES 2
#define POR_UNIDADE 6

// Banco de perguntas: guarda originais para reembaralhar quando pilha esvaziar
typedef struct {
    Pergunta perguntas[POR_UNIDADE];
    int qtd;
} tp_banco;

// Cria uma pergunta de forma compacta
Pergunta nova_pergunta(const char *texto, const char *a, const char *b,
                       const char *c, const char *d, char correta, int nivel, int unidade) {
    Pergunta p;
    strcpy(p.texto, texto);
    strcpy(p.alt[0], a); strcpy(p.alt[1], b);
    strcpy(p.alt[2], c); strcpy(p.alt[3], d);
    p.correta = correta; p.nivel = nivel; p.unidade = unidade;
    return p;
}

// Embaralhamento Fisher-Yates
void embaralhar(Pergunta vet[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Pergunta temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

// Esvazia a pilha e recarrega com perguntas embaralhadas do banco
void carregar_pilha(tp_pilha *pilha, tp_banco *banco) {
    Pergunta lixo;
    while (!pilha_vazia(pilha)) pop(pilha, &lixo);
    embaralhar(banco->perguntas, banco->qtd);
    for (int i = 0; i < banco->qtd; i++) push(pilha, banco->perguntas[i]);
}

// ==========================================
// CRIACAO DAS PERGUNTAS (6 por unidade)
// ==========================================
void criar_perguntas(tp_pilha *u1, tp_pilha *u2, tp_banco bancos[]) {

    // === UNIDADE 1: FIFO, LIFO, Fila, Pilha, Basico de C ===
    bancos[0].qtd = 6;
    Pergunta *b = bancos[0].perguntas;

    // Faceis
    b[0] = nova_pergunta("Qual estrutura segue a regra FIFO?",
        "A) Pilha", "B) Fila", "C) Arvore", "D) Grafo",
        'B', 1, 1);

    b[1] = nova_pergunta("O que significa a sigla LIFO?",
        "A) Last In, First Out", "B) Last In, Final Order",
        "C) Linear Input, First Output", "D) List In, First Out",
        'A', 1, 1);

    // Medias
    b[2] = nova_pergunta("Qual operacao remove o elemento do topo de uma pilha?",
        "A) push", "B) pop", "C) enqueue", "D) dequeue",
        'B', 2, 1);

    b[3] = nova_pergunta("Em C, qual simbolo indica o endereco de uma variavel?",
        "A) *", "B) #", "C) &", "D) @",
        'C', 2, 1);

    // Dificeis
    b[4] = nova_pergunta("Em uma fila circular com MAX posicoes, como avancar o indice?",
        "A) (pos + 1) % MAX", "B) pos + 1", "C) pos % MAX", "D) (pos - 1) % MAX",
        'A', 3, 1);

    b[5] = nova_pergunta("O que acontece ao empilhar em uma pilha estatica cheia?",
        "A) O topo volta a zero", "B) Ocorre Stack Overflow",
        "C) O ultimo elemento e sobrescrito", "D) A pilha dobra de tamanho",
        'B', 3, 1);

    // === UNIDADE 2: malloc, Ordenacao, Complexidade, Listas Encadeadas ===
    bancos[1].qtd = 6;
    b = bancos[1].perguntas;

    // Faceis
    b[0] = nova_pergunta("Qual funcao em C aloca memoria dinamicamente?",
        "A) calloc", "B) free", "C) malloc", "D) sizeof",
        'C', 1, 2);

    b[1] = nova_pergunta("Em uma lista simplesmente encadeada, cada no possui:",
        "A) Dado e ponteiro para proximo", "B) Apenas o dado",
        "C) Ponteiro para anterior e proximo", "D) Dois dados",
        'A', 1, 2);

    // Medias
    b[2] = nova_pergunta("Qual a complexidade do Bubble Sort no pior caso?",
        "A) O(n)", "B) O(n log n)", "C) O(n^2)", "D) O(log n)",
        'C', 2, 2);

    b[3] = nova_pergunta("Qual a vantagem da lista duplamente encadeada sobre a simples?",
        "A) Usa menos memoria", "B) Percorre em ambas direcoes",
        "C) Acesso direto por indice", "D) Insercao mais rapida no inicio",
        'B', 2, 2);

    // Dificeis
    b[4] = nova_pergunta("Qual a complexidade de inserir no inicio de uma lista encadeada?",
        "A) O(n)", "B) O(n^2)", "C) O(log n)", "D) O(1)",
        'D', 3, 2);

    b[5] = nova_pergunta("Qual funcao deve ser chamada para liberar memoria alocada com malloc?",
        "A) delete", "B) release", "C) free", "D) destroy",
        'C', 3, 2);

    // Embaralha e carrega cada pilha
    carregar_pilha(u1, &bancos[0]);
    carregar_pilha(u2, &bancos[1]);

    printf("\n-> 12 perguntas criadas, embaralhadas e empilhadas!\n");
    printf("   Unidade 1: %d perguntas | Unidade 2: %d\n",
           altura_pilha(u1), altura_pilha(u2));
}

// ==========================================
// FAZER PERGUNTA
// ==========================================
int fazer_pergunta(tp_pilha *pilha_unidade, tp_banco *banco) {
    Pergunta p;
    char r;
    const char *nomes_dif[] = {"", "Facil", "Medio", "Dificil"};

    // Se esgotou, reembaralha e recarrega
    if (pilha_vazia(pilha_unidade)) {
        printf("   [Reembaralhando perguntas da unidade %d...]\n", banco->perguntas[0].unidade);
        carregar_pilha(pilha_unidade, banco);
    }

    pop(pilha_unidade, &p);

    printf("\n  +-----------------------------------------+\n");
    printf("  | Unidade %d | Dificuldade: %-8s       |\n", p.unidade, nomes_dif[p.nivel]);
    printf("  +-----------------------------------------+\n");
    printf("  %s\n\n", p.texto);
    printf("    %s\n    %s\n    %s\n    %s\n", p.alt[0], p.alt[1], p.alt[2], p.alt[3]);
    printf("\n  Sua resposta (A/B/C/D): ");
    scanf(" %c", &r);

    if (r >= 'a' && r <= 'd') r = r - 32;

    if (r == p.correta) {
        printf("  CORRETO! Avanca %d casa(s)!\n", p.nivel);
        return p.nivel;
    } else {
        printf("  ERRADO! A resposta era: %c\n", p.correta);
        return -1;
    }
}

#endif