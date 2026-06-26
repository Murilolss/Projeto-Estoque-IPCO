#ifndef BD_H
#define BD_H

#define TAM 10

/*
    Arquivo BD - Database Management
    Funciona basicamente como um Banco de dados
*/

// Data Produto
typedef struct {
    int id;
    char nome[30];
    char status[15];
    int estoque;
    float preco;
} Produto;

extern Produto produtos[TAM];

// Data Cliente
typedef struct{
    int id;
    char nome[30];
    char cpf[16];
    char status[15];
    float totalvendas;
} Cliente;

extern Cliente clientes[TAM];

// Data Venda
typedef struct{
    int id;
    char datavenda[12];
    char cpfcliente[16];
    int idproduto;
    int qtddesejada;
    float totalVenda;
} Venda;

extern Venda vendas[TAM];

// Funções de Salvar e Carregar Dados
void salvarProdutos();
void carregarProdutos();
void salvarClientes();
void carregarClientes();
void salvarVendas();
void carregarVendas();
void salvarTudo();
void carregarTudo();

#endif