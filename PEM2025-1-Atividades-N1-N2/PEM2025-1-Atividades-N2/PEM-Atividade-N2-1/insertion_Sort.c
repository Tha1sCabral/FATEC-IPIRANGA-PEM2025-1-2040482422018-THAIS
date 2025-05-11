/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: InsetionSort               :)    *
* Data - 10/05/2025                                      * 
* Autor: Thaís Cabral;       '-'                         *
*--------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *vetor, int tamanho);
void mostrar_vetor(int *vetor, int tamanho);

int main() {
    int tamanho;
    int *numeros;
       
    printf("Digite a quantidade de numeros para serem ordenados: ");
    scanf("%d", &tamanho);
    
    numeros = (int *) malloc(tamanho * sizeof(int));
    if (numeros == NULL) {
        printf("Erro na alocacao de memoria\n");
        return 1;
    }
    
    printf("Digite os %d numeros:\n", tamanho);
    int i = 0;
    for (i = 0; i < tamanho; i++) {
        printf("Numero %d: ", i+1);
        scanf("%d", &numeros[i]);
    }
    
// Aplicar o Insertion Sort e exibição dos números.
    printf("\nOrdenando usando Insertion Sort...\n");
    insertionSort(numeros, tamanho);
    printf("\nNumeros em ordem ascendente:\n");
    mostrar_vetor(numeros, tamanho);
    
// Liberar memória alocada
    free(numeros);
    
    return 0;
}

// Implementação do Insertion Sort com uso de ponteiros
void insertionSort(int *vetor, int tamanho) {
    int valor_atual, posicao, i=1;
    
    for (i = 1; i < tamanho; i++) {
// Valor atual a ser comparado
        valor_atual = *(vetor + i);
        posicao = i - 1;
        
// Movimentação dos valores do vetor que são maiores que valor_atual, para uma posicao a frente.
        while (posicao >= 0 && *(vetor + posicao) > valor_atual) {
            *(vetor + posicao + 1) = *(vetor + posicao);
            posicao = posicao - 1;
        }
        *(vetor + posicao + 1) = valor_atual;
    }
}
// exibicao do vetor
void mostrar_vetor(int *vetor, int tamanho) {
    int i = 0;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", *(vetor + i));
    }
    printf("\n");
}
