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
    char status[15];
    int estoque;
    float preco;
} Produto;

extern Produto produtos[TAM];

typedef struct{
    int id;
    char nome[30];
    char cpf[16];
    char status[15];
    int totalvendas;
} Cliente;

extern Cliente clientes[TAM];

typedef struct{
    int id;
    char datavenda[10];
    char cpfcliente[16];
    int idproduto;
    int qtddesejada;
} Venda;

extern Venda vendas[TAM];

#endif