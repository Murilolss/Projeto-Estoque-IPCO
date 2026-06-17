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
int validaCpf(const char *cpf_str);

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
        while (getchar() != '\n')
            ;

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
    int vazio = -1;
    for (int i = 0; i < TAM; i++)
    {
        if (clientes[i].id == -1)
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
        char dataTemp[10];
        char cpf[16];
        int idProduto = 0;
        int idCliente = 0;
        int quantidade = 0;
        int clienteEncontrado = 0;
        int produtoEncontrado = -1;

        printf("Digite a data da venda no formato dd/mm/aaaa: ");
        fgets(dataTemp, 10, stdin);
        dataTemp[strcspn(dataTemp, "\n")] = '\0';

        printf("Informe o CPF do Cliente: ");
        scanf("%d", &idCliente);
        while (getchar() != '\n')
            ;

        printf("Informe o ID do Produto: ");
        scanf("%d", &idProduto);
        while (getchar() != '\n')
            ;

        printf("Informe a Quantidade: ");
        scanf("%d", &quantidade);
        while (getchar() != '\n')
            ;

        if (!validaCpf(cpf))
        {
            printf("CPF Invalido!\n");
            return;
        }

        for (int i = 0; i < TAM; i++)
        {
            if (strcmp(clientes[i].cpf, cpf) == 0)
            {
                clienteEncontrado = 1;
                break;
            }
        }

        if (!clienteEncontrado)
        {
            printf("Cliente com esse CPF nao encontrado no sistema!\n");
            return;
        }

        for (int i = 0; i < TAM; i++)
        {
            if (idProduto == produtos[i].id)
            {
                produtoEncontrado = i;
                break;
            }
        }
        if (produtoEncontrado == -1)
        {
            printf("Produto com esse ID nao encontrado no sistema!\n");
            return;
        }

        if (quantidade > produtos[produtoEncontrado].estoque)
        {
            printf("Quantidade maior que o estoque disponivel!\n");
            return;
        }

        vendas[vazio].id = vazio + 1;
        strcpy(vendas[vazio].datavenda, dataTemp);
        strcpy(vendas[vazio].cpfcliente, cpf);
        vendas[vazio].idproduto = idProduto;
        vendas[vazio].qtddesejada = quantidade;
        printf("Venda cadastrada com sucesso!\n");
    }
}

void listarVendas()
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

    for (int i = 0; i < TAM; i++)
    {
    }

    if (!temProduto)
    {
        printf("Nenhuma Venda encontrada\n");
        return;
    }

    printf("\n+--------+------------+---------------+--------------------+------------+--------------------+");
    printf("\n| %-6s | %-10s | %-13s | %-18s | %-10s | %-18s |", "ID", "Data", "CPF", "Cliente", "ID Prod.", "Produto");
    printf("\n+--------+------------+---------------+--------------------+------------+--------------------+");

    for (int i = 0; i < TAM; i++)
    {
        int indiceCliente = -1;
        for (int j = 0; j < TAM; j++)
        {
            if (clientes[j].id == -1) continue;
            if (strcmp(vendas[i].cpfcliente, clientes[j].cpf) == 0)
            {
                indiceCliente = j;
                break;
            }
        }

        int indiceProduto = -1;
        for (int k = 0; k < TAM; k++)
        {
            if (produtos[k].id == -1)continue;
            if (produtos[k].id == vendas[i].idproduto)
            {
                indiceProduto = k;
                break;
            }
        }

        if (vendas[i].id == -1)continue;
        printf("\n| %-6d | %-10s | %-13s | %-18s | %-10d | %-18s |", vendas[i].id, vendas[i].datavenda, vendas[i].cpfcliente, clientes[indiceCliente].nome, vendas[i].idproduto, produtos[indiceProduto].nome);
        printf("\n+--------+------------+---------------+--------------------+------------+--------------------+");
    }

    printf("\n");
}

int validaCpf(const char *cpf_str)
{
    char digits[12];
    int len = 0;

    // Extrai apenas os dígitos
    for (int i = 0; cpf_str[i] != '\0' && len < 11; i++)
    {
        if (isdigit((unsigned char)cpf_str[i]))
            digits[len++] = cpf_str[i] - '0';
    }

    if (len != 11)
        return 0;

    // Rejeita sequências repetidas (ex: 000.000.000-00)
    int all_same = 1;
    for (int i = 1; i < 11; i++)
        if (digits[i] != digits[0])
        {
            all_same = 0;
            break;
        }
    if (all_same)
        return 0;

    // Valida 1º dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++)
        soma += digits[i] * (10 - i);
    int resto = (soma * 10) % 11;
    if (resto == 10)
        resto = 0;
    if (resto != digits[9])
        return 0;

    // Valida 2º dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++)
        soma += digits[i] * (11 - i);
    resto = (soma * 10) % 11;
    if (resto == 10)
        resto = 0;
    if (resto != digits[10])
        return 0;

    return 1;
}