#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sgbd.c"

/*
    Aquivo clientes - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

void cadastroCliente();
void listarClientes();

void menuCliente()
{
    int escolha;
    do
    {
        system("cls");
        printf("---- Selecione uma Opcao ----\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Voltar\n");
        printf("4 - Encerrar Programa\n");
        printf("------------------------------\n");
        printf("Digite uma das Opcoes: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            cadastroCliente();

            sleep(3);
            break;

        case 2:
            system("cls");
            listarClientes();

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

void cadastroCliente()
{
    printf("Cliente cadastrado com sucesso");
}

void listarClientes()
{
    printf("Clientes encontrado com sucesso");
}