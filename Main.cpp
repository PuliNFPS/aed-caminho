/* =====================================================================
 * main.c
 * Disciplina : Algoritmos e Estrutura de Dados
 * Docente    : Marcio Rene Brandao Soussa
 * Trabalho   : Caminho do Conhecimento - 1a Entrega
 *
 * Compilacao:
 *   gcc main.c jogador.c perguntas.c -o jogo
 *
 * Descricao:
 *   Integra os modulos das duas duplas e demonstra o funcionamento
 *   da Fila FIFO (jogadores) e das Pilhas LIFO embaralhadas (perguntas).
 * ===================================================================== */

#include <stdio.h>
#include <ctype.h>
#include "jogador.h"
#include "fila_jogador.h"
#include "perguntas.h"
#include "pilha_pergunta.h"

/* Prototipo da funcao de cadastro definida em jogador.c */
tp_fila cadastrarJogadores();

/* =====================================================================
 * main
 * ===================================================================== */
int main() {

    printf("\n");
    printf("  ============================================\n");
    printf("    CAMINHO DO CONHECIMENTO - 1a Entrega\n");
    printf("    Algoritmos e Estrutura de Dados\n");
    printf("  ============================================\n");

    /* ------------------------------------------------------------------
     * ETAPA 1: Carregar banco de perguntas (Dupla 2 - perguntas.c)
     * ------------------------------------------------------------------ */
    printf("\n  [1/3] Carregando banco de perguntas...\n");
    carregarBancoDePerguntas();
    printf("  %d perguntas carregadas com sucesso!\n", TOTAL_PERGUNTAS);

    /* ------------------------------------------------------------------
     * ETAPA 2: Inicializar pilhas embaralhadas (Dupla 2 - pilha_pergunta.h)
     * ------------------------------------------------------------------ */
    printf("\n  [2/3] Inicializando pilhas (Fisher-Yates)...\n\n");
    inicializarPilhas();

    /* ------------------------------------------------------------------
     * ETAPA 3: Cadastrar jogadores na Fila FIFO (Dupla 1 - jogador.c)
     * ------------------------------------------------------------------ */
    printf("\n  [3/3] Cadastro de jogadores...\n");
    tp_fila fila = cadastrarJogadores();

    /* ------------------------------------------------------------------
     * DEMONSTRACAO 1: Fila de turno dos jogadores
     * ------------------------------------------------------------------ */
    printf("\n  ============================================\n");
    printf("   FILA FIFO - Ordem de turno dos jogadores\n");
    printf("  ============================================\n");
    imprimeFila(fila);
    printf("  Total de jogadores na fila: %d\n", tamanhoFila(&fila));

    /* ------------------------------------------------------------------
     * DEMONSTRACAO 2: Conteudo das pilhas embaralhadas
     * ------------------------------------------------------------------ */
    printf("\n  ============================================\n");
    printf("   PILHAS LIFO - Perguntas por unidade\n");
    printf("   (embaralhadas pelo algoritmo Fisher-Yates)\n");
    printf("  ============================================\n");
    for (int u = 0; u < NUM_UNIDADES; u++) {
        printf("\n  Pilha da %s (%d perguntas):\n",
               nomeUnidade(u + 1),
               altura_pilha(&pilhasPorUnidade[u]));
        imprime_pilha(pilhasPorUnidade[u]);
    }

    /* ------------------------------------------------------------------
     * DEMONSTRACAO 3: Cada jogador responde uma pergunta da Unidade 1
     * ------------------------------------------------------------------ */
    printf("\n  ============================================\n");
    printf("   SIMULACAO - Rodada de perguntas\n");
    printf("  ============================================\n");
    printf("  Cada jogador retira uma pergunta do TOPO\n");
    printf("  da pilha da Unidade 1 e tenta responder.\n\n");

    int total = tamanhoFila(&fila);

    for (int rodada = 1; rodada <= total; rodada++) {

        /* Recarrega pilha se esgotou */
        if (pilha_vazia(&pilhasPorUnidade[0])) {
            recarregarPilha(1);
        }

        /* Retira pergunta do TOPO (LIFO) */
        Pergunta p;
        pop(&pilhasPorUnidade[0], &p);

        /* Retira jogador da frente da fila (FIFO) */
        Jogador j;
        removeFila(&fila, &j);

        printf("  Rodada %d - Jogador: %s\n", rodada, j.nome);
        exibirPergunta(&p);

        /* Le resposta */
        char resp;
        printf("\n  Sua resposta (A/B/C/D): ");
        scanf(" %c", &resp);
        while (getchar() != '\n');
        resp = toupper(resp);

        /* Avalia */
        if (resp == p.gabarito) {
            printf("  CORRETO! A resposta era: %c\n", p.gabarito);
            j.posicao++;
        } else {
            printf("  ERRADO!  A resposta correta era: %c\n", p.gabarito);
        }

        /* Reinsere jogador no FINAL da fila (FIFO) */
        insereFila(&fila, j);

        printf("  Perguntas restantes na pilha U1: %d\n", altura_pilha(&pilhasPorUnidade[0]));
        printf("  ------------------------------------------\n");
    }

    /* Status final */
    printf("\n  Estado final da fila:\n");
    imprimeFila(fila);

    printf("\n  ============================================\n");
    printf("   Demonstracao concluida!\n");
    printf("  ============================================\n\n");

    return 0;
}