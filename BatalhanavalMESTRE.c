#include <stdio.h>

#define TAM 10
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

#define M 5

// Inicializa o tabuleiro com água
void inicializatabuleiro(int TAB[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            TAB[i][j] = AGUA;
        }
    }
}

// Posiciona navios de exemplo
void posicionanaviosexemplo(int TAB[TAM][TAM]) {
    TAB[1][3] = NAVIO; TAB[1][4] = NAVIO; TAB[1][5] = NAVIO;
    TAB[6][7] = NAVIO; TAB[7][7] = NAVIO; TAB[8][7] = NAVIO;
}

// Máscara em cruz
void construirmascaracruz(int mask[M][M]) {
    int centro = M / 2;
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            mask[r][c] = (r == centro || c == centro) ? 1 : 0;
        }
    }
}

// Máscara em octaedro (losango)
void construirmascaraoctaedro(int mask[M][M]) {
    int centro = M / 2;
    int raio = centro;
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            int manhattan1 = (r - centro);
            if (manhattan1 < 0) manhattan1 = -manhattan1;
            int manhattan2 = (c - centro);
            if (manhattan2 < 0) manhattan2 = -manhattan2;
            mask[r][c] = (manhattan1 + manhattan2 <= raio) ? 1 : 0;
        }
    }
}

// Máscara em cone (triângulo para baixo)
void construirmascaracone(int mask[M][M]) {
    int centro = M / 2;
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            int half = r;
            int cmin = centro - half;
            int cmax = centro + half;
            mask[r][c] = (c >= cmin && c <= cmax) ? 1 : 0;
        }
    }
}

// Aplica máscara no tabuleiro
void aplicarmascaranotabuleiro(int TAB[TAM][TAM], int mask[M][M], int origemlinha, int origemcoluna) {
    int centro = M / 2;
    int iniciolinha = origemlinha - centro;
    int iniciocoluna = origemcoluna - centro;

    for (int mr = 0; mr < M; mr++) {
        for (int mc = 0; mc < M; mc++) {
            if (mask[mr][mc] == 0) continue;

            int br = iniciolinha + mr;
            int bc = iniciocoluna + mc;

            if (br < 0 || br >= TAM || bc < 0 || bc >= TAM) continue;

            if (TAB[br][bc] != NAVIO) {
                TAB[br][bc] = AFETADO;
            }
        }
    }
}

// Imprime o tabuleiro
void imprimirtabuleiro(int TAB[TAM][TAM]) {
    printf("\nLegenda: .= água (0), N = navio (3), *= área (5)\n\n");

    printf("   ");
    for (int c = 0; c < TAM; c++) printf("%2d", c);
    printf("\n");

    for (int r = 0; r < TAM; r++) {
        printf("%2d ", r);
        for (int c = 0; c < TAM; c++) {
            char ch = '.';
            if (TAB[r][c] == NAVIO) ch = 'N';
            else if (TAB[r][c] == AFETADO) ch = '*';
            printf(" %c", ch);
        }
        printf("\n");
    }
}

int main(void) {
    int tab[TAM][TAM];
    inicializatabuleiro(tab);
    posicionanaviosexemplo(tab);

    int cone[M][M];
    int cruz[M][M];
    int octaedro[M][M];

    construirmascaracone(cone);
    construirmascaracruz(cruz);
    construirmascaraoctaedro(octaedro);

    int origemconelinha = 2, origemcolunacone = 2;
    int origemcruzlinha = 4, origemcruzcoluna = 4;
    int origemoctaedrolinha = 7, origemoctaedrocoluna = 7;

    aplicarmascaranotabuleiro(tab, cone, origemconelinha, origemcolunacone);
    aplicarmascaranotabuleiro(tab, cruz, origemcruzlinha, origemcruzcoluna);
    aplicarmascaranotabuleiro(tab, octaedro, origemoctaedrolinha, origemoctaedrocoluna);

    imprimirtabuleiro(tab);

    return 0;
}