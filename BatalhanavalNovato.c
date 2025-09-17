#include <stdio.h>

#define TAM 10
#define NAVIO 3

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // Inicializa tabuleiro com 0
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Coordenadas dos navios
    int linhanavioH = 4;
    int colunanavioH = 2;
    int linhanavioV = 5;
    int colunanavioV = 6;

    // ---- NAVIO HORIZONTAL ----
    if (colunanavioH + NAVIO <= TAM) {
        for (j = colunanavioH; j < colunanavioH + NAVIO; j++) {
            tabuleiro[linhanavioH][j] = 3;
        }
    } else {
        printf("ERRO: navio horizontal fora do tabuleiro\n");
        return 1;
    }

    // ---- NAVIO VERTICAL ----
    if (linhanavioV + NAVIO <= TAM) {
        for (i = linhanavioV; i < linhanavioV + NAVIO; i++) {
            if (tabuleiro[i][colunanavioV] == 0) { // checa sobreposição
                tabuleiro[i][colunanavioV] = 3;
            } else {
                printf("ERRO: sobreposição de navios detectada!!\n");
                return 1;
            }
        }
    } else {
        printf("ERRO: navio vertical fora dos limites!!\n");
        return 1;
    }

    // ---- EXIBIR TABULEIRO ----
    printf("\nTabuleiro de Batalha Naval:\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
