#include <stdio.h>
#include <stdlib.h>
#include "FILA.H"

// Função modularizada para cadastrar os jogadores
void cadastrar_jogadores(tp_fila *fila_turnos) {
    int qtd_jogadores = 0;

    // Garante que o número de jogadores seja entre 2 e 4
    while (qtd_jogadores < 2 || qtd_jogadores > 4) {
        printf("Quantos jogadores vao participar? (2 a 4): ");
        scanf("%d", &qtd_jogadores);

        if (qtd_jogadores < 2 || qtd_jogadores > 4) {
            printf("Quantidade invalida! Tente novamente.\n\n");
        }
    }

    // Limpa o buffer do teclado antes de ler as strings
    while (getchar() != '\n');

    // Cria e insere cada jogador na fila
    for (int i = 0; i < qtd_jogadores; i++) {
        Jogador novo_jogador;
        novo_jogador.id = i + 1;
        novo_jogador.posicao = 0; // Todos iniciam na casa 0 (INICIO)

        printf("Digite o nome do jogador %d: ", i + 1);
        fgets(novo_jogador.nome, 50, stdin);

        // Remove o '\n' que o fgets captura
        novo_jogador.nome[strcspn(novo_jogador.nome, "\n")] = 0;

        // Insere o jogador na estrutura adequada (Fila)
        if (insereFila(fila_turnos, novo_jogador)) {
            printf("-> %s cadastrado com sucesso e posicionado no inicio!\n", novo_jogador.nome);
        } else {
            printf("-> Erro ao inserir jogador na fila!\n");
        }
    }
}

// Função auxiliar apenas para testar se a fila guardou tudo certinho
void exibir_ordem_rodada(tp_fila *fila_turnos) {
    printf("\n--- ORDEM DAS RODADAS ---\n");
    tp_item j;
    int tamanho = tamanhoFila(fila_turnos);

    for(int i = 0; i < tamanho; i++){
        removeFila(fila_turnos, &j);
        printf("%d. %s (Posicao: %d)\n", i + 1, j.nome, j.posicao);
        // Retorna o jogador para a fila para não perder os dados
        insereFila(fila_turnos, j);
    }
    printf("-------------------------\n");
}

int main() {
    tp_fila fila_turnos;

    // 1. Inicializa a estrutura de dados
    inicializa_fila(&fila_turnos);

    printf("=== BEM-VINDO AO CAMINHO DO CONHECIMENTO ===\n\n");

    // 2. Chama a funcionalidade exigida na primeira entrega
    cadastrar_jogadores(&fila_turnos);

    // 3. Verifica a fila (Teste)
    exibir_ordem_rodada(&fila_turnos);

    return 0;
}