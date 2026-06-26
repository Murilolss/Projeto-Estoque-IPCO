#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "bd.h"
#define TAM 10

/*
    Arquivo clientes - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

// Chamadas das Funções Utilizadas
int validarCpf(const char *cpf_str);
int campoVazio(const char *str);
void cadastroCliente();
void listarClientes();

// Menu de Seleção da parte do Cliente
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
        while (getchar() != '\n');

        switch (escolha)
        {
        case 1:
            system("cls");
            cadastroCliente();
            salvarClientes();

            sleep(3);
            break;

        case 2:
            system("cls");
            listarClientes();

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

// Função para Cadastrar Clientes
void cadastroCliente()
{
    // Verifia o proximo Campo vazio do vetor
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
        char cpf[16];
        char nomeTemp[30];
        int cpfExiste = 0;

        printf("Digite o Nome Completo do Cliente: ");
        fgets(nomeTemp, 30, stdin);
        nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

        if (campoVazio(nomeTemp))
        {
            printf("Nome nao pode ser vazio!\n");
            return;
        }

        printf("Digite o CPF do Cliente: ");
        fgets(cpf, 16, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        if (!validarCpf(cpf))
        {
            printf("CPF Invalido!\n");
            return;
        }

        // Compara se o CPF Digitado existe no vetor de clientes
        for (int i = 0; i < TAM; i++)
        {
            if (strcmp(clientes[i].cpf, cpf) == 0)
            {
                cpfExiste = 1;
                break;
            }
        }

        if (cpfExiste)
        {
            printf("CPF ja cadastrado!\n");
            return;
        }

        clientes[vazio].id = vazio + 1;
        strcpy(clientes[vazio].nome, nomeTemp);
        strcpy(clientes[vazio].cpf, cpf);
        strcpy(clientes[vazio].status, "ATIVO");
        printf("\nCliente cadastrado com sucesso!");
    }
}

// Função para Listar os Clientes
void listarClientes()
{
    // Verifica se tem cliente cadastrado no vetor
    int temCliente = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (clientes[i].id != -1)
        {
            temCliente = 1;
            break;
        }
    }

    if (!temCliente)
    {
        printf("Nenhum Cliente encontrado\n");
        return;
    }

    // Tabela de Clientes
    printf("\n+------+--------------------+---------------+-----------------+----------+");
    printf("\n| %-4s | %-18s | %-13s | %-15s | %-8s |", "ID", "Nome", "CPF", "Total de Vendas", "Status");
    printf("\n+------+--------------------+---------------+-----------------+----------+");

    for (int i = 0; i < TAM; i++)
    {
        if (clientes[i].id == -1)
            continue;
        printf("\n| %-4d | %-18s | %-13s | R$: %-11.2f | %-8s |", clientes[i].id, clientes[i].nome, clientes[i].cpf, clientes[i].totalvendas, clientes[i].status);
        printf("\n+------+--------------------+---------------+-----------------+----------+");
    }
}

// Função para validação de CPF
int validarCpf(const char *cpf_str)
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

// Validação de campo vazio
int campoVazio(const char *str)
{
    return str == NULL || str[0] == '\0';
}