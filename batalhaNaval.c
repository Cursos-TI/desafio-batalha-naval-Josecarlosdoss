#include <stdio.h>

// =========================================================================
// REQUISITOS NÃO FUNCIONAIS: Definição de Constantes e Tipos
// =========================================================================

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define SUCESSO 1
#define ERRO 0

// Códigos de Orientação
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define DIAGONAL_PRINCIPAL 'P' // Linha e Coluna aumentam (i++, j++)
#define DIAGONAL_SECUNDARIA 'S' // Linha aumenta, Coluna diminui (i++, j--)

// =========================================================================
// FUNÇÕES DE VALIDAÇÃO E POSICIONAMENTO
// =========================================================================

/**
 * Valida se um navio pode ser posicionado no tabuleiro sem sair dos limites, 
 * para qualquer orientação (H, V, P, S).
 * @return SUCESSO (1) se válido, ERRO (0) se fora dos limites.
 */
int validarPosicao(int linha_inicio, int coluna_inicio, char orientacao) {
    if (linha_inicio < 0 || coluna_inicio < 0 || linha_inicio >= TAMANHO_TABULEIRO || coluna_inicio >= TAMANHO_TABULEIRO) {
        return ERRO; // Ponto inicial fora do tabuleiro
    }

    // Verifica os limites para cada orientação específica
    switch (orientacao) {
        case HORIZONTAL:
            return (coluna_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
        case VERTICAL:
            return (linha_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
        case DIAGONAL_PRINCIPAL: // (i+2, j+2)
            return (linha_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
        case DIAGONAL_SECUNDARIA: // (i+2, j-2)
            // A linha aumenta, mas a coluna final deve ser >= 0
            return (linha_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna_inicio - (TAMANHO_NAVIO - 1) >= 0);
        default:
            return ERRO;
    }
}

/**
 * Tenta posicionar um navio no tabuleiro, verificando sobreposição.
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, char orientacao, int id_navio) {
    
    int i;
    int l = linha_inicio;
    int c = coluna_inicio;
    int sobreposicao_detectada = 0;
    
    // Vetores temporários para armazenar as coordenadas a serem ocupadas
    int coords_l[TAMANHO_NAVIO];
    int coords_c[TAMANHO_NAVIO];

    // 1. Calcular coordenadas e checar sobreposição
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        // Define as coordenadas baseadas na orientação
        if (orientacao == HORIZONTAL) {
            coords_l[i] = linha_inicio;
            coords_c[i] = coluna_inicio + i;
        } else if (orientacao == VERTICAL) {
            coords_l[i] = linha_inicio + i;
            coords_c[i] = coluna_inicio;
        } else if (orientacao == DIAGONAL_PRINCIPAL) {
            coords_l[i] = linha_inicio + i;
            coords_c[i] = coluna_inicio + i;
        } else if (orientacao == DIAGONAL_SECUNDARIA) {
            coords_l[i] = linha_inicio + i;
            coords_c[i] = coluna_inicio - i;
        }

        // Verifica se a posição já está ocupada
        if (tabuleiro[coords_l[i]][coords_c[i]] == NAVIO) {
            sobreposicao_detectada = 1;
            break; // Sai do loop se sobrepõe
        }
    }

    // 2. Posicionar de fato se não houver sobreposição
    if (sobreposicao_detectada) {
        printf("[ERRO] Navio %d (L%d, C%d, %c) sobrepoe outro navio. Nao posicionado.\n", 
               id_navio, linha_inicio, coluna_inicio, orientacao);
    } else {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[coords_l[i]][coords_c[i]] = NAVIO;
        }
         printf("[OK] Navio %d (L%d, C%d, %c) posicionado com sucesso.\n", 
                id_navio, linha_inicio, coluna_inicio, orientacao);
    }
}


// =========================================================================
// FUNÇÃO PRINCIPAL
// =========================================================================
int main() {
    int i, j; // Variáveis de controle de loop
    // Requisito: Matriz 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // --- 1. Inicialização do Tabuleiro (com água) ---
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Entrada de Dados (Coordenadas fixas no código) ---
    // Navio 1: Horizontal
    int L1 = 0, C1 = 0; char O1 = HORIZONTAL;
    // Navio 2: Vertical
    int L2 = 5, C2 = 5; char O2 = VERTICAL;
    // Navio 3: Diagonal Principal (Teste OK)
    int L3 = 1, C3 = 6; char O3 = DIAGONAL_PRINCIPAL;
    // Navio 4: Diagonal Secundária (Teste OK)
    int L4 = 7, C4 = 2; char O4 = DIAGONAL_SECUNDARIA;
    // Teste de Erro (Sobreposição com Navio 2):
    int L_E = 6, C_E = 5; char O_E = HORIZONTAL;


    // --- 3. Validação e Posicionamento ---
    printf("Iniciando posicionamento dos navios de tamanho %d...\n", TAMANHO_NAVIO);

    if (validarPosicao(L1, C1, O1)) { posicionarNavio(tabuleiro, L1, C1, O1, 1); }
    else { printf("[ERRO] Coordenadas do Navio 1 (%d, %d, %c) invalidas.\n", L1, C1, O1); }

    if (validarPosicao(L2, C2, O2)) { posicionarNavio(tabuleiro, L2, C2, O2, 2); }
    else { printf("[ERRO] Coordenadas do Navio 2 (%d, %d, %c) invalidas.\n", L2, C2, O2); }

    if (validarPosicao(L3, C3, O3)) { posicionarNavio(tabuleiro, L3, C3, O3, 3); }
    else { printf("[ERRO] Coordenadas do Navio 3 (%d, %d, %c) invalidas.\n", L3, C3, O3); }

    if (validarPosicao(L4, C4, O4)) { posicionarNavio(tabuleiro, L4, C4, O4, 4); }
    else { printf("[ERRO] Coordenadas do Navio 4 (%d, %d, %c) invalidas.\n", L4, C4, O4); }
    
    // Tentativa de posicionar navio que sobrepõe o Navio 2
    if (validarPosicao(L_E, C_E, O_E)) { posicionarNavio(tabuleiro, L_E, C_E, O_E, 5); }
    else { printf("[ERRO] Coordenadas do Navio 5 (%d, %d, %c) invalidas.\n", L_E, C_E, O_E); }


    printf("\n");

    // --- 4. Exibição do Tabuleiro Final ---
    printf("--- Tabuleiro Final (0 = Agua, 3 = Navio) ---\n\n");
    
    // Adiciona cabeçalho de colunas (0 a 9)
    printf("  ");
    for(j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Loop aninhado para exibir o tabuleiro formatado
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Adiciona rótulo de linha
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Usa largura fixa de 1 caractere para alinhamento
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }

    return 0;
}
