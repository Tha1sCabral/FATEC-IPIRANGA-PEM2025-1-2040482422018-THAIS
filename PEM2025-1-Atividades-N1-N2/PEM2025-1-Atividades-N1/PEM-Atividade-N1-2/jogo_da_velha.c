/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Tabuleiro de jogo da velha!:)    *
* Data - 28/02/2025                                      * 
* Autor: Thaís Cabral;       '-'                         *
*--------------------------------------------------------*/
#include <stdio.h>

int main() {
    char Tabuleiro [3][3] = {{' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}}; //Estrutura do tabuleiro.
    char jogador = 'X'; //Jogador 1.
    int jogadas = 0; //Jogador 2.
    for (jogadas = 0; jogadas < 9; jogadas++) {
        // Exibe o tabuleiro.
        printf("\n");
        int i = 0;
        for ( i = 0; i < 3; i++) {
            printf(" %c | %c | %c \n", Tabuleiro[i][0], Tabuleiro[i][1], Tabuleiro[i][2]);// Imprime cada linha do tabuleiro com separadores.
            if (i < 2) printf("---+---+---\n");
        }
        
        // Leitura da jogada.
        int linha, Coluna;
        printf("Jogador %c- Digite a linha (0,1,2) e coluna (0,1,2): ", jogador);
        scanf("%d %d", &linha, &Coluna);
        
        // Valida e marca.
        if (linha < 0 || linha > 2 || Coluna < 0 || Coluna > 2 || Tabuleiro[linha][Coluna] != ' ') {
            printf("Jogada invalida! Tente novamente.\n");
            jogadas--; // Repete a jogada.
            continue;
        }
        Tabuleiro[linha][Coluna] = jogador;
        
        // Verifica a vitoria.
        int Venceu = 0;
        
        for (i = 0; i < 3; i++) {
            if (Tabuleiro[i][0] == jogador && Tabuleiro[i][1] == jogador && Tabuleiro[i][2] == jogador) Venceu = 1; // Linhas.
            if (Tabuleiro[0][i] == jogador && Tabuleiro[1][i] == jogador && Tabuleiro[2][i] == jogador) Venceu = 1; // Colunas.
        }
        // Verifica diagonais.
        if (Tabuleiro[0][0] == jogador && Tabuleiro[1][1] == jogador && Tabuleiro[2][2] == jogador) Venceu = 1; // Diagonal 1.
        if (Tabuleiro[0][2] == jogador && Tabuleiro[1][1] == jogador && Tabuleiro[2][0] == jogador) Venceu = 1; // Diagonal 2.
        
        if (Venceu) {
            printf("\nJogador %c venceu!!\n", jogador);
            return 0;
        }
        
        jogador = (jogador == 'X') ? 'O' : 'X'; // Troca de jogador.
    }
    
    printf("\nEmpatou!!!\n");
    return 0;
}