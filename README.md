# Sistema de Cadastro de Alunos com Árvore Binária de Busca

Projeto desenvolvido para a disciplina de **Estrutura de Dados 2026-01**, da UTFPR.

## Integrantes

* Diogo Calegari dos Reis
* João Antonio Carboni Gomes

**Professor:** Clayton Kossoski

## Descrição

Este projeto implementa um sistema simples de cadastro de alunos utilizando uma **Árvore Binária de Busca (ABB)** em C++.

Os alunos são organizados alfabeticamente pelo nome. Cada nó da árvore armazena:

* Matrícula;
* Nome completo;
* Curso;
* Ponteiro para o filho à esquerda;
* Ponteiro para o filho à direita.

## Funcionalidades

* Inserir aluno;
* Buscar aluno pelo nome;
* Listar alunos em ordem alfabética;
* Exibir a quantidade total de alunos cadastrados;
* Exibir a altura da árvore.

## Estrutura utilizada

Foi utilizada uma Árvore Binária de Busca. Para cada aluno:

* Nomes menores que o nó atual são inseridos à esquerda;
* Nomes maiores são inseridos à direita;
* Nomes duplicados não são cadastrados.

## Como compilar e executar

No terminal, dentro da pasta do projeto:

```bash
g++ cadastro.cpp -o cadastro
```

No Windows:

```bash
.\cadastro.exe
```

## Arquivo principal

* `cadastro.cpp`: contém a implementação do sistema.
