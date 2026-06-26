#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "bd.h"
#define TAM 10

/*
    Arquivo produtos - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

// Chamada das Funções Utilizadas
void cadastroProduto();
void atualizarProduto();
void desativarProduto();
void buscarProduto();
void buscarProdutoNome();
void buscarProdutos();
void estoqueBaixo();
void paraMinusculo(char *destino, const char *origem);

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
        printf("5 - Buscar Produto (Nome)\n");
        printf("6 - Listar Produtos\n");
        printf("7 - Nivel Baixo de Estoque\n");
        printf("8 - Voltar\n");
        printf("9 - Encerrar Programa\n");
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
            salvarProdutos();

            sleep(3);
            break;

        case 2:
            system("cls");
            atualizarProduto();

            break;

        case 3:
            system("cls");
            desativarProduto();

            printf("\nPressione Enter para voltar...");
            getchar();
            break;

        case 4:
            system("cls");
            buscarProduto();
            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 5:
            system("cls");
            buscarProdutoNome();
            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 6:
            system("cls");
            buscarProdutos();
            printf("\n");

            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 7:
            system("cls");
            estoqueBaixo();
            printf("\n");

            printf("\nPressione Enter para voltar...");
            getchar();

            break;

        case 8:
            return;

        case 9:
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

// Função para cadastro de Produtos
void cadastroProduto()
{
    // Verifia o proximo Campo vazio do vetor
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
        int nomeExistente = 0;
        char nomeTemp[30];
        char nomeTempMin[30];
        float precoTemp = 0;
        int estoqueTemp = 0;

        printf("Digite o Nome do Produto: ");
        fgets(nomeTemp, 30, stdin);
        nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

        // Verifica se o nome do produto digitado ja existe no vetor
        paraMinusculo(nomeTempMin, nomeTemp);
        for (int i = 0; i < TAM; i++)
        {
            if (produtos[i].id == -1)continue;
            char nomeProdutoMin[30];
            paraMinusculo(nomeProdutoMin, produtos[i].nome);
            if (strcmp(nomeProdutoMin, nomeTempMin) == 0)
            {
                nomeExistente = 1;
                break;
            }
        }

        if (nomeExistente)
        {
            printf("Produto com esse nome ja esta cadastrado!\n");
            return;
        }

        printf("Digite a quantidade no Estoque: ");
        scanf("%d", &estoqueTemp);
        while (getchar() != '\n');

        if (estoqueTemp < 0)
        {
            printf("Estoque nao pode ser negativo!\n");
            return;
        }

        printf("Digite o Preco do Produto: ");
        scanf("%f", &precoTemp);
        while (getchar() != '\n');

        if (precoTemp < 0)
        {
            printf("Preco nao pode ser negativo!\n");
            return;
        }

        strcpy(produtos[vazio].status, "ATIVO");

        produtos[vazio].preco = precoTemp;
        produtos[vazio].id = vazio + 1;
        strcpy(produtos[vazio].nome, nomeTemp);
        printf("\nProduto cadastrado com sucesso!");
    }
}

// Função para atualização de Produtos
void atualizarProduto()
{
    int id = 0;

    printf("Digite o ID do produto que deseja Atualizar: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < TAM; i++)
    {
        if (id == produtos[i].id)
        {
            id = i;
            break;
        }
    }

    if ((id == -1) || (produtos[id].id == 0))
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
            while (getchar() != '\n');

            printf("\nEstoque atualizado com sucesso! Pressione enter para voltar...");
            getchar();
            break;

        case 3:
            printf("Digite um novo Preco do Produto: ");
            scanf("%f", &produtos[id].preco);
            while (getchar() != '\n');

            printf("\nPreco atualizado com sucesso! Pressione enter para voltar...");
            getchar();

            break;

        case 4:
            printf("Digite 1 para Status(ATIVO) ou 2 para Status(INATIVO): ");
            scanf("%d", &escolhaStatus);
            while (getchar() != '\n');

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

// Função para (deletar) Produtos
void desativarProduto()
{
    int id = 0;
    int deletar = 0;
    int ativar = 0;
    int vinculado = 0;

    printf("Digite o ID do produto que deseja deletar: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < TAM; i++)
    {
        if (id == produtos[i].id)
        {
            id = i;
            break;
        }
    }

    if ((id == -1) || (produtos[id].id == 0))
    {
        printf("Produto com esse ID nao encontrado!");
    }

    if (strcmp(produtos[id].status, "INATIVO") == 0)
    {
        printf("Produto selecionado esta INATIVO, Selecione 1 para ATIVAR ou 2 para voltar: ");
        scanf("%d", &ativar);
    }

    if (ativar == 1)
    {
        printf("\nProduto ativado com Sucesso!");
        strcpy(produtos[id].status, "ATIVO");
    }
    else if (ativar == 2)
    {
        return;
    }

    else
    {

        printf("\n+------+--------------------+----------+---------------+-------------+");
        printf("\n| %-4s | %-18s | %-8s | %-13s | %-11s |", "ID", "Nome", "Estoque", "Preco", "Status");
        printf("\n+------+--------------------+----------+---------------+-------------+");
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-11s |", produtos[id].id, produtos[id].nome, produtos[id].estoque, produtos[id].preco, produtos[id].status);
        printf("\n+------+--------------------+----------+---------------+-------------+");
        printf("\n");
        printf("\nO produto nao pode ser deletado, pode apenas mudar o status para INATIVO");
        printf("\nDigite 1 para mudar status ou 2 para voltar: ");
        scanf("%d", &deletar);
        while (getchar() != '\n');

        if (deletar == 1)
        {
            for (int i = 0; i < TAM; i++)
            {
                // Verifica se o produto a ser deletar esta vinculado em alguma venda
                if (produtos[i].id == vendas[i].idproduto)
                {
                    vinculado = 1;
                    break;
                }
            }
        }
        else if (deletar == 2)
        {
            return;
        }

        if (vinculado)
        {
            printf("\nPorduto nao pode ser desativado pois esta vinculado a uma venda!");
            return;
        }
        else
        {
            strcpy(produtos[id].status, "INATIVO");
            printf("\nPorduto desativado com sucesso!");
        }
    }
}

// Função para buscar Produto(ID)
void buscarProduto()
{
    int id = 0;

    printf("Digite o ID do produto que deseja Buscar: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < TAM; i++)
    {
        if (id == produtos[i].id)
        {
            id = i;
            break;
        }
    }

    if ((id == -1) || (produtos[id].id == 0))
    {
        printf("Produto com esse ID nao encontrado!");
    }
    else
    {

        printf("\n+------+--------------------+----------+---------------+-------------+");
        printf("\n| %-4s | %-18s | %-8s | %-13s | %-11s |", "ID", "Nome", "Estoque", "Preco", "Status");
        printf("\n+------+--------------------+----------+---------------+-------------+");
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-11s |", produtos[id].id, produtos[id].nome, produtos[id].estoque, produtos[id].preco, produtos[id].status);
        printf("\n+------+--------------------+----------+---------------+-------------+");
    }
}

// Função para listar todos os Produtos
void buscarProdutos()
{

    int temProduto = 0;
    float totalEstoque = 0;
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

    printf("\n+------+--------------------+----------+---------------+-------------+");
    printf("\n| %-4s | %-18s | %-8s | %-13s | %-11s |", "ID", "Nome", "Estoque", "Preco", "Status");
    printf("\n+------+--------------------+----------+---------------+-------------+");

    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == -1)continue;
        totalEstoque = totalEstoque + (produtos[i].estoque * produtos[i].preco);
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-11s |", produtos[i].id, produtos[i].nome, produtos[i].estoque, produtos[i].preco, produtos[i].status);
        printf("\n+------+--------------------+----------+---------------+-------------+");
    }

    printf("\n");
    printf("\n|   Valor total do Estoque  |--------------------------|  R$: %.2f  |", totalEstoque);
}

// Função para verificar produtos abaixo do Estoque
void estoqueBaixo()
{
    int quantidadeMin = 0;

    printf("Digite uma Quantidade minima: ");
    scanf("%d", &quantidadeMin);
    while (getchar() != '\n');

    int temProduto = 0;
    for (int i = 0; i < TAM; i++)
    {
        // Verificação de Estoque minimo
        if ((produtos[i].estoque != 0) && (produtos[i].estoque <= quantidadeMin))
        {
            temProduto = 1;
            break;
        }
    }

    if (!temProduto)
    {
        printf("Nenhum Produto encontrado com Estoque abaixo da Quantidade minima\n");
        return;
    }

    printf("Produtos com Estoque menor ou igual a: %d", quantidadeMin);
    printf("\n+------+--------------------+----------+---------------+-------------+");
    printf("\n| %-4s | %-18s | %-8s | %-13s | %-11s |", "ID", "Nome", "Estoque", "Preco", "Status");
    printf("\n+------+--------------------+----------+---------------+-------------+");

    for (int i = 0; i < TAM; i++)
    {
        // Lista todos os produtos conforme a quantidade minima digitada
        if (produtos[i].estoque <= quantidadeMin)
        {
            if (produtos[i].id == -1)
                continue;
            printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-11s |", produtos[i].id, produtos[i].nome, produtos[i].estoque, produtos[i].preco, produtos[i].status);
            printf("\n+------+--------------------+----------+---------------+-------------+");
        }
    }

    printf("\n");
}

// Função para tranformar tudo em minusculo
void paraMinusculo(char *destino, const char *origem)
{
    int i;
    for (i = 0; origem[i] != '\0'; i++)
    {
        destino[i] = tolower((unsigned char)origem[i]);
    }
    destino[i] = '\0';
}

// Função para Buscar Produtos por nome
void buscarProdutoNome()
{
    int encontrou = 0;
    char termoMin[30];
    char nomeMin[30];
    char nome[30];

    printf("Digite o nome do produto que deseja buscar:");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Função para tranformar o nome em minusculo para comparação
    paraMinusculo(termoMin, nome);

    printf("\n+------+--------------------+----------+---------------+-------------+");
    printf("\n| %-4s | %-18s | %-8s | %-13s | %-11s |", "ID", "Nome", "Estoque", "Preco", "Status");
    printf("\n+------+--------------------+----------+---------------+-------------+");

    for (int i = 0; i < TAM; i++)
    {
        if (produtos[i].id == -1)
            continue;

        paraMinusculo(nomeMin, produtos[i].nome);
        if (strstr(nomeMin, termoMin) == NULL)continue;

        encontrou = 1;
        printf("\n| %-4d | %-18s | %-8d | R$ %9.2f  | %-11s |", produtos[i].id, produtos[i].nome, produtos[i].estoque, produtos[i].preco, produtos[i].status);
        printf("\n+------+--------------------+----------+---------------+-------------+");
    }

    if (!encontrou)
    {
        printf("\nNenhum produto encontrado com esse nome.\n");
        return;
    }

    printf("\n");
}