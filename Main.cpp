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


// cria perguntas
void perguntas(tp_pilha *facil, tp_pilha *medio, tp_pilha *dificil) {
    Pergunta p;

    // facil
    strcpy(p.texto,"variavel local existe so na funcao? (s/n)");
    p.resposta='s'; p.nivel=1; push(facil,p);

    strcpy(p.texto,"fila segue ordem de chegada? (s/n)");
    p.resposta='s'; p.nivel=1; push(facil,p);

    strcpy(p.texto,"pilha remove ultimo inserido? (s/n)");
    p.resposta='s'; p.nivel=1; push(facil,p);

    // medio
    strcpy(p.texto,"while sempre executa uma vez? (s/n)");
    p.resposta='n'; p.nivel=2; push(medio,p);

    strcpy(p.texto,"for pode virar while? (s/n)");
    p.resposta='s'; p.nivel=2; push(medio,p);

    strcpy(p.texto,"array cresce automaticamente? (s/n)");
    p.resposta='n'; p.nivel=2; push(medio,p);

    // dificil
    strcpy(p.texto,"scanf precisa de &? (s/n)");
    p.resposta='s'; p.nivel=3; push(dificil,p);

    strcpy(p.texto,"printf muda valor de variavel? (s/n)");
    p.resposta='n'; p.nivel=3; push(dificil,p);

    strcpy(p.texto,"ponteiro guarda endereco? (s/n)");
    p.resposta='s'; p.nivel=3; push(dificil,p);
}

// faz pergunta
int fazer_pergunta(tp_pilha *facil, tp_pilha *medio, tp_pilha *dificil) {
    int tipo = rand()%3+1;
    Pergunta p;
    char r;

    if(tipo==1 && !pilha_vazia(facil)) {
        pop(facil, &p);
    }
    else if(tipo==2 && !pilha_vazia(medio)) {
        pop(medio, &p);
    }
    else {
        pop(dificil, &p);
    }

    printf("pergunta (nivel %d): %s\n", p.nivel, p.texto);
    scanf(" %c",&r);

    if(r==p.resposta) {
        printf("acertou\n");
        return tipo;
    } else {
        printf("errou\n");
        return -1;
    }
}



// ==========================================
// FUNCAO PRINCIPAL
// ==========================================
int main() {
    srand(time(NULL));

    tp_fila fila_turnos;
    tp_pilha facil,medio,dificil;

    inicializa_fila(&fila_turnos);
    inicializa_pilha(&facil);
    inicializa_pilha(&medio);
    inicializa_pilha(&dificil);

    printf("============================================\n");
    printf("     CAMINHO DO CONHECIMENTO - FASE 1       \n");
    printf("============================================\n");

    cadastrar_jogadores(&fila_turnos);
    perguntas(&facil,&medio,&dificil);

    printf("\n============================================\n");
    printf("   ESTRUTURAS PRONTAS PARA O JOGO INICIAR!  \n");
    printf("============================================\n\n");

    return 0;
}