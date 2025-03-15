/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Vetor Multidimensional modular   *
* Data - 14/03/2025                                      * 
* Autor: Thaís Cabral;       '-'                         *
*--------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define RUAS_TOTAL 3
#define GONDOLAS_TOTAL 10
#define CODIGO_PRODUTO_TAMANHO 5
#define CODIGO_PRODUTO_VALIDO 4
// * Estrutura para armazenar informações de um produto
typedef struct
{
    char codigo[CODIGO_PRODUTO_TAMANHO];
    int quantidade;
} Produto;
// Estrutura para representar todo o estoque
typedef struct
{
    Produto matriz[RUAS_TOTAL][GONDOLAS_TOTAL];
} Estoque;
// Protótipos das funções
void inicializarEstoque(Estoque *estoque);
bool validarCodigoProduto(const char *codigo);
bool validarPosicao(int rua, int gondola);
void cadastrarProduto(Estoque *estoque);
void mostrarRelatorio(const Estoque *estoque);
int encontrarProduto(const Estoque *estoque, const char *codigo, int *rua, int *gondola);
void adicionarQuantidade(Estoque *estoque, int rua, int gondola, int quantidade);
void inserirNovoProduto(Estoque *estoque, int rua, int gondola, const char *codigo, int quantidade);

// Função principal
int main()
{
    // Alocação do estoque
    Estoque *estoque = (Estoque *)malloc(sizeof(Estoque));

    if (estoque == NULL)
    {
        printf("Erro: Falha na alocacao de memoria para o estoque\n");
        return 1;
    }
    // Inicialização e execução do programa
    inicializarEstoque(estoque);
    cadastrarProduto(estoque);

    // Liberação da memória alocada
    free(estoque);
    return 0;
}

// Inicializa o estoque, zerando todas as posições
void inicializarEstoque(Estoque *estoque)
{
    int rua = 0, gondola = 0;
    for (rua = 0; rua < RUAS_TOTAL; rua++)
    {
        for (gondola = 0; gondola < GONDOLAS_TOTAL; gondola++)
        {
            estoque->matriz[rua][gondola].codigo[0] = '\0';
            estoque->matriz[rua][gondola].quantidade = 0;
        }
    }
}
// Valida se o código do produto segue o padrão (letra maiúscula + 3 números)
bool validarCodigoProduto(const char *codigo)
{
    // Verificar tamanho
    if (strlen(codigo) != CODIGO_PRODUTO_VALIDO)
    {
        return false;
    }

    // Verificar se o primeiro caractere é uma letra maiúscula
    if (!isupper(codigo[0]))
    {
        return false;
    }

    // Verificar se os 3 caracteres seguintes são dígitos
    int i = 1;
    for (i = 1; i < CODIGO_PRODUTO_VALIDO; i++)
    {
        if (!isdigit(codigo[i]))
        {
            return false;
        }
    }

    return true;
}

// Valida se a posição (rua, gôndola) está dentro dos limites permitidos

bool validarPosicao(int rua, int gondola)
{
    if (rua < 0 || rua >= RUAS_TOTAL || gondola < 0 || gondola >= GONDOLAS_TOTAL)
    {
        printf("Erro: Posicao invalida. Ruas validas: 1-%d, Gondolas validas: 1-%d\n",
               RUAS_TOTAL, GONDOLAS_TOTAL);
        return false;
    }
    return true;
}

/*Procura um produto no estoque pelo código
 * Retorna 1 se encontrado, 0 caso contrário
 * Os parâmetros rua e gondola são preenchidos com a posição encontrada*/

int encontrarProduto(const Estoque *estoque, const char *codigo, int *rua, int *gondola)
{
    int r = 0, g = 0;
    for (r = 0; r < RUAS_TOTAL; r++)
    {
        for (g = 0; g < GONDOLAS_TOTAL; g++)
        {
            if (strcmp(estoque->matriz[r][g].codigo, codigo) == 0)
            {
                *rua = r;
                *gondola = g;
                return 1;
            }
        }
    }
    return 0;
}

// Adiciona uma quantidade ao produto existente

void adicionarQuantidade(Estoque *estoque, int rua, int gondola, int quantidade)
{
    if (quantidade <= 0)
    {
        printf("Erro: A quantidade deve ser maior que zero!\n");
        return;
    }

    estoque->matriz[rua][gondola].quantidade += quantidade;
    printf("Quantidade atualizada! Produto %s agora tem %d unidades na rua %d, gondola %d.\n",
           estoque->matriz[rua][gondola].codigo,
           estoque->matriz[rua][gondola].quantidade,
           rua + 1, gondola + 1);
}

// Insere um novo produto no estoque

void inserirNovoProduto(Estoque *estoque, int rua, int gondola, const char *codigo, int quantidade)
{
    if (quantidade <= 0)
    {
        printf("Erro: A quantidade deve ser maior que zero!\n");
        return;
    }

    if (estoque->matriz[rua][gondola].quantidade > 0)
    {
        printf("Erro: A gondola %d da rua %d ja esta ocupada!\n", gondola + 1, rua + 1);
        return;
    }

    strcpy(estoque->matriz[rua][gondola].codigo, codigo);
    estoque->matriz[rua][gondola].quantidade = quantidade;
    printf("Produto %s cadastrado com sucesso na rua %d, gondola %d com %d unidades!\n",
           codigo, rua + 1, gondola + 1, quantidade);
}

// Função principal para cadastrar produtos no estoque

void cadastrarProduto(Estoque *estoque)
{
    char codigo[CODIGO_PRODUTO_TAMANHO];
    int quantidade, rua, gondola;
    char continuar;

    // Solicitar código do produto
    printf("Digite o codigo do produto (Ex: A123): ");
    scanf("%s", codigo);

    // Validar formato do código
    if (!validarCodigoProduto(codigo))
    {
        printf("Erro: Codigo de produto invalido! Use uma letra maiuscula seguida de 3 numeros (Ex: A123).\n");
        return;
    }

    // Verificar se o produto já existe
    int produtoEncontrado = encontrarProduto(estoque, codigo, &rua, &gondola);

    if (produtoEncontrado)
    {
        printf("Produto %s ja cadastrado na rua %d, gondola %d.\n", codigo, rua + 1, gondola + 1);
        printf("Informe a quantidade adicional a ser somada: ");
        scanf("%d", &quantidade);

        adicionarQuantidade(estoque, rua, gondola, quantidade);
    }
    else
    {
        // Solicitar posição para novo produto
        printf("Informe a Rua e a gondola para armazenar o produto %s: ", codigo);
        scanf("%d %d", &rua, &gondola);
        rua--;
        gondola--; // Ajuste para índices baseados em 0

        if (!validarPosicao(rua, gondola))
        {
            return;
        }

        printf("Informe a quantidade inicial do produto %s: ", codigo);
        scanf("%d", &quantidade);

        inserirNovoProduto(estoque, rua, gondola, codigo, quantidade);
    }

    // Verificar se deseja cadastrar outro produto
    printf("Deseja cadastrar outro produto? (S/N): ");
    scanf(" %c", &continuar);

    if (continuar == 'S' || continuar == 's')
    {
        cadastrarProduto(estoque);
    }
    else
    {
        printf("Cadastro finalizado. Exibindo relatorio final:\n");
        mostrarRelatorio(estoque);
    }
}

// Mostra o relatório de todos os produtos cadastrados no estoque

void mostrarRelatorio(const Estoque *estoque)
{
    printf("=== RELATORIO DE PRODUTOS CADASTRADOS ===\n");
    int produtosEncontrados = 0, rua;

    for (rua = 0; rua < RUAS_TOTAL; rua++)
    {
        int gondola = 0;
        for (gondola = 0; gondola < GONDOLAS_TOTAL; gondola++)
        {
            if (estoque->matriz[rua][gondola].quantidade > 0)
            {
                printf("Rua %d, Gondola %d - Produto: %s, Quantidade: %d\n",
                       rua + 1, gondola + 1,
                       estoque->matriz[rua][gondola].codigo,
                       estoque->matriz[rua][gondola].quantidade);
                produtosEncontrados++;
            }
        }
    }

    if (produtosEncontrados == 0)
    {
        printf("Nenhum produto cadastrado no estoque.\n");
    }
    printf("====================================================\n");
}