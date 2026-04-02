#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Fila.h"
#include "Pilha.h"

// ==========================================
// MODULO 1: GERENCIAMENTO DE JOGADORES (FILA)
// ==========================================
void cadastrar_jogadores(tp_fila *fila_turnos) {
    int qtd_jogadores = 0;

    printf("\n--- CADASTRO DE JOGADORES ---\n");
    while (qtd_jogadores < 2 || qtd_jogadores > 4) {
        printf("Quantos jogadores vao participar? (2 a 4): ");
        scanf("%d", &qtd_jogadores);
        if (qtd_jogadores < 2 || qtd_jogadores > 4) {
            printf("Quantidade invalida! Tente novamente.\n");
        }
    }

    while (getchar() != '\n'); // Limpa buffer

    for (int i = 0; i < qtd_jogadores; i++) {
        Jogador novo_jogador;
        novo_jogador.id = i + 1;
        novo_jogador.posicao = 0;

        printf("Nome do jogador %d: ", i + 1);
        fgets(novo_jogador.nome, 50, stdin);
        novo_jogador.nome[strcspn(novo_jogador.nome, "\n")] = 0;

        if (insereFila(fila_turnos, novo_jogador)) {
            printf("-> %s posicionado no inicio!\n", novo_jogador.nome);
        }
    }
}


// ==========================================
// FUNCAO PRINCIPAL
// ==========================================
int main() {
    srand(time(NULL));

    tp_fila fila_turnos;
    tp_pilha pilha_u1, pilha_u2, pilha_u3;

    inicializa_fila(&fila_turnos);
    inicializa_pilha(&pilha_u1);
    inicializa_pilha(&pilha_u2);
    inicializa_pilha(&pilha_u3);

    printf("============================================\n");
    printf("     CAMINHO DO CONHECIMENTO - FASE 1       \n");
    printf("============================================\n");

    cadastrar_jogadores(&fila_turnos);
    preparar_perguntas(&pilha_u1, &pilha_u2, &pilha_u3);

    printf("\n============================================\n");
    printf("   ESTRUTURAS PRONTAS PARA O JOGO INICIAR!  \n");
    printf("============================================\n\n");

    return 0;
}