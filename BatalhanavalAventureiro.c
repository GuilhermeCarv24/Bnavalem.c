#include <stdio.h>

#define TAM 10
#define NAVIO 3

// Inicializa o tabuleiro com 0
void inicializartabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se pode colocar o navio sem sair do tabuleiro ou sobrepor
int podecolocar(int tabuleiro[TAM][TAM], int linha, int coluna, int direcao, int diagonal) {
    for (int k = 0; k < NAVIO; k++) {
        int x = linha;
        int y = coluna;

        if (diagonal == 0) {
            if (direcao == 0) y += k;     // horizontal
            else x += k;                  // vertical
        } else {
            if (direcao == 0) {           // diagonal principal
                x += k;
                y += k;
            } else {                      // diagonal secundária
                x += k;
                y -= k;
            }
        }

        if (x < 0 || x >= TAM || y < 0 || y >= TAM || tabuleiro[x][y] != 0)
            return 0;
    }
    return 1;
}

// Coloca o navio no tabuleiro
void colocarnavio(int tabuleiro[TAM][TAM], int linha, int coluna, int direcao, int diagonal) {
    for (int k = 0; k < NAVIO; k++) {
        int x = linha;
        int y = coluna;

        if (diagonal == 0) {
            if (direcao == 0) y += k;
            else x += k;
        } else {
            if (direcao == 0) {
                x += k;
                y += k;
            } else {
                x += k;
                y -= k;
            }
        }

        tabuleiro[x][y] = 3; // marca navio
    }
}

// Imprime o tabuleiro na tela
void imprimirtabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializartabuleiro(tabuleiro);

    if (podecolocar(tabuleiro, 0, 0, 0, 0))
        colocarnavio(tabuleiro, 0, 0, 0, 0);

    if (podecolocar(tabuleiro, 2, 2, 1, 0))
        colocarnavio(tabuleiro, 2, 2, 1, 0);

    if (podecolocar(tabuleiro, 4, 0, 0, 1))
        colocarnavio(tabuleiro, 4, 0, 0, 1);

    if (podecolocar(tabuleiro, 0, 9, 1, 1))
        colocarnavio(tabuleiro, 0, 9, 1, 1);

    imprimirtabuleiro(tabuleiro);

    return 0;
}
