#include <stdio.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

//Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]){
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    printf("    ");
    for (int j = 0; j < TAM; j++) printf("%2d ", j);
    printf("\n");
    printf("   -----------------------------------------\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(" ~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf(" N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" * ");
            else
                printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para construir matriz de habilidade CONE
void habilidadeCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

//Função para construir matriz de habilidade CRUZ
void habilidadeCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

//Funçao para construir matriz de habilidade LOSANGO
void habilidadeLosango(int matriz [TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

//Aplica uma matriz de habilidade no tabuleiro, centrando-a na origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int hab[TAM_HAB][TAM_HAB],int origemLinha, int origemColuna ) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int linha = origemLinha + (i - offset);
                int coluna = origemColuna + (j - offset);

                //Verificar limites do tabuleiro
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    //Marca a área afetada com valor 5, mas não sobrescreve navio 
                    if (tabuleiro[linha][coluna] == AGUA)
                        tabuleiro[linha][coluna] = HABILIDADE;
                }

            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    //Posiciona alguns navios
    tabuleiro[2][2] = NAVIO;
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    tabuleiro[8][7] = NAVIO;

    //Cria as três matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int losango[TAM_HAB][TAM_HAB];

    habilidadeCone(cone);
    habilidadeCruz(cruz);
    habilidadeLosango(losango);
    
    //Define pontos de origem no tabuleiro (centro de habilidades)
    int origemConeLinha = 3, origemConeColuna = 5;
    int origemCruzLinha = 7, origemCruzColuna = 2;
    int origemLosangoLinha = 5, OrigemLosangoColuna = 8;

    //Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, losango, origemLosangoLinha, OrigemLosangoColuna);

    //Exibe o tabuleiro final com as áreas afetadas
    exibirTabuleiro(tabuleiro);

    return 0;
}
