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

#endif