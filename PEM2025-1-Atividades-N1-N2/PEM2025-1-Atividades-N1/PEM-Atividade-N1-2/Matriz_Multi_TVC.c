/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Vetor  Multidimensional          *
* Data - 06/03/2025                                      * 
* Autor: Thaís Cabral;       '-'                         *
*--------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define RUAS_TOTAL 3
#define GONDOLAS_TOTAL 10
#define CODIGO_PRODUTO_SIZE 5

void Mostrar_Relatorio_Final();
int Validar_Posicao(int Rua, int Gondola);

// Estrutura para armazenar um produto no estoque
typedef struct
{
    char Codigo_Produto[CODIGO_PRODUTO_SIZE]; // Código do produto (ex: X123)
    int Quantidade;
} Produto;

// Matriz tridimensional para o estoque (Rua x Gôndola)
Produto Estoque[RUAS_TOTAL][GONDOLAS_TOTAL];

// Função para inicializar o estoque
void Iniciar_Estoque()
{
    int Rua = 0, Gondola = 0;
    for (Rua = 0; Rua < RUAS_TOTAL; Rua++)
    {
        for (Gondola = 0; Gondola < GONDOLAS_TOTAL; Gondola++)
        {
            strcpy(Estoque[Rua][Gondola].Codigo_Produto, "");
            Estoque[Rua][Gondola].Quantidade = 0;
        }
    }
}

// Função para validar código do produto (deve começar com letra maiúscula e ter 3 números)
int Validar_Cod_Produto(const char *codigo)
{
    if (strlen(codigo) != 4)
        return 0; // Deve ter exatamente 4 caracteres
    if (!isupper(codigo[0]))
        return 0; // Primeiro caractere deve ser uma letra maiúscula (A-Z)
        int i = 1;
    for (i = 1; i < 4; i++)
    {
        if (!isdigit(codigo[i]))
            return 0; // Os 3 últimos devem ser números
    }
    return 1; // Código válido
}

// Função para validar posição da gôndola
int Validar_Posicao(int Rua, int Gondola) {
    if (Rua < 0 || Rua >= RUAS_TOTAL || Gondola < 0 || Gondola >= GONDOLAS_TOTAL) {
        printf("Erro!!! A posição informada é invAlida.\n");
        return 0;
    }
    return 1;
}

// Função para cadastrar um novo produto no estoque
void CadastrarProduto() {
    char Codigo_Produto[CODIGO_PRODUTO_SIZE];
    int Quantidade;
    int Rua = -1, Gondola = -1;
    
    // Solicitar código do produto ao usuário
    printf("Digite o codigo do produto (Ex: A123): ");
    scanf("%s", Codigo_Produto);
    
    // Verificar se o código segue o padrão correto (Letra + 3 números)
    if (!Validar_Cod_Produto(Codigo_Produto)) {
        printf("Erro!!! Codigo do produto invalido! Deve seguir o padrao letra maiuscula seguida de tres numeros (Ex: A123).\n");
        return;
    }

    // Verificar se o produto já está cadastrado e em qual gôndola
    int ProdutoJaCadastrado = 0, R = 0, G = 0; 
    for (R = 0; R < RUAS_TOTAL; R++) {
        for (G = 0; G < GONDOLAS_TOTAL; G++) {
            if (strcmp(Estoque[R][G].Codigo_Produto, Codigo_Produto) == 0) {
                ProdutoJaCadastrado = 1;
                Rua = R;
                Gondola = G;
                break;
            }
        }
    }

    // Se o produto já existe, ele só pode ser armazenado na mesma gôndola
    if (ProdutoJaCadastrado) {
        printf("Produto %s ja cadastrado na rua %d, gondola %d.\n", Codigo_Produto, Rua + 1, Gondola + 1);
        printf("Informe a quantidade adicional a ser somada: ");
        scanf("%d", &Quantidade);

        if (Quantidade <= 0) {
            printf("Erro!!! A quantidade deve ser maior que zero!\n");
            return;
        }

        // Atualiza a quantidade do produto
        Estoque[Rua][Gondola].Quantidade += Quantidade;
        printf("Quantidade atualizada! Produto %s agora tem %d unidades na rua %d, gondola %d.\n", 
            Codigo_Produto, Estoque[Rua][Gondola].Quantidade, Rua + 1, Gondola + 1);
    } else {
        // Solicitar Rua e Gôndola para armazenar o produto
        printf("Informe a Rua e a gondola para armazenar o produto %s: ", Codigo_Produto);
        scanf("%d %d", &Rua, &Gondola);
        Rua--; Gondola--; // Ajuste para índices baseados em 0
        
        if (!Validar_Posicao(Rua, Gondola)) return;
        
        // Verificar se o espaço está vazio antes de cadastrar
        if (Estoque[Rua][Gondola].Quantidade == 0) {
            printf("Informe a quantidade inicial do produto %s: ", Codigo_Produto);
            scanf("%d", &Quantidade);
            
            if (Quantidade <= 0) {
                printf("Erro!!! A quantidade deve ser maior que zero!\n");
                return;
            }
            
            // Cadastrar o produto na gôndola escolhida
            strcpy(Estoque[Rua][Gondola].Codigo_Produto, Codigo_Produto);
            Estoque[Rua][Gondola].Quantidade = Quantidade;
            printf("Produto %s cadastrado com sucesso na rua %d, gondola %d com %d unidades!\n", 
                Codigo_Produto, Rua + 1, Gondola + 1, Quantidade);
        } else {
            printf("Erro!!! A gondola %d da rua %d ja esta ocupada!\n", Gondola + 1, Rua + 1);
        }
    }

    // Pergunta se deseja cadastrar outro produto
    char continuar;
    printf("Deseja cadastrar outro produto? (S/N): ");
    scanf(" %c", &continuar);

    if (continuar == 'S' || continuar == 's') {
        CadastrarProduto();
    } else {
        printf("Cadastro finalizado. Exibindo relatorio final:\n");
        Mostrar_Relatorio_Final();
    }
}

// Função para mostrar o relatório final com produtos cadastrados e gôndolas preenchidas
void Mostrar_Relatorio_Final() {
    printf("Produtos cadastrados e suas gondolas:\n");
    int Rua = 0, Gondola = 0;
    for (Rua = 0; Rua < RUAS_TOTAL; Rua++) {
        for (Gondola = 0; Gondola < GONDOLAS_TOTAL; Gondola++) {
            if (Estoque[Rua][Gondola].Quantidade > 0) {
                printf("Rua %d, Gondola %d - Produto: %s, Quantidade: %d\n", 
                    Rua + 1, Gondola + 1, Estoque[Rua][Gondola].Codigo_Produto, Estoque[Rua][Gondola].Quantidade);
            }
        }
    }
}

int main() {
    Iniciar_Estoque();
    CadastrarProduto();
    return 0;
}
