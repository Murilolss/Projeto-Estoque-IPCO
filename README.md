# 📦 Sistema de Controle de Estoque
Projeto desenvolvido para a disciplina de Introdução à Programação de Computadores (IPCO).

## 🎯 Objetivo

Desenvolver um sistema de controle de estoque utilizando a linguagem C, aplicando conceitos de programação estruturada, manipulação de arquivos, estruturas (`structs`) e modularização.

## ✨ Funcionalidades
### 📦 Produtos
- Cadastro de produtos
- Exclusão lógica de produtos
- Listagem de produtos
- Atualização de estoque
- Busca por ID ou nome
- Cálculo do valor total do estoque
- Relatório de estoque baixo

### 👤 Clientes
- Cadastro de clientes
- Listagem de clientes

### 💰 Vendas
- Registro de vendas
- Controle automático de estoque
- Histórico de vendas

---

## 🏗️ Estrutura do Projeto

```text
📁 projeto
├──📁 output
├── main.c
├── produtos.c
├── clientes.c
├── vendas.c
├── persistencia.c
└── bd.h
```
## 💾 Persistência de Dados

## Fluxo Geral
 
```
Programa inicia  →  carregarTudo() lê os .dat  →  vetores na memória
Programa roda    →  você cadastra / edita / deleta
Programa fecha   →  salvarTudo() escreve os .dat
```
 
---
 
## 📤 `salvarProdutos()` — Escrevendo no disco
 
```c
FILE *f = fopen(ARQUIVO_PRODUTOS, "wb");
fwrite(produtos, sizeof(Produto), TAM, f);
fclose(f);
```
 
| Linha | O que faz |
|---|---|
| `fopen(..., "wb")` | Abre ou cria o arquivo em modo **escrita binária** |
| `fwrite(produtos, sizeof(Produto), TAM, f)` | Copia o vetor inteiro byte a byte pro arquivo — como tirar uma "foto" da memória |
| `fclose(f)` | Fecha e garante que tudo foi gravado no disco |
 
> O arquivo `.dat` fica com exatamente `sizeof(Produto) * TAM` bytes — o tamanho exato do vetor na memória.
 
---
 
## 📥 `carregarProdutos()` — Lendo do disco
 
```c
FILE *f = fopen(ARQUIVO_PRODUTOS, "rb");
if (!f) return;
fread(produtos, sizeof(Produto), TAM, f);
fclose(f);
```
 
| Linha | O que faz |
|---|---|
| `fopen(..., "rb")` | Abre o arquivo em modo **leitura binária** |
| `if (!f) return` | Se o arquivo não existe (primeira execução), ignora sem crash |
| `fread(produtos, sizeof(Produto), TAM, f)` | Faz o inverso do `fwrite`: copia os bytes do arquivo de volta pro vetor na memória |
| `fclose(f)` | Fecha o arquivo |
 
---
 
## 🔁 Por que binário funciona tão bem aqui?
 
Sua `struct Produto` na memória e no disco são **idênticas**:
 
```
Memória:  [ id | nome[100] | preco | estoque ]
               ↕  fwrite copia ↓
Arquivo:  [ id | nome[100] | preco | estoque ]
               ↕  fread restaura ↑
Memória:  [ id | nome[100] | preco | estoque ]
```
 
Não precisa converter nada — o que está na memória vai direto pro disco e volta idêntico.
 
---
 
## 🔑 O `id = -1` é a chave
 
```c
produtos[i].id = -1;  // slot vazio
```
 
Esse é o marcador de **"posição livre"** no vetor. Quando você carrega do arquivo:
 
- Slots com dados → voltam com o `id` real
- Slots vazios → voltam com `-1`
Tudo se mantém consistente, sem lixo de memória.
 
---
 
## 📁 Arquivos gerados
 
```
📁 projeto
└──📁 output
    ├── produtos.dat   ← vetor Produto[] serializado
    ├── clientes.dat   ← vetor Cliente[] serializado
    ├── vendas.dat     ← vetor Venda[] serializado
    └── main.exe
```
 
Para **resetar** os dados, basta deletar esses arquivos. Na próxima execução, `carregarTudo()` não encontra os arquivos, não faz nada, e o sistema começa do zero.
 
---
 
## ⚖️ Binário vs Texto (CSV)
 
| | Binário (`.dat`) | Texto (`.csv`) |
|---|---|---|
| Código necessário | `fwrite`/`fread` simples | Precisa formatar e parsear |
| Velocidade | Mais rápido | Mais lento |
| Legível por humanos | ❌ Não | ✅ Sim |
| Compatível com a struct | ✅ Perfeito | Requer conversão manual |
 

## 🌐 Onde Nos Encontrar

<p align="left">
  <a href="https://instagram.com/liliane_perim">
    <img src="https://img.shields.io/badge/Instagram-@liliane_perim-E4405F?style=for-the-badge&logo=instagram&logoColor=white" />
  </a>
  <a href="https://instagram.com/murilolss__">
    <img src="https://img.shields.io/badge/Instagram-@murilolss__-E4405F?style=for-the-badge&logo=instagram&logoColor=white" />
  </a>
</p>

---


## 🛠️ Ferramentas Utilizadas

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)

---

## 📄 Licença

Projeto desenvolvido exclusivamente para fins acadêmicos.


