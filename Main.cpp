#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para o sorteio aleatório
#include "FILA.H"
#include "PILHA.H"

// ==========================================
// MÓDULO 1: GERENCIAMENTO DE JOGADORES (FILA)
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
// MÓDULO 2: GERENCIAMENTO DE PERGUNTAS (PILHA)
// ==========================================

// Função auxiliar para embaralhar um vetor de perguntas (Algoritmo Fisher-Yates)
void embaralhar_vetor(Pergunta arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Pergunta temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Função para criar, embaralhar e empilhar as perguntas
void preparar_perguntas(tp_pilha *u1, tp_pilha *u2, tp_pilha *u3) {
    // Criando um banco de 18 perguntas (6 por unidade, mesclando dificuldades)
    Pergunta banco[18] = {
        // Unidade 1
        {1, "O que e uma variavel?", 1, 1},
        {2, "Como se declara um inteiro em C?", 1, 1},
        {3, "O que faz o comando 'for'?", 1, 2},
        {4, "Diferenca entre 'while' e 'do-while'?", 1, 2},
        {5, "Como funciona a passagem por referencia?", 1, 3},
        {6, "Explique a recursividade de cauda.", 1, 3},
        // Unidade 2
        {7, "O que e um vetor (array)?", 2, 1},
        {8, "Como acessar o primeiro elemento de um vetor?", 2, 1},
        {9, "O que e uma matriz?", 2, 2},
        {10, "Como se declara uma struct?", 2, 2},
        {11, "Qual a complexidade de busca em um vetor nao ordenado?", 2, 3},
        {12, "Como funciona o algoritmo Bubble Sort?", 2, 3},
        // Unidade 3 (Estruturas de Dados)
        {13, "O que e o critério LIFO?", 3, 1},
        {14, "O que e o critério FIFO?", 3, 1},
        {15, "Quais os ponteiros principais de uma Fila?", 3, 2},
        {16, "O que acontece em um Stack Overflow?", 3, 2},
        {17, "Diferenca entre alocacao estatica e dinamica?", 3, 3},
        {18, "Como implementar uma Pilha usando duas Filas?", 3, 3}
    };

    // Separando em vetores temporários por unidade para embaralhar
    Pergunta vet_u1[6], vet_u2[6], vet_u3[6];
    int c1 = 0, c2 = 0, c3 = 0;

    for (int i = 0; i < 18; i++) {
        if (banco[i].unidade == 1) vet_u1[c1++] = banco[i];
        else if (banco[i].unidade == 2) vet_u2[c2++] = banco[i];
        else if (banco[i].unidade == 3) vet_u3[c3++] = banco[i];
    }

    // Sorteando a ordem (inclusão de forma aleatória)
    embaralhar_vetor(vet_u1, 6);
    embaralhar_vetor(vet_u2, 6);
    embaralhar_vetor(vet_u3, 6);

    // Empilhando nas respectivas pilhas da disciplina
    for (int i = 0; i < 6; i++) {
        push(u1, vet_u1[i]);
        push(u2, vet_u2[i]);
        push(u3, vet_u3[i]);
    }
    printf("\n-> 18 Perguntas criadas, embaralhadas e empilhadas com sucesso!\n");
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main() {
    // Semente para geração de números aleatórios
    srand(time(NULL));

    // Declarando as estruturas
    tp_fila fila_turnos;
    tp_pilha pilha_u1, pilha_u2, pilha_u3;

    // 1. Inicialização
    inicializa_fila(&fila_turnos);
    inicializa_pilha(&pilha_u1);
    inicializa_pilha(&pilha_u2);
    inicializa_pilha(&pilha_u3);

    printf("============================================\n");
    printf("     CAMINHO DO CONHECIMENTO - FASE 1       \n");
    printf("============================================\n");

    // 2. Funcionalidade da Dupla 1 (Jogadores)
    cadastrar_jogadores(&fila_turnos);

    // 3. Funcionalidade da Dupla 2 (Perguntas)
    preparar_perguntas(&pilha_u1, &pilha_u2, &pilha_u3);

    printf("\n============================================\n");
    printf("   ESTRUTURAS PRONTAS PARA O JOGO INICIAR!  \n");
    printf("============================================\n\n");

    return 0;
}