#include <stdio.h>
#include "bd.h"

#define ARQUIVO_PRODUTOS "produtos.dat"
#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_VENDAS "vendas.dat"

// Arquivo persistencia - Responsável pelas funções de salvar e carregar os dados do sistema

// Produtos - Salvar
void salvarProdutos()
{
    FILE *f = fopen(ARQUIVO_PRODUTOS, "wb"); // "wb" = write binary
    if (!f)
    {
        printf("\nErro ao salvar produtos!");
        return;
    }

    fwrite(produtos, sizeof(Produto), TAM, f); // grava o vetor inteiro
    fclose(f);
}

// Produtos - Carregar
void carregarProdutos()
{
    FILE *f = fopen(ARQUIVO_PRODUTOS, "rb"); // "rb" = read binary
    if (!f)
        return;

    fread(produtos, sizeof(Produto), TAM, f);
    fclose(f);
}

// Clientes - Salvar
void salvarClientes()
{
    FILE *f = fopen(ARQUIVO_CLIENTES, "wb");
    if (!f)
    {
        printf("\nErro ao salvar clientes!");
        return;
    }

    fwrite(clientes, sizeof(Cliente), TAM, f);
    fclose(f);
}

// Clientes - Carregar
void carregarClientes()
{
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f)
        return;

    fread(clientes, sizeof(Cliente), TAM, f);
    fclose(f);
}

// Vendas - Salvar
void salvarVendas()
{
    FILE *f = fopen(ARQUIVO_VENDAS, "wb");
    if (!f)
    {
        printf("\nErro ao salvar vendas!");
        return;
    }

    fwrite(vendas, sizeof(Venda), TAM, f);
    fclose(f);
}

// Vendas - Carregar
void carregarVendas()
{
    FILE *f = fopen(ARQUIVO_VENDAS, "rb");
    if (!f)
        return;
    fread(vendas, sizeof(Venda), TAM, f);
    fclose(f);
}

// Funções para salvar todos os dados de uma vez
void salvarTudo()
{
    salvarProdutos();
    salvarClientes();
    salvarVendas();
}

// Funções para carregar todos os dados de uma vez
void carregarTudo()
{
    carregarProdutos();
    carregarClientes();
    carregarVendas();
}