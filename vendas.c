#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sgbd.h"

/*
    Aquivo Vendas - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

// Chamada das funções Utilizadas
void cadastroVenda();
void listarVendas();
int validaCpf(const char *cpf_str);
int validaData(const char *data_str);

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

            sleep(4);
            break;

        case 2:
            system("cls");
            listarVendas();
            printf("\nPressione Enter para voltar...");
            getchar();

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

// Função para cadastrar Vendas
void cadastroVenda()
{
    // Verifia o proximo Campo vazio do vetor
    int vazio = -1;
    for (int i = 0; i < TAM; i++)
    {
        if (vendas[i].id == -1)
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
        char dataTemp[12];
        char cpf[16];
        int idProduto = 0;
        int quantidade = 0;
        int indiceCliente = -1;
        int indiceProduto = -1;

        printf("Digite a data da venda no formato dd/mm/aaaa: ");
        fgets(dataTemp, sizeof(dataTemp), stdin);
        dataTemp[strcspn(dataTemp, "\n")] = '\0';

        printf("Informe o CPF do Cliente: ");
        fgets(cpf, 16, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        printf("Informe o ID do Produto: ");
        scanf("%d", &idProduto);
        while (getchar() != '\n');

        printf("Informe a Quantidade: ");
        scanf("%d", &quantidade);
        while (getchar() != '\n');

        // Validação de data
        if (!validaData(dataTemp))
        {
            printf("Data invalida! Use o formato dd/mm/aaaa.\n");
            return;
        }

        // Validação de CPF
        if (!validaCpf(cpf))
        {
            printf("CPF Invalido!\n");
            return;
        }

        // Validação para verificar se o cpf digitado existe no vetor de cliente
        for (int i = 0; i < TAM; i++)
        {
            if (clientes[i].id == -1)continue;

            if (strcmp(clientes[i].cpf, cpf) == 0)
            {
                indiceCliente = i;
                break;
            }
        }

        if (indiceCliente == -1)
        {
            printf("Cliente com esse CPF nao encontrado no sistema!\n");
            return;
        }

        // Validação para verificar se o ID digitado exite no vetor de produtos
        for (int i = 0; i < TAM; i++)
        {
            if (idProduto == produtos[i].id)
            {
                indiceProduto = i;
                break;
            }
        }

        if (indiceProduto == -1)
        {
            printf("Produto com esse ID nao encontrado no sistema!\n");
            return;
        }

        // Validação para verificar se o prodtudo selecionado está inativo 
        if (strcmp(produtos[indiceProduto].status, "INATIVO") == 0)
        {
            printf("O Produto Selecionado se encontra INATIVO, Ative ele ou Selecione outro Produto");
            return;
        }

        // Validação para verificar se a quantidade digitada é maior que a quantidade no estoque
        if (quantidade > produtos[indiceProduto].estoque)
        {
            printf("Quantidade maior que o estoque disponivel!\n");
            return;
        }

        vendas[vazio].id = vazio + 1;
        strcpy(vendas[vazio].datavenda, dataTemp);
        strcpy(vendas[vazio].cpfcliente, cpf);
        vendas[vazio].idproduto = idProduto;
        vendas[vazio].qtddesejada = quantidade;
        produtos[indiceProduto].estoque = produtos[indiceProduto].estoque - vendas[vazio].qtddesejada;
        vendas[vazio].totalVenda = quantidade * produtos[indiceProduto].preco;
        clientes[indiceCliente].totalvendas = clientes[indiceCliente].totalvendas + vendas[vazio].totalVenda;
        printf("\nVenda cadastrada com sucesso!");
    }
}

// Função para Listar todas as Vendas
void listarVendas()
{
    // Validação para verificar se tem vendas ou não no vetor
    int temVendas = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vendas[i].id != -1)
        {
            temVendas = 1;
            break;
        }
    }

    if (!temVendas)
    {
        printf("Nenhuma Venda encontrada\n");
        return;
    }

    printf("\n+--------+------------+---------------+--------------------+----------+------------+--------------------+--------------+");
    printf("\n| %-6s | %-10s | %-13s | %-18s | %-8s | %-10s | %-18s | %-12s |", "ID", "Data", "CPF", "Cliente", "ID Prod.", "Quantidade", "Produto", "Total");
    printf("\n+--------+------------+---------------+--------------------+----------+------------+--------------------+--------------+");

    for (int i = 0; i < TAM; i++)
    {
        // Validação para verificar se o CPF digitado existe no vetor de Clientes
        int indiceCliente = -1;
        for (int j = 0; j < TAM; j++)
        {
            if (clientes[j].id == -1)continue;
            if (strcmp(vendas[i].cpfcliente, clientes[j].cpf) == 0)
            {
                indiceCliente = j;
                break;
            }
        }

        // Validação para verificar se o ID do produto digitado existe no vetor de Produtos
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
        printf("\n| %-6d | %-10s | %-13s | %-18s | %-8d | %-10d | %-18s | %-12.2f |",
               vendas[i].id, vendas[i].datavenda, vendas[i].cpfcliente, clientes[indiceCliente].nome,
               vendas[i].idproduto, vendas[i].qtddesejada, produtos[indiceProduto].nome, vendas[i].totalVenda);
        printf("\n+--------+------------+---------------+--------------------+----------+------------+--------------------+--------------+");
    }

    printf("\n");
}

// Função para validação de CPF
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

// Função para Validação de data
int validaData(const char *data_str)
{
    // Verifica o tamanho exato: dd/mm/aaaa = 10 caracteres
    if (strlen(data_str) != 10)
        return 0;

    // Verifica se as barras estão nas posições certas
    if (data_str[2] != '/' || data_str[5] != '/')
        return 0;

    // Verifica se todos os outros caracteres são dígitos
    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit((unsigned char)data_str[i]))
            return 0;
    }

    int dia, mes, ano;
    sscanf(data_str, "%2d/%2d/%4d", &dia, &mes, &ano);

    // Verifica intervalo básico de mês e ano
    if (mes < 1 || mes > 12)
        return 0;

    if (ano < 1900 || ano > 2100) // ajuste o intervalo conforme sua necessidade
        return 0;

    // Dias por mês
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifica ano bissexto para fevereiro
    int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    if (mes == 2 && bissexto)
        diasNoMes[1] = 29;

    if (dia < 1 || dia > diasNoMes[mes - 1])
        return 0;

    return 1; // data válida
}