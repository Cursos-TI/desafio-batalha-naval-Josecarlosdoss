#include <stdio.h>
#include <math.h> // Necessário para a função abs() na lógica do Octaedro

// =========================================================================
// Definição de Constantes e Tipos
// =========================================================================

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5 // Tamanho fixo para as matrizes de habilidade (5x5)
#define AGUA 0
#define NAVIO 3
#define EFEITO_HABILIDADE 5
#define SUCESSO 1
#define ERRO 0
#define CENTRO_HAB (TAMANHO_HABILIDADE / 2) // Índice central da matriz de habilidade (2 para 5x5)

// Códigos de Orientação 
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define DIAGONAL_PRINCIPAL 'P'
#define DIAGONAL_SECUNDARIA 'S'


/**
 * Cria a matriz de habilidade em forma de CONE dinamicamente.
 * O cone aponta para baixo a partir do topo.
 */
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    for (i = 0; i < TAMANHO_HABILIDADE; i++) { // i = linha (distância do topo)
        for (j = 0; j < TAMANHO_HABILIDADE; j++) { // j = coluna
            // Condicional: A área afetada (1) expande com a linha (i)
            // A largura do cone na linha 'i' é 2*i + 1
            if (j >= CENTRO_HAB - i && j <= CENTRO_HAB + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em forma de CRUZ dinamicamente.
 */
void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condicional: Atinge a linha central OU a coluna central
            if (i == CENTRO_HAB || j == CENTRO_HAB) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em forma de OCTAEDRO (losango) dinamicamente.
 *  (|x| + |y| <= raio).
 */
void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    // O "raio" máximo para um 5x5 centrado em (2,2) é 2.
    int raio = CENTRO_HAB; 

    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a distância de Manhattan do ponto (i, j) ao centro (CENTRO_HAB, CENTRO_HAB)
            int distancia = abs(i - CENTRO_HAB) + abs(j - CENTRO_HAB);
            
            // Condicional: Se a distância for menor ou igual ao raio, está dentro do losango
            if (distancia <= raio) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * Aplica a matriz de habilidade sobre o tabuleiro principal.
 * Usa condicionais para garantir que a sobreposição permaneça dentro dos limites do tabuleiro.
 */
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        int origem_l, int origem_c) {
    int i, j;
    
    // Iteração sobre a matriz de habilidade (i_habil, j_habil)
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a posição correspondente no tabuleiro principal (l_tab, c_tab)
            // Centra a habilidade no ponto de origem dado
            int l_tab = origem_l + (i - CENTRO_HAB);
            int c_tab = origem_c + (j - CENTRO_HAB);

            // Condicional: Verifica se a coordenada calculada está DENTRO dos limites do tabuleiro 10x10
            if (l_tab >= 0 && l_tab < TAMANHO_TABULEIRO &&
                c_tab >= 0 && c_tab < TAMANHO_TABULEIRO) {
                
                // Condicional: Se a posição na matriz de habilidade for afetada (1)
                if (habilidade[i][j] == 1) {
                    // Aplica o efeito visual (5) no tabuleiro principal
                    // Nota: Sobrescreve navios se eles estiverem na área de efeito.
                    tabuleiro[l_tab][c_tab] = EFEITO_HABILIDADE;
                }
            }
        }
    }
}

/**
 * Exibe o tabuleiro formatado, usando caracteres visuais para melhor legibilidade.
 */
void exibirTabuleiroVisual(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;

    printf("--- Tabuleiro Final (Visao Visual) ---\n");
    printf("~ = Agua (0), # = Navio (3), X = Habilidade (5)\n\n");
    
    // Cabeçalho de colunas
    printf("  ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Loop aninhado para exibir o tabuleiro formatado
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Rótulo de linha
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Usa condicionais para escolher o caractere de saída
            if (tabuleiro[i][j] == AGUA) {
                printf("~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("# ");
            } else if (tabuleiro[i][j] == EFEITO_HABILIDADE) {
                printf("X ");
            } else {
                // Caso inesperado
                printf("? ");
            }
        }
        printf("\n");
    }
}


// =========================================================================
// FUNÇÃO PRINCIPAL
// =========================================================================
int main() {
    int i, j;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Matrizes de habilidade 5x5 que serão preenchidas dinamicamente
    int mat_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int mat_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int mat_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];


    // --- 1. Inicialização do Tabuleiro Principal (Água) ---
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Posicionamento de Navios 
    tabuleiro[2][1] = NAVIO; tabuleiro[2][2] = NAVIO; tabuleiro[2][3] = NAVIO; // Navio H
    tabuleiro[5][5] = NAVIO; tabuleiro[6][5] = NAVIO; tabuleiro[7][5] = NAVIO; // Navio V


    // --- 3. Geração Dinâmica das Matrizes de Habilidade ---
    criarCone(mat_cone);
    criarCruz(mat_cruz);
    criarOctaedro(mat_octaedro);
    
    // --- 4. Definição dos Pontos de Origem no Tabuleiro Principal ---
    int origem_cone_l = 2, origem_cone_c = 8; // Canto superior direito
    int origem_cruz_l = 5, origem_cruz_c = 2; // Centro esquerda
    int origem_octa_l = 8, origem_octa_c = 8; // Canto inferior direito

    // --- 5. Sobreposição das Habilidades no Tabuleiro Principal ---
    printf("Aplicando habilidades no tabuleiro...\n");
    sobreporHabilidade(tabuleiro, mat_cone, origem_cone_l, origem_cone_c);
    sobreporHabilidade(tabuleiro, mat_cruz, origem_cruz_l, origem_cruz_c);
    sobreporHabilidade(tabuleiro, mat_octaedro, origem_octa_l, origem_octa_c);
    printf("Habilidades aplicadas.\n\n");


    // --- 6. Exibição do Tabuleiro com Habilidades ---
    exibirTabuleiroVisual(tabuleiro);

    return 0;
}
