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

            break;

        case 3:
            system("cls");
            desativarProduto();

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
        while (getchar() != '\n')
            ;

        printf("Digite o Preco do Produto: ");
        scanf("%f", &produtos[vazio].preco);
        while (getchar() != '\n')
            ;

        strcpy(produtos[vazio].status, "ATIVO");

        printf("\nProduto cadastrado com sucesso!");
    }
}

void atualizarProduto()
{
    int id = 0;

    printf("Digite o ID do produto que deseja Atualizar: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == id)
        {
            id = i;
            break;
        }
    }

    if (id != 0)
    {
        printf("Produto com esse ID nao encontrado!");
    }
    else
    {

        printf("\n+------+--------------------+----------+---------------+----------+");
        printf("\n| %-4s | %-18s | %-8s | %-13s | %-8s |", "ID", "Nome", "Estoque", "Preco", "Status");
        printf("\n+------+--------------------+----------+---------------+----------+");
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-8s |", produtos[id].id, produtos[id].nome, produtos[id].estoque, produtos[id].preco, produtos[id].status);
        printf("\n+------+--------------------+----------+---------------+----------+");
    }

    int escolha;
    int escolhaStatus = 0;
    do
    {
        printf("\n---- Selecione um campo Para atualizar ----\n");
        printf("1 - Nome\n");
        printf("2 - Estoque\n");
        printf("3 - Preco\n");
        printf("4 - Status\n");
        printf("5 - Voltar\n");
        printf("6 - Encerrar Programa\n");
        printf("------------------------------\n");
        printf("Digite uma das Opcoes: ");
        scanf("%d", &escolha);
        while (getchar() != '\n')
            ;

        switch (escolha)
        {
        case 1:
            printf("Digite um novo Nome: ");
            fgets(produtos[id].nome, 30, stdin);
            produtos[id].nome[strcspn(produtos[id].nome, "\n")] = '\0';

            printf("\nNome atualizado com sucesso! Pressione enter para voltar...");
            getchar();
            break;

        case 2:
            printf("Digite a nova quantidade no Estoque: ");
            scanf("%d", &produtos[id].estoque);
            while (getchar() != '\n')
                ;

            printf("\nEstoque atualizado com sucesso! Pressione enter para voltar...");
            getchar();
            break;

        case 3:
            printf("Digite um novo Preco do Produto: ");
            scanf("%f", &produtos[id].preco);
            while (getchar() != '\n')
                ;

            printf("\nPreco atualizado com sucesso! Pressione enter para voltar...");
            getchar();

            break;

        case 4:
            printf("Digite 1 para Status(ATIVO) ou 2 para Status(INATIVO): ");
            scanf("%d", &escolhaStatus);
            while (getchar() != '\n')
                ;

            if (escolhaStatus == 1)
            {
                strcpy(produtos[id].status, "ATIVO");
            }
            else if (escolhaStatus == 2)
            {
                strcpy(produtos[id].status, "INATIVO");
            }

            printf("\nStatus atualizado com sucesso! Pressione enter para voltar...");
            getchar();

            break;

        case 5:
            return;

        case 6:
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
    } while (escolha != 6);
}

void desativarProduto()
{
}

void buscarProduto()
{
    int id = 0;

    printf("Digite o ID do produto que deseja Buscar: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == id)
        {
            id = i;
            break;
        }
    }

    if (id != 0)
    {
        printf("Produto com esse ID nao encontrado!");
    }
    else
    {

        printf("\n+------+--------------------+----------+---------------+----------+");
        printf("\n| %-4s | %-18s | %-8s | %-13s | %-8s |", "ID", "Nome", "Estoque", "Preco", "Status");
        printf("\n+------+--------------------+----------+---------------+----------+");
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-8s |", produtos[id].id, produtos[id].nome, produtos[id].estoque, produtos[id].preco, produtos[id].status);
        printf("\n+------+--------------------+----------+---------------+----------+");
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
        if (produtos[i].id == -1)continue;
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-8s |", produtos[i].id, produtos[i].nome, produtos[i].estoque, produtos[i].preco, produtos[i].status);
        printf("\n+------+--------------------+----------+---------------+----------+");
    }
}