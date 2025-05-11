/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: BubbleSort                 :)    *
* Data - 10/05/2025                                      * 
* Autor: Thaís Cabral;       '-'                         *
*--------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *vetor, int tamanho);
void exibir_numeros(int *vetor, int tamanho);

int main() {
    int quantidade,*numeros;
    
    printf("Digite a quantidade de numeros para serem ordenados: ");
    scanf("%d", &quantidade);
// Alocando memoria para o vetor.
    numeros = (int *) malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        printf("Erro na alocacao de memoria\n");
        return 1;
    }
//Leitura e aplicação do bubble sort.
    printf("Digite os %d numeros:\n", quantidade);
    int i=0;
    for (i = 0; i < quantidade; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }
    printf("\nOrdenando usando Bubble Sort...\n");
    bubble_sort(numeros, quantidade);

    printf("\nNumeros em ordem ascendente:\n");
    exibir_numeros(numeros, quantidade);
// Liberar memória alocada
    free(numeros);
    return 0;
}
// Implementação do Bubble Sort usando ponteiro
void bubble_sort(int *vetor, int tamanho) {
    int temp, i = 0;
    for (i = 0; i < tamanho - 1; i++) {
        int j = 0;
        for (j = 0; j < tamanho - i - 1; j++) {
            if (*(vetor + j) > *(vetor + j + 1)) {
                temp = *(vetor + j);
                *(vetor + j) = *(vetor + j + 1);
                *(vetor + j + 1) = temp;
            }
        }
    }
}
//Exibicao do vetor.
void exibir_numeros(int *vetor, int tamanho) {
    int i= 0;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", *(vetor + i));
    }
    printf("\n");
}
