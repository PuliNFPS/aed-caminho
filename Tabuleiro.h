#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Jogadores.h"

#define TOTAL_CASAS 30
#define CASAS_POR_UNIDADE 15
#define MAX_JOGADORES 4
#define CASAS_POR_LINHA 6

// Tipos de casa
#define CASA_NORMAL   'N'
#define CASA_PERGUNTA 'P'
#define CASA_AVANCO   'A'
#define CASA_RETORNO  'R'
#define CASA_INICIO   'I'
#define CASA_FIM      'F'

// Cores
#define COR_PADRAO    7
#define COR_VERDE     10
#define COR_VERMELHO  12
#define COR_AMARELO   14
#define COR_CIANO     11
#define COR_BRANCO    15
#define COR_CINZA     8
#define COR_MAGENTA   13

void cor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int cor_jogador(int id) {
    int cores[] = {0, 11, 13, 14, 10};
    return cores[id];
}

// No da lista duplamente encadeada
typedef struct tp_casa {
    int numero;
    int unidade;
    char tipo;
    int jogadores[MAX_JOGADORES];
    struct tp_casa *prox;
    struct tp_casa *ant;
} tp_casa;

typedef struct {
    tp_casa *inicio;
    tp_casa *fim;
    int total;
} tp_tabuleiro;

tp_casa *criar_casa(int numero, char tipo, int unidade) {
    tp_casa *nova = (tp_casa*) malloc(sizeof(tp_casa));
    nova->numero = numero;
    nova->tipo = tipo;
    nova->unidade = unidade;
    for (int i = 0; i < MAX_JOGADORES; i++) nova->jogadores[i] = 0;
    nova->prox = NULL;
    nova->ant = NULL;
    return nova;
}

char tipo_casa(int num) {
    if (num == 3 || num == 6 || num == 10 || num == 13 ||
        num == 17 || num == 20 || num == 24 || num == 27) return CASA_PERGUNTA;
    if (num == 5 || num == 15 || num == 22) return CASA_AVANCO;
    if (num == 8 || num == 18 || num == 28) return CASA_RETORNO;
    return CASA_NORMAL;
}

tp_tabuleiro *criar_tabuleiro() {
    tp_tabuleiro *tab = (tp_tabuleiro*) malloc(sizeof(tp_tabuleiro));
    tab->total = TOTAL_CASAS;
    tab->inicio = criar_casa(0, CASA_INICIO, 0);
    tp_casa *atual = tab->inicio;

    for (int i = 1; i <= TOTAL_CASAS; i++) {
        int unidade = (i <= CASAS_POR_UNIDADE) ? 1 : 2;
        char tipo = (i == TOTAL_CASAS) ? CASA_FIM : tipo_casa(i);
        tp_casa *nova = criar_casa(i, tipo, unidade);
        atual->prox = nova;
        nova->ant = atual;
        atual = nova;
    }
    tab->fim = atual;
    return tab;
}

tp_casa *buscar_casa(tp_tabuleiro *tab, int numero) {
    tp_casa *atual = tab->inicio;
    while (atual != NULL) {
        if (atual->numero == numero) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void colocar_jogador(tp_casa *casa, int id) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (casa->jogadores[i] == 0) { casa->jogadores[i] = id; return; }
    }
}

void remover_jogador(tp_casa *casa, int id) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (casa->jogadores[i] == id) { casa->jogadores[i] = 0; return; }
    }
}

void mover_jogador(tp_tabuleiro *tab, int id, int pos_antiga, int pos_nova) {
    if (pos_nova > TOTAL_CASAS) pos_nova = TOTAL_CASAS;
    if (pos_nova < 0) pos_nova = 0;
    tp_casa *antiga = buscar_casa(tab, pos_antiga);
    tp_casa *nova = buscar_casa(tab, pos_nova);
    if (antiga) remover_jogador(antiga, id);
    if (nova) colocar_jogador(nova, id);
}

// ==========================================
// INTERFACE VISUAL - TABULEIRO EM GRID
// ==========================================

// Cor de fundo pela tipo da casa
int cor_da_casa(char tipo) {
    switch (tipo) {
        case CASA_PERGUNTA: return COR_AMARELO;
        case CASA_AVANCO:   return COR_VERDE;
        case CASA_RETORNO:  return COR_VERMELHO;
        case CASA_INICIO:   return COR_CIANO;
        case CASA_FIM:      return COR_CIANO;
        default:            return COR_PADRAO;
    }
}

// Texto do tipo (3 chars)
const char *sigla_tipo(char tipo) {
    switch (tipo) {
        case CASA_PERGUNTA: return "?PE";
        case CASA_AVANCO:   return "+AV";
        case CASA_RETORNO:  return "-VL";
        case CASA_INICIO:   return "INI";
        case CASA_FIM:      return "FIM";
        default:            return "   ";
    }
}

// Desenha a linha separadora do grid
void linha_grid(int qtd) {
    cor(COR_CINZA);
    printf("  +");
    for (int i = 0; i < qtd; i++) {
        printf("---------+");
    }
    printf("\n");
    cor(COR_PADRAO);
}

// Desenha uma fileira de casas (linha do numero + tipo)
void linha_casas(tp_casa *casas[], int qtd) {
    cor(COR_CINZA);
    printf("  |");
    for (int i = 0; i < qtd; i++) {
        int c = cor_da_casa(casas[i]->tipo);
        cor(c);
        if (casas[i]->tipo == CASA_INICIO || casas[i]->tipo == CASA_FIM) {
            printf("  %s    ", sigla_tipo(casas[i]->tipo));
        } else if (casas[i]->tipo != CASA_NORMAL) {
            printf(" %02d %s  ", casas[i]->numero, sigla_tipo(casas[i]->tipo));
        } else {
            printf("   %02d   ", casas[i]->numero);
        }
        cor(COR_CINZA);
        printf("|");
    }
    printf("\n");
}

// Desenha a linha dos jogadores dentro das casas
void linha_jogadores(tp_casa *casas[], int qtd, Jogador jogadores[], int qtd_jog) {
    cor(COR_CINZA);
    printf("  |");
    for (int i = 0; i < qtd; i++) {
        // Conta jogadores nesta casa
        int jogs_aqui[MAX_JOGADORES];
        int n = 0;
        for (int j = 0; j < qtd_jog; j++) {
            for (int k = 0; k < MAX_JOGADORES; k++) {
                if (casas[i]->jogadores[k] == jogadores[j].id) {
                    jogs_aqui[n++] = j;
                }
            }
        }

        if (n == 0) {
            printf("         ");
        } else if (n == 1) {
            printf("   ");
            cor(cor_jogador(jogadores[jogs_aqui[0]].id));
            printf("[%c]", jogadores[jogs_aqui[0]].nome[0]);
            cor(COR_CINZA);
            printf("   ");
        } else if (n == 2) {
            printf(" ");
            cor(cor_jogador(jogadores[jogs_aqui[0]].id));
            printf("[%c]", jogadores[jogs_aqui[0]].nome[0]);
            cor(COR_CINZA);
            printf(" ");
            cor(cor_jogador(jogadores[jogs_aqui[1]].id));
            printf("[%c]", jogadores[jogs_aqui[1]].nome[0]);
            cor(COR_CINZA);
            printf(" ");
        } else if (n == 3) {
            cor(cor_jogador(jogadores[jogs_aqui[0]].id));
            printf("[%c]", jogadores[jogs_aqui[0]].nome[0]);
            cor(cor_jogador(jogadores[jogs_aqui[1]].id));
            printf("[%c]", jogadores[jogs_aqui[1]].nome[0]);
            cor(cor_jogador(jogadores[jogs_aqui[2]].id));
            printf("[%c]", jogadores[jogs_aqui[2]].nome[0]);
            cor(COR_CINZA);
        } else {
            for (int x = 0; x < n && x < 4; x++) {
                cor(cor_jogador(jogadores[jogs_aqui[x]].id));
                printf("%c", jogadores[jogs_aqui[x]].nome[0]);
            }
            cor(COR_CINZA);
            for (int x = n; x < 9; x++) printf(" ");
        }
        cor(COR_CINZA);
        printf("|");
    }
    printf("\n");
}

// Exibe o tabuleiro completo
void exibir_tabuleiro(tp_tabuleiro *tab, Jogador jogadores[], int qtd_jog) {
    // Coleta todas as casas em array
    tp_casa *todas[TOTAL_CASAS + 1];
    tp_casa *atual = tab->inicio;
    for (int i = 0; i <= TOTAL_CASAS; i++) {
        todas[i] = atual;
        atual = atual->prox;
    }

    printf("\n");
    cor(COR_CIANO);
    printf("  =============================================================\n");
    cor(COR_BRANCO);
    printf("                    CAMINHO DO CONHECIMENTO\n");
    cor(COR_CIANO);
    printf("  =============================================================\n\n");
    cor(COR_PADRAO);

    // Legenda
    printf("  ");
    cor(COR_AMARELO);  printf(" ?PE ");
    cor(COR_PADRAO);   printf("Pergunta  ");
    cor(COR_VERDE);    printf(" +AV ");
    cor(COR_PADRAO);   printf("Avanco  ");
    cor(COR_VERMELHO); printf(" -VL ");
    cor(COR_PADRAO);   printf("Retorno  ");
    cor(COR_CIANO);    printf(" FIM ");
    cor(COR_PADRAO);   printf("Chegada\n\n");

    int idx = 0;

    // Fileira 0: INI + casas 1-5
    cor(COR_CIANO);
    printf("  UNIDADE 1: FIFO, LIFO, Fila, Pilha, C Basico\n");
    cor(COR_PADRAO);
    tp_casa *fileira[CASAS_POR_LINHA];
    fileira[0] = todas[0]; // INI
    for (int i = 1; i < CASAS_POR_LINHA; i++) fileira[i] = todas[i];
    linha_grid(CASAS_POR_LINHA);
    linha_casas(fileira, CASAS_POR_LINHA);
    linha_jogadores(fileira, CASAS_POR_LINHA, jogadores, qtd_jog);
    linha_grid(CASAS_POR_LINHA);
    idx = CASAS_POR_LINHA;

    // Fileiras seguintes
    int u2_mostrado = 0;
    while (idx <= TOTAL_CASAS) {
        // Cabecalho da unidade 2 (casas 16+)
        if (!u2_mostrado && idx >= 18) {
            printf("\n");
            cor(COR_CIANO);
            printf("  UNIDADE 2: malloc, Ordenacao, Complexidade, Listas\n");
            cor(COR_PADRAO);
            u2_mostrado = 1;
        }

        int qtd = 0;
        while (qtd < CASAS_POR_LINHA && idx + qtd <= TOTAL_CASAS) {
            fileira[qtd] = todas[idx + qtd];
            qtd++;
        }

        // Seta de continuacao
        if (idx > 0) {
            cor(COR_CINZA);
            printf("      |\n      v\n");
            cor(COR_PADRAO);
        }

        linha_grid(qtd);
        linha_casas(fileira, qtd);
        linha_jogadores(fileira, qtd, jogadores, qtd_jog);
        linha_grid(qtd);

        idx += qtd;
    }

    // Status dos jogadores
    printf("\n");
    cor(COR_CIANO);
    printf("  -------------------------------------------------------------\n");
    cor(COR_PADRAO);
    for (int i = 0; i < qtd_jog; i++) {
        printf("  ");
        cor(cor_jogador(jogadores[i].id));
        printf("[%c] %-15s", jogadores[i].nome[0], jogadores[i].nome);
        cor(COR_PADRAO);
        printf(" Casa: %2d  |  Unidade %d\n",
               jogadores[i].posicao,
               jogadores[i].posicao <= CASAS_POR_UNIDADE ? 1 : 2);
    }
    cor(COR_CIANO);
    printf("  =============================================================\n");
    cor(COR_PADRAO);
}

#endif