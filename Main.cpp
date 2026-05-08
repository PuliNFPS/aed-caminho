#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Jogadores.h"
#include "Perguntas.h"

int main() {
    srand(time(NULL));

    tp_fila  *fila_turnos = inicializa_fila();
    tp_pilha *unidade1    = inicializa_pilha();
    tp_pilha *unidade2    = inicializa_pilha();
    tp_banco  bancos[NUM_UNIDADES];

    printf("============================================\n");
    printf("     CAMINHO DO CONHECIMENTO - FASE 1       \n");
    printf("============================================\n");

    cadastrar_jogadores(fila_turnos);
    criar_perguntas(unidade1, unidade2, bancos);

    // Teste
    printf("\n--- TESTE DE PERGUNTAS ---\n");
    printf("\n[Unidade 1]");
    fazer_pergunta(unidade1, &bancos[0]);
    printf("\n[Unidade 2]");
    fazer_pergunta(unidade2, &bancos[1]);

    printf("\n============================================\n");
    printf("   ESTRUTURAS PRONTAS PARA O JOGO INICIAR!  \n");
    printf("============================================\n\n");

    return 0;
}