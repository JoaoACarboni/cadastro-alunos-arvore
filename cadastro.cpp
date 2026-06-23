// Sistema de Cadastro de Alunos: Árvore Binária de Busca
// Disciplina: Estrutura de Dados 2026-01 - UTFPR
// Professor: Clayton Kossoski
// Alunos: Diogo Calegari dos Reis, João Antonio Carboni Gomes

/*
 Compilar: g++ cadastro.cpp -o cadastro
 Rodar:    .\cadastro.exe
 */
#include <iostream>
#include <string>
using namespace std;

// Estrutura aluno: nó da árvore binária
struct Aluno {
    int matricula;     
    string nome;        
    string curso; 
    Aluno* esquerda;     // ponteiro para filho com nome menor
    Aluno* direita;      // ponteiro para filho com nome maior
};

// Cria e retorna um novo nó com os dados do aluno
Aluno* criarAluno(int matricula, string nome, string curso) {
    Aluno* novo = new Aluno();  // aloca memória para o novo nó
    novo->matricula = matricula;
    novo->nome = nome;
    novo->curso = curso;
    novo->esquerda = nullptr;   // ainda não tem filhos
    novo->direita = nullptr;
    return novo;
}

// Insere um novo aluno na árvore e retorna a raiz atualizada
// Usa recursão
Aluno* inserir(Aluno* raiz, int matricula, string nome, string curso) {
    
    // Caso a raiz seja nula, cria um novo nó e retorna
    if (raiz == nullptr) {
        return criarAluno(matricula, nome, curso);
    }

    // Compara o nome novo com o nome do nó atual
    if (nome < raiz->nome) {
        // Nome menor: vai para a esquerda
        raiz->esquerda = inserir(raiz->esquerda, matricula, nome, curso);
    } 
    else if (nome > raiz->nome) {
        // Nome maior: vai para a direita
        raiz->direita = inserir(raiz->direita, matricula, nome, curso);
    } 
    else {
        // Nome igual: aluno já existe, não insere duplicado
        cout << "Aluno \"" << nome << "\" ja cadastrado!" << endl;
    }

    return raiz; // retorna a raiz sem modificação
}

// Percorre a árvore em ordem e exibe os alunos cadastrados
void listarEmOrdem(Aluno* raiz) {
    if (raiz == nullptr) {
        return; // chegou numa folha, para a recursão
    }

    listarEmOrdem(raiz->esquerda);  // visita esquerda

    // Exibe os dados do aluno atual
    cout << raiz->nome 
         << " - Matricula: " << raiz->matricula 
         << " - Curso: " << raiz->curso << endl;

    listarEmOrdem(raiz->direita);   // visita direita
}

// Busca um aluno pelo nome e retorna o ponteiro para ele
// Retorna nullptr se não encontrar
Aluno* buscar(Aluno* raiz, string nome) {
    // Caso base: árvore vazia ou nome encontrado
    if (raiz == nullptr) {
        return nullptr; 
    }
    if (raiz->nome == nome) {
        return raiz;
    }

    // Nome buscado é menor:
    if (nome < raiz->nome) {
        return buscar(raiz->esquerda, nome);
    }
    // Nome buscado é maior:
    return buscar(raiz->direita, nome);
}

// Calcula a altura da árvore recursivamente
// Altura = número de níveis da árvore
int altura(Aluno* raiz) {
    if (raiz == nullptr) {
        return 0; // árvore vazia tem altura 0
    }
    // Calcula altura dos dois lados e retorna o maior + 1
    int alturaEsq = altura(raiz->esquerda);
    int alturaDir = altura(raiz->direita);

    if (alturaEsq > alturaDir) {
        return alturaEsq + 1;
    }
    return alturaDir + 1;
}

// Conta o total de alunos cadastrados na árvore
int contarAlunos(Aluno* raiz) {
    if (raiz == nullptr) {
        return 0; // árvore vazia
    }
    // Conta o nó atual + todos da esquerda + todos da direita
    return 1 + contarAlunos(raiz->esquerda) + contarAlunos(raiz->direita);
}

int main() {
    Aluno* raiz = nullptr; // árvore começa vazia
    int opcao;

    do {
        // Menu de opções
        cout << "\n===== SISTEMA DE CADASTRO DE ALUNOS =====" << endl;
        cout << "1. Inserir aluno" << endl;
        cout << "2. Buscar aluno" << endl;
        cout << "3. Listar alunos em ordem alfabetica" << endl;
        cout << "4. Informacoes da arvore" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // limpa o buffer do teclado

        if (opcao == 1) {
            // Inserir aluno
            int matricula;
            string nome, curso;

            cout << "Matricula: ";
            cin >> matricula;
            cin.ignore();

            cout << "Nome completo: ";
            getline(cin, nome); // getline lê nome com espaços

            cout << "Curso: ";
            getline(cin, curso);

            raiz = inserir(raiz, matricula, nome, curso);
            cout << "Aluno inserido com sucesso!" << endl;

        } else if (opcao == 2) {
            // Buscar aluno
            string nome;
            cout << "Digite o nome do aluno: ";
            getline(cin, nome);

            Aluno* encontrado = buscar(raiz, nome);
            if (encontrado != nullptr) {
                cout << "Aluno encontrado!" << endl;
                cout << "Nome: "      << encontrado->nome      << endl;
                cout << "Matricula: " << encontrado->matricula << endl;
                cout << "Curso: "     << encontrado->curso     << endl;
            } else {
                cout << "Aluno nao encontrado!" << endl;
            }

        } else if (opcao == 3) {
            // Listar em ordem alfabética
            if (raiz == nullptr) {
                cout << "Nenhum aluno cadastrado!" << endl;
            } else {
                cout << "\n--- Alunos em ordem alfabetica ---" << endl;
                listarEmOrdem(raiz);
            }

        } else if (opcao == 4) {
            // Informações da árvore
            cout << "\n--- Informacoes da arvore ---" << endl;
            cout << "Total de alunos: " << contarAlunos(raiz) << endl;
            cout << "Altura da arvore: " << altura(raiz)      << endl;

        } else if (opcao != 0) {
            cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0); // repete até o usuário digitar 0

    cout << "Encerrando o sistema. Ate logo!" << endl;
    return 0;
}