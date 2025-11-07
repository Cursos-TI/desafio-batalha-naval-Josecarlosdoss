#include <stdio.h>

//  Definição de Constantes e Tipos

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define SUCESSO 1
#define ERRO 0

// FUNÇÕES DE VALIDAÇÃO E POSICIONAMENTO
/**
 * Valida se um navio pode ser posicionado no tabuleiro sem sair dos limites.
 * Simplificação: A sobreposição é verificada no momento do posicionamento.
 * @return SUCESSO (1) se válido, ERRO (0) se fora dos limites.
 */
int validarPosicao(int linha_inicio, int coluna_inicio, int orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna_inicio >= 0 && coluna_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
            linha_inicio >= 0 && linha_inicio < TAMANHO_TABULEIRO) {
            return SUCESSO;
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha_inicio >= 0 && linha_inicio + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
            coluna_inicio >= 0 && coluna_inicio < TAMANHO_TABULEIRO) {
            return SUCESSO;
        }
    }
    return ERRO;
}

/**
 * Tenta posicionar um navio no tabuleiro. Se houver sobreposição, imprime um erro.
 * A sobreposição é trivialmente verificada tentando sobrescrever um local já ocupado.
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, int orientacao) {
    
    int i, j;
    int sobreposicao_detectada = 0;

    if (orientacao == 'H') {
        for (j = 0; j < TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha_inicio][coluna_inicio + j] == NAVIO) {
                sobreposicao_detectada = 1;
                break; // Sai do loop de posicionamento se sobrepõe
            }
        }
        // Se não houve sobreposição, posiciona de fato
        if (!sobreposicao_detectada) {
            for (j = 0; j < TAMANHO_NAVIO; j++) {
                tabuleiro[linha_inicio][coluna_inicio + j] = NAVIO;
            }
        }

    } else if (orientacao == 'V') {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_inicio + i][coluna_inicio] == NAVIO) {
                sobreposicao_detectada = 1;
                break; // Sai do loop de posicionamento se sobrepõe
            }
        }
        // Se não houve sobreposição, posiciona de fato
        if (!sobreposicao_detectada) {
             for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_inicio + i][coluna_inicio] = NAVIO;
            }
        }
    }

    if (sobreposicao_detectada) {
        // Exibe erro no console caso a sobreposição ocorra
        printf("[ERRO] Sobreposicao detectada para o navio em (%d, %d, %c). Navio nao posicionado.\n", 
               linha_inicio, coluna_inicio, orientacao);
    }
}


// FUNÇÃO PRINCIPAL
int main() {
    int i, j; // Variáveis de controle de loop
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // --- 1. Inicialização do Tabuleiro ---
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Entrada de Dados (Coordenadas fixas no código) ---
    // Navio 1: Horizontal, começa em (Linha 2, Coluna 1)
    int L1 = 2, C1 = 1; 
    char O1 = 'H';
    // Navio 2: Vertical, começa em (Linha 5, Coluna 5)
    int L2 = 5, C2 = 5; 
    char O2 = 'V';
    // Navio 3 (Teste de Sobreposição/Erro): Horizontal, começa em (Linha 5, Coluna 4)
    // Este navio deveria se sobrepor ao Navio 2.
    int L3 = 5, C3 = 4;
    char O3 = 'H';


    // --- 3. Validação e Posicionamento ---

    printf("Iniciando posicionamento dos navios...\n");

    // Validação e Posicionamento do Navio 1
    if (validarPosicao(L1, C1, O1)) {
        posicionarNavio(tabuleiro, L1, C1, O1);
        printf("[OK] Navio 1 posicionado.\n");
    } else {
        printf("[ERRO] Coordenadas do Navio 1 (%d, %d) invalidas.\n", L1, C1);
    }

    // Validação e Posicionamento do Navio 2
    if (validarPosicao(L2, C2, O2)) {
        posicionarNavio(tabuleiro, L2, C2, O2);
         printf("[OK] Navio 2 posicionado.\n");
    } else {
        printf("[ERRO] Coordenadas do Navio 2 (%d, %d) invalidas.\n", L2, C2);
    }
    
    // Teste de validação de sobreposição/limite
    if (validarPosicao(L3, C3, O3)) {
        // Esta chamada irá detectar e reportar a sobreposição dentro da função
        posicionarNavio(tabuleiro, L3, C3, O3); 
    } else {
         printf("[ERRO] Coordenadas do Navio 3 (%d, %d) invalidas/fora do limite.\n", L3, C3);
    }
    
    printf("\n");

    // --- 4. Exibição do Tabuleiro Final ---
    printf("--- Tabuleiro Final (0 = Agua, 3 = Navio) ---\n\n");
    
    // Loop aninhado para exibir o tabuleiro formatado
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }

    return 0;
}
