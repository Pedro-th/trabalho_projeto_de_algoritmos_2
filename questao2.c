#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para verificar se uma permutação dada é possível em uma pilha
bool validar_permutacao_pilha(int permutacao[], int n) {
    int pilha[10]; // Pilha para simular (tamanho 10 é suficiente para n=4)
    int topo = -1; // Topo da pilha (-1 indica vazia)
    
    int proximo_a_entrar = 1; // Elementos chegam estritamente na ordem 1, 2, 3, 4
    
    for (int i = 0; i < n; i++) {
        int elemento_esperado = permutacao[i];
        
        // Se o elemento esperado não está no topo, empilhamos os próximos 
        // da sequência de entrada até encontrá-lo
        while (proximo_a_entrar <= n && (topo == -1 || pilha[topo] != elemento_esperado)) {
            topo++;
            pilha[topo] = proximo_a_entrar;
            proximo_a_entrar++; // Incrementa para o próximo elemento da entrada
        }
        
        // Verifica se o topo é de fato o elemento que queremos desempilhar
        if (topo != -1 && pilha[topo] == elemento_esperado) {
            topo--; // Desempilha (POP)
        } else {
            // Caso contrário, a permutação exige um desempilhamento inválido
            return false;
        }
    }
    
    // Se no final todos os elementos foram removidos corretamente, a pilha deve estar vazia
    return topo == -1;
}

// Função principal que gera e testa todas as permutações utilizando o Algoritmo de Heap
void testar_todas_permutacoes() {
    int n = 4;
    int permutacao[] = {1, 2, 3, 4};
    int total_validas = 0;
    int total_invalidas = 0;

    printf("--- Validacao de Permutacoes (Pilha n=4) ---\n\n");
    
    // Algoritmo de Heap para gerar todas as 24 permutações
    int controle[4] = {0, 0, 0, 0};
    
    // Testa a permutação inicial (1, 2, 3, 4)
    if(validar_permutacao_pilha(permutacao, n)) {
        printf("VALIDA:   %d, %d, %d, %d\n", permutacao[0], permutacao[1], permutacao[2], permutacao[3]);
        total_validas++;
    } else {
        printf("INVALIDA: %d, %d, %d, %d\n", permutacao[0], permutacao[1], permutacao[2], permutacao[3]);
        total_invalidas++;
    }

    int i = 0;
    while (i < n) {
        if (controle[i] < i) {
            if (i % 2 == 0) {
                // Troca o primeiro com o i-ésimo
                int temp = permutacao[0];
                permutacao[0] = permutacao[i];
                permutacao[i] = temp;
            } else {
                // Troca o controle com o i-ésimo
                int temp = permutacao[controle[i]];
                permutacao[controle[i]] = permutacao[i];
                permutacao[i] = temp;
            }
            
            // Testa a permutação gerada
            if(validar_permutacao_pilha(permutacao, n)) {
                printf("VALIDA:   %d, %d, %d, %d\n", permutacao[0], permutacao[1], permutacao[2], permutacao[3]);
                total_validas++;
            } else {
                printf("INVALIDA: %d, %d, %d, %d\n", permutacao[0], permutacao[1], permutacao[2], permutacao[3]);
                total_invalidas++;
            }
            
            controle[i] += 1;
            i = 0;
        } else {
            controle[i] = 0;
            i += 1;
        }
    }
    
    printf("\n--- RESULTADO FINAL ---\n");
    printf("Total de Sequencias Validas: %d\n", total_validas);
    printf("Total de Sequencias Invalidas: %d\n", total_invalidas);
}

int main() {
    testar_todas_permutacoes();
    return 0;
}
