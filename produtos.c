#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sgbd.h"
#define TAM 3

/*
    Aquivo produtos - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

void cadastroProduto();
void atualizarProduto();
void desativarProduto();
void buscarProduto();
void buscarProdutos();

void menuProduto()
{
    int escolha;
    do
    {
        system("cls");
        printf("---- Selecione uma Opcao ----\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Atualizar Produto\n");
        printf("3 - Deletar Produto\n");
        printf("4 - Buscar Produto (ID)\n");
        printf("5 - Listar Produtos\n");
        printf("6 - Voltar\n");
        printf("7 - Encerrar Programa\n");
        printf("------------------------------\n");
        printf("Digite uma das Opcoes: ");
        scanf("%d", &escolha);
        while (getchar() != '\n')
            ;

        switch (escolha)
        {
        case 1:
            system("cls");
            cadastroProduto();

            sleep(3);
            break;

        case 2:
            system("cls");
            atualizarProduto();

            sleep(3);
            break;

        case 3:
            system("cls");
            desativarProduto();

            sleep(3);
            break;

        case 4:
            system("cls");
            buscarProduto();
            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 5:
            system("cls");
            buscarProdutos();
            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 6:
            return;

        case 7:
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
    } while (escolha != 7);
}

void cadastroProduto()
{
    int vazio = -1;
    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == -1)
        {
            vazio = i;
            break;
        }
    }

    if (vazio == -1)
    {
        printf("Banco de dados cheio, contate a equipe de TI.");
    }
    else
    {

        produtos[vazio].id = vazio + 1;

        printf("Digite o Nome do Produto: ");
        fgets(produtos[vazio].nome, 30, stdin);
        produtos[vazio].nome[strcspn(produtos[vazio].nome, "\n")] = '\0';

        printf("Digite a quantidade no Estoque: ");
        scanf("%d", &produtos[vazio].estoque);
        while (getchar() != '\n');

        printf("Digite o Preco do Produto: ");
        scanf("%f", &produtos[vazio].preco);

        strcpy(produtos[vazio].status, "ATIVO");

        printf("\nProduto cadastrado com sucesso!");
    }
}

void atualizarProduto()
{
    printf("Produto atualizado com sucesso");
}

void desativarProduto()
{
    printf("Produto deletado com sucesso");
}

void buscarProduto()
{
    int id = 0;

    printf("Digite o ID do produto que deseja Buscar: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < TAM; i++)
    {
        if (id == produtos[i].id)
        {
            printf("\n+------+--------------------+----------+---------------+----------+");
            printf("\n| %-4s | %-18s | %-8s | %-13s | %-8s |", "ID", "Nome", "Estoque", "Preco", "Status");
            printf("\n+------+--------------------+----------+---------------+----------+");
            printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-8s |", produtos[id].id, produtos[id].nome, produtos[id].estoque, produtos[id].preco, produtos[id].status);
            printf("\n+------+--------------------+----------+---------------+----------+");
        
        }
    }
}

void buscarProdutos()
{

    int temProduto = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id != -1)
        {
            temProduto = 1;
            break;
        }
    }

    if (!temProduto)
    {
        printf("Nenhum Produto encontrado\n");
        return;
    }

    printf("\n+------+--------------------+----------+---------------+----------+");
    printf("\n| %-4s | %-18s | %-8s | %-13s | %-8s |", "ID", "Nome", "Estoque", "Preco", "Status");
    printf("\n+------+--------------------+----------+---------------+----------+");

    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == -1)
            continue;
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-8s |", produtos[i].id, produtos[i].nome, produtos[i].estoque, produtos[i].preco, produtos[i].status);
        printf("\n+------+--------------------+----------+---------------+----------+");
    }
}