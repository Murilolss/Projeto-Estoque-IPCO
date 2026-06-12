#ifndef SGBD_H
#define SGBD_H

#define TAM 3

/*
    Arquivo SGBD - Database Management System
    Funciona basicamente como um Banco de dados
*/

typedef struct {
    int id;
    char nome[30];
    int estoque;
    float preco;
} Produto;

extern Produto produtos[TAM];

typedef struct{
    char nome[30];
    int cpf;
    int totalvendas;
} Cliente;

extern Cliente clientes[TAM];

typedef struct{
    char datavenda[10];
    int cpfcliente;
    int idproduto;
    int qtddesejada;
} Venda;

extern Venda vendas[TAM];

#endif