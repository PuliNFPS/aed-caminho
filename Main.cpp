#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Jogo.h"

int main() {
    srand(time(NULL));

    // Configura console para UTF-8
    SetConsoleOutputCP(65001);

    tp_jogo jogo;
    jogo.fila_turnos = inicializa_fila();
    jogo.pilha_u1    = inicializa_pilha();
    jogo.pilha_u2    = inicializa_pilha();
    jogo.tabuleiro   = criar_tabuleiro();

    system("cls");
    cor(COR_CIANO);
    printf("\n  ============================================\n");
    cor(COR_BRANCO);
    printf("       CAMINHO DO CONHECIMENTO\n");
    cor(COR_CIANO);
    printf("  ============================================\n");
    cor(COR_PADRAO);

    cadastrar_jogadores(jogo.fila_turnos);
    criar_perguntas(jogo.pilha_u1, jogo.pilha_u2, jogo.bancos);
    iniciar_jogo(&jogo);

    return 0;
}