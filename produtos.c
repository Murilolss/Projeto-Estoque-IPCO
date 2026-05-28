#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sgbd.c"

/*
    Aquivo produtos - Responsável pelo CRUD dessa "página"
    C = CREATE
    R = READ
    U = UPDATE
    D = DELETE
*/

void cadastroProduto();
void atualizarProduto();
void deletarProduto();
void buscarProduto();
void buscarProdutos();

void menuProduto(){
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
            deletarProduto();
            
            sleep(3);
            break;
            
            case 4:
            system("cls");
            buscarProduto();

            sleep(3);
            break;

            case 5:
            system("cls");
            buscarProdutos();

            sleep(3);
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

void cadastroProduto(){
    printf("Produto cadastrado com sucesso");
}

void atualizarProduto(){
    printf("Produto atualizado com sucesso");
}

void deletarProduto(){
    printf("Produto deletado com sucesso");
}

void buscarProduto(){
    printf("Produto encontrado com sucesso");
}

void buscarProdutos(){
    printf("Lista de produtos encontrada com sucesso");
}