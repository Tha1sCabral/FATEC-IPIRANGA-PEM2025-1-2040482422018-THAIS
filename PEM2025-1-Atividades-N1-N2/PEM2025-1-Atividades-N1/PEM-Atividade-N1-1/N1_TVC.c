#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX_CANDIDATOS 50 // Define o número máximo de candidatos permitidos.
#define T_MAX_NOME 100   // Define o tamanho máximo do nome do candidato.
#define TOP15_CLASSIFICADOS 15  // Define o número de candidatos a serem exibidos no ranking final.

//Estrutura para armazenar informações de um candidato, que funciona como uma "planilha".
typedef struct {
    char Nome[T_MAX_NOME];  //Declara o nome do candidato.
    float Notas_PE[4];   // Declara notas da prova escrita.(4 avaliações)
    float Notas_AC[5];  // Declara notas da análise curricular.(5 avaliações)
    float Notas_PP[10]; // Declara notas da prova prática.(10 avaliações)
    float Notas_EB[3];  // Declara notas da entrevista em banca.(3 avaliações)
    float Nota_Final; // Declara nota final calculada.
} Candidato;

// Função para calcular a soma das notas centrais, excluindo a maior e menor.
float Calcular_Soma_Central(float Notas[], int Tamanho) {
    float Soma = 0.0, Maior = Notas[0], Menor = Notas[0];
    int i;
    
    for (i = 0; i < Tamanho; i++) {
        Soma += Notas[i];
        if (Notas[i] > Maior) Maior = Notas[i];
        if (Notas[i] < Menor) Menor = Notas[i];
    }
    return Soma - Maior - Menor;
}

// Função para capturar as notas de um candidato.
void Capturar_Notas(float Notas[], int Tamanho, const char *Nome_Prova) {
    printf("Digite as %d notas da prova %s: ", Tamanho, Nome_Prova);
    int i;
    for ( i = 0; i < Tamanho; i++) {
        scanf("%f", &Notas[i]);// Lê as notas digitadas pelo usuário.
    }
}

// Função para comparar candidatos e organizar por nota final(decrescente).
int Comparar(const void *a, const void *b) {
    float NotaA = ((Candidato*)a)->Nota_Final;
    float NotaB = ((Candidato*)b)->Nota_Final;
    return (NotaA < NotaB) - (NotaA > NotaB);// Retorna a ordem de classificação.
}

int main() {
    Candidato Candidatos[N_MAX_CANDIDATOS];// Vetor para armazenar candidatos.
    int N_Candidatos;

// Solicita o número de candidatos que serão cadastrados.
    printf("Quantos candidatos deseja cadastrar? (Max %d): ", N_MAX_CANDIDATOS);
    scanf("%d", &N_Candidatos);
    // Valida o número de candidatos.
    if (N_Candidatos > N_MAX_CANDIDATOS || N_Candidatos <= 0) {
        printf("Número invalido de candidatos!\n");
        return 1;// Encerra o programa em caso de entrada inválida.
    }

    // Captura os dados de cada candidato.
    int i;
    for ( i = 0; i < N_Candidatos; i++) {
        printf("\nCandidato %d:\n", i + 1);
    // Realiza a leitura dos nomes com tratamento para espaços.
        printf("Nome: ");
        scanf(" %99[^\n]", Candidatos[i].Nome);

 // Captura as notas de cada prova.
 Capturar_Notas(Candidatos[i].Notas_PE, 4, "PE");
 Capturar_Notas(Candidatos[i].Notas_AC, 5, "AC");
 Capturar_Notas(Candidatos[i].Notas_PP, 10, "PP");
 Capturar_Notas(Candidatos[i].Notas_EB, 3, "EB");

 // Calcula somas centrais de cada prova.
 float Soma_PE = Calcular_Soma_Central(Candidatos[i].Notas_PE, 4);
 float Soma_AC = Calcular_Soma_Central(Candidatos[i].Notas_AC, 5);
 float Soma_PP = Calcular_Soma_Central(Candidatos[i].Notas_PP, 10);
 float Soma_EB = Calcular_Soma_Central(Candidatos[i].Notas_EB, 3);

         // Calcula nota final com pesos definidos.
         Candidatos[i].Nota_Final = (Soma_PE * 0.3) + 
         (Soma_AC * 0.1) + 
         (Soma_PP * 0.4) + 
         (Soma_EB * 0.2);
}

// Ordena os candidatos por nota final.(Ordem Decrescente)
    qsort(Candidatos, N_Candidatos, sizeof(Candidato), Comparar);

    // Exibe os 15 melhores candidatos.
    printf("\nTop %d Candidatos:\n", TOP15_CLASSIFICADOS);

  for (i = 0; i < N_Candidatos && i < TOP15_CLASSIFICADOS; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, Candidatos[i].Nome, Candidatos[i].Nota_Final);
    }

    return 0;
}