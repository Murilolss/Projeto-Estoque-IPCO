#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "produtos.c"
#include "clientes.c"
#include "vendas.c"
#include "sgbd.h"
#define TAM 3

// Arqivo main - Responsável pelo menu

// Declaração de Vetores Globais
Produto produtos[TAM];
Venda vendas[TAM];
Cliente clientes[TAM];

// Chamada da Função menu
void menu();

// Funcção Principal
int main()
{

    //Inicialização de ID
    for (int i = 0; i < TAM; i++)
    {
        produtos[i].id = -1;
    }

    for (int i = 0; i < TAM; i++)
    {
        clientes[i].id = -1;
    }

    for (int i = 0; i < TAM; i++)
    {
        vendas[i].id = -1;
    }

    // Menu de Seleção
    menu();

    return 0;
}

// Menu de Seleção
void menu()
{
    int escolha;
    do
    {
        system("cls");
        printf("---- Selecione uma Pagina ----\n");
        printf("1 - Produtos\n");
        printf("2 - Clientes\n");
        printf("3 - Vendas\n");
        printf("4 - Encerrar Programa\n");
        printf("------------------------------\n");
        printf("Digite uma das Opcoes: ");
        scanf("%d", &escolha);
        while (getchar() != '\n')
            ;

        switch (escolha)
        {
        case 1:
            system("cls");
            menuProduto();
            break;

        case 2:
            system("cls");
            menuCliente();
            break;

        case 3:
            system("cls");
            menuVenda();
            break;

        case 4:
            system("cls");
            printf("\nEncerrando o programa.\n");
            break;

        default:
            system("cls");
            printf("\nOpcao errada! Digite novamente.\n");
            sleep(3);
            break;
        }
    } while (escolha != 4);
}