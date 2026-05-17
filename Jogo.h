#ifndef JOGO_H
#define JOGO_H

#include <conio.h>
#include "Jogadores.h"
#include "Perguntas.h"
#include "Tabuleiro.h"

// Estado completo do jogo
typedef struct {
    tp_fila      *fila_turnos;
    tp_pilha     *pilha_u1, *pilha_u2;
    tp_banco      bancos[NUM_UNIDADES];
    tp_tabuleiro *tabuleiro;
    Jogador       jogadores[MAX_JOGADORES];
    int           qtd_jog;
    int           rodada;
    int           vencedor;
} tp_jogo;

// Espera o jogador apertar qualquer tecla
void esperar_tecla(const char *msg) {
    cor(COR_CINZA);
    printf("  %s", msg);
    cor(COR_PADRAO);
    getch();
    printf("\n");
}

int rolar_dado() { return rand() % 6 + 1; }

int unidade_da_posicao(int pos) {
    return (pos <= CASAS_POR_UNIDADE) ? 1 : 2;
}

// Exibe o dado de forma visual
void exibir_dado(int valor) {
    cor(COR_BRANCO);
    printf("\n    +-------+\n");
    printf("    |       |\n");
    printf("    |   %d   |\n", valor);
    printf("    |       |\n");
    printf("    +-------+\n");
    cor(COR_PADRAO);
}

// Atualiza posicao no tabuleiro e no array
void atualizar_posicao(tp_jogo *jogo, Jogador *jog, int pos_nova) {
    if (pos_nova > TOTAL_CASAS) pos_nova = TOTAL_CASAS;
    if (pos_nova < 0) pos_nova = 0;

    mover_jogador(jogo->tabuleiro, jog->id, jog->posicao, pos_nova);
    jog->posicao = pos_nova;

    for (int i = 0; i < jogo->qtd_jog; i++) {
        if (jogo->jogadores[i].id == jog->id) {
            jogo->jogadores[i] = *jog;
            break;
        }
    }

    if (pos_nova >= TOTAL_CASAS) jogo->vencedor = jog->id;
}

// Processa o efeito da casa
void processar_casa(tp_jogo *jogo, Jogador *jog) {
    tp_casa *casa = buscar_casa(jogo->tabuleiro, jog->posicao);
    int pos = jog->posicao;

    switch (casa->tipo) {
        case CASA_PERGUNTA: {
            int unidade = unidade_da_posicao(pos);
            cor(COR_AMARELO);
            printf("\n  >>> CASA DE PERGUNTA! (Unidade %d) <<<\n", unidade);
            cor(COR_PADRAO);

            tp_pilha *pilha = (unidade == 1) ? jogo->pilha_u1 : jogo->pilha_u2;
            tp_banco *banco = &jogo->bancos[unidade - 1];
            int resultado = fazer_pergunta(pilha, banco);

            if (resultado > 0) {
                cor(COR_VERDE);
                printf("  +++ Bonus: avancando +%d casa(s)!\n", resultado);
                cor(COR_PADRAO);
                atualizar_posicao(jogo, jog, pos + resultado);
            } else {
                cor(COR_VERMELHO);
                printf("  --- Punicao: voltando 1 casa!\n");
                cor(COR_PADRAO);
                atualizar_posicao(jogo, jog, pos - 1);
            }
            break;
        }
        case CASA_AVANCO:
            cor(COR_VERDE);
            printf("\n  >>> CASA DE AVANCO! +2 casas! <<<\n");
            cor(COR_PADRAO);
            atualizar_posicao(jogo, jog, pos + 2);
            break;

        case CASA_RETORNO:
            cor(COR_VERMELHO);
            printf("\n  >>> CASA DE RETORNO! -2 casas! <<<\n");
            cor(COR_PADRAO);
            atualizar_posicao(jogo, jog, pos - 2);
            break;

        default:
            cor(COR_CINZA);
            printf("\n  Casa normal.\n");
            cor(COR_PADRAO);
            break;
    }
}

// Executa o turno de um jogador
void executar_turno(tp_jogo *jogo) {
    Jogador atual;
    removeFila(jogo->fila_turnos, &atual);

    for (int i = 0; i < jogo->qtd_jog; i++) {
        if (jogo->jogadores[i].id == atual.id) {
            atual = jogo->jogadores[i];
            break;
        }
    }

    system("cls");
    exibir_tabuleiro(jogo->tabuleiro, jogo->jogadores, jogo->qtd_jog);

    printf("\n");
    cor(COR_BRANCO);
    printf("  RODADA %d", jogo->rodada);
    cor(COR_PADRAO);
    printf(" - Vez de: ");
    cor(cor_jogador(atual.id));
    printf("%s", atual.nome);
    cor(COR_PADRAO);
    printf(" (Casa %d)\n", atual.posicao);

    esperar_tecla("Pressione qualquer tecla para rolar o dado...");

    int dado = rolar_dado();
    exibir_dado(dado);

    printf("  Avanca de casa %d para casa %d\n", atual.posicao, atual.posicao + dado);
    atualizar_posicao(jogo, &atual, atual.posicao + dado);

    if (!jogo->vencedor) {
        processar_casa(jogo, &atual);
    }

    insereFila(jogo->fila_turnos, atual);
    if (atual.id == jogo->qtd_jog) jogo->rodada++;
}

// Resumo final com cores
void resumo_final(tp_jogo *jogo) {
    system("cls");
    exibir_tabuleiro(jogo->tabuleiro, jogo->jogadores, jogo->qtd_jog);

    printf("\n");
    cor(COR_CIANO);
    printf("  ============================================\n");
    cor(COR_BRANCO);
    printf("              FIM DO JOGO!\n");
    cor(COR_CIANO);
    printf("  ============================================\n\n");

    // Vencedor
    for (int i = 0; i < jogo->qtd_jog; i++) {
        if (jogo->jogadores[i].id == jogo->vencedor) {
            cor(COR_VERDE);
            printf("  VENCEDOR: %s\n", jogo->jogadores[i].nome);
            break;
        }
    }

    cor(COR_PADRAO);
    printf("\n  Rodadas jogadas: %d\n\n", jogo->rodada);
    printf("  Placar final:\n");
    for (int i = 0; i < jogo->qtd_jog; i++) {
        cor(cor_jogador(jogo->jogadores[i].id));
        printf("    %s", jogo->jogadores[i].nome);
        cor(COR_PADRAO);
        printf(" - Casa %d", jogo->jogadores[i].posicao);
        if (jogo->jogadores[i].id == jogo->vencedor) {
            cor(COR_VERDE);
            printf(" APROVADO!");
        }
        cor(COR_PADRAO);
        printf("\n");
    }

    printf("\n");
    cor(COR_CIANO);
    printf("  ============================================\n");
    cor(COR_PADRAO);
    printf("\n");
}

// Inicializa e roda o jogo
void iniciar_jogo(tp_jogo *jogo) {
    tp_casa *inicio = buscar_casa(jogo->tabuleiro, 0);
    jogo->qtd_jog = tamanhoFila(jogo->fila_turnos);

    for (int i = 0; i < jogo->qtd_jog; i++) {
        removeFila(jogo->fila_turnos, &jogo->jogadores[i]);
        jogo->jogadores[i].posicao = 0;
        colocar_jogador(inicio, jogo->jogadores[i].id);
        insereFila(jogo->fila_turnos, jogo->jogadores[i]);
    }

    jogo->rodada = 1;
    jogo->vencedor = 0;

    esperar_tecla("Pressione qualquer tecla para comecar...");

    while (!jogo->vencedor) {
        executar_turno(jogo);

        if (!jogo->vencedor) {
            esperar_tecla("Pressione qualquer tecla para continuar...");
        }
    }

    resumo_final(jogo);
}

#endif