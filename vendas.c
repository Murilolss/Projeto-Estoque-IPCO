#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sgbd.h"

/*
    Aquivo Vendas - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

void cadastroVenda();
void listarVendas();

void menuVenda()
{
    int escolha;
    do
    {
        system("cls");
        printf("---- Selecione uma Opcao ----\n");
        printf("1 - Cadastrar Venda\n");
        printf("2 - Listar Vendas\n");
        printf("3 - Voltar\n");
        printf("4 - Encerrar Programa\n");
        printf("------------------------------\n");
        printf("Digite uma das Opcoes: ");
        scanf("%d", &escolha);
        while (getchar() != '\n');

        switch (escolha)
        {
        case 1:
            system("cls");
            cadastroVenda();

            sleep(3);
            break;

        case 2:
            system("cls");
            listarVendas();

            sleep(3);
            break;

        case 3:
            return;

        case 4:
            system("cls");
            printf("\nEncerrando o programa.\n");
            exit(0);
            break;

        default:

            system("cls");
            printf("\nOpcao errada! Digite novamente.\n");
            sleep(3);
            break;
        }
    } while (escolha != 4);
}

void cadastroVenda()
{
    printf("Venda cadastrado com sucesso");
}

void listarVendas()
{
    printf("Vendas encontrado com sucesso");
}