#ifndef JOGADORES_H
#define JOGADORES_H

#include "Fila.h"

// Cadastra 2 a 4 jogadores e insere na fila de turnos
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


    for (int i = 0; i < qtd_jogadores; i++) {
        Jogador novo_jogador;
        novo_jogador.id = i + 1;
        novo_jogador.posicao = 0;

        printf("Nome do jogador %d: ", i + 1);
        scanf(" %49[^\n]", novo_jogador.nome);

        if (insereFila(fila_turnos, novo_jogador)) {
            printf("-> %s posicionado no inicio!\n", novo_jogador.nome);
        }
    }
}

#endif