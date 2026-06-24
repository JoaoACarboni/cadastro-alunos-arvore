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
    Aluno* novo = new Aluno();

    novo->matricula = matricula;
    novo->nome = nome;
    novo->curso = curso;
    novo->esquerda = nullptr;
    novo->direita = nullptr;

    return novo;
}

// Insere um novo aluno na árvore e retorna a raiz atualizada
// Usa recursão
Aluno* inserir(Aluno* raiz, int matricula, string nome, string curso, bool& inserido) {

    // Caso a raiz seja nula, cria um novo nó
    if (raiz == nullptr) {
        inserido = true;
        return criarAluno(matricula, nome, curso);
    }

    // Nome menor: insere à esquerda
    if (nome < raiz->nome) {
        raiz->esquerda = inserir(raiz->esquerda, matricula, nome, curso, inserido);
    }
    // Nome maior: insere à direita
    else if (nome > raiz->nome) {
        raiz->direita = inserir(raiz->direita, matricula, nome, curso, inserido);
    }
    else {
        // Nome igual: não permite cadastrar novamente
        inserido = false;
        cout << "Aluno \"" << nome << "\" ja cadastrado!" << endl;
    }

    return raiz;
}

// Verifica se já existe algum aluno com a matrícula informada
bool matriculaExiste(Aluno* raiz, int matricula) {
    if (raiz == nullptr) {
        return false;
    }

    // Encontrou a matrícula repetida
    if (raiz->matricula == matricula) {
        return true;
    }

    // Como a árvore é organizada pelo nome, verifica os dois lados
    return matriculaExiste(raiz->esquerda, matricula) ||
           matriculaExiste(raiz->direita, matricula);
}

// Percorre a árvore em ordem e exibe os alunos cadastrados
void listarEmOrdem(Aluno* raiz) {
    if (raiz == nullptr) {
        return;
    }

    listarEmOrdem(raiz->esquerda);

    cout << raiz->nome
         << " - Matricula: " << raiz->matricula
         << " - Curso: " << raiz->curso << endl;

    listarEmOrdem(raiz->direita);
}

// Busca um aluno pelo nome e retorna o ponteiro para ele
Aluno* buscar(Aluno* raiz, string nome) {
    if (raiz == nullptr) {
        return nullptr;
    }

    if (raiz->nome == nome) {
        return raiz;
    }

    if (nome < raiz->nome) {
        return buscar(raiz->esquerda, nome);
    }

    return buscar(raiz->direita, nome);
}

// Calcula a altura da árvore recursivamente
int altura(Aluno* raiz) {
    if (raiz == nullptr) {
        return 0;
    }

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
        return 0;
    }

    return 1 + contarAlunos(raiz->esquerda) + contarAlunos(raiz->direita);
}

int main() {
    Aluno* raiz = nullptr;
    int opcao;

    do {
        cout << "\n===== SISTEMA DE CADASTRO DE ALUNOS =====" << endl;
        cout << "1. Inserir aluno" << endl;
        cout << "2. Buscar aluno" << endl;
        cout << "3. Listar alunos em ordem alfabetica" << endl;
        cout << "4. Informacoes da arvore" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";

        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            int matricula;
            string nome, curso;

            cout << "Matricula: ";
            cin >> matricula;
            cin.ignore();

            cout << "Nome completo: ";
            getline(cin, nome);

            cout << "Curso: ";
            getline(cin, curso);

            // Verifica se a matrícula já está cadastrada
            if (matriculaExiste(raiz, matricula)) {
                cout << "Matricula " << matricula << " ja cadastrada!" << endl;
            }
            else {
                // Variável usada para informar se o nome foi inserido
                bool inserido = false;

                raiz = inserir(raiz, matricula, nome, curso, inserido);

                // Só mostra sucesso se o nome não for repetido
                if (inserido) {
                    cout << "Aluno inserido com sucesso!" << endl;
                }
            }

        }
        else if (opcao == 2) {
            string nome;

            cout << "Digite o nome do aluno: ";
            getline(cin, nome);

            Aluno* encontrado = buscar(raiz, nome);

            if (encontrado != nullptr) {
                cout << "Aluno encontrado!" << endl;
                cout << "Nome: " << encontrado->nome << endl;
                cout << "Matricula: " << encontrado->matricula << endl;
                cout << "Curso: " << encontrado->curso << endl;
            }
            else {
                cout << "Aluno nao encontrado!" << endl;
            }

        }
        else if (opcao == 3) {
            if (raiz == nullptr) {
                cout << "Nenhum aluno cadastrado!" << endl;
            }
            else {
                cout << "\n--- Alunos em ordem alfabetica ---" << endl;
                listarEmOrdem(raiz);
            }

        }
        else if (opcao == 4) {
            cout << "\n--- Informacoes da arvore ---" << endl;
            cout << "Total de alunos: " << contarAlunos(raiz) << endl;
            cout << "Altura da arvore: " << altura(raiz) << endl;

        }
        else if (opcao != 0) {
            cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0);

    cout << "Encerrando o sistema. Ate logo!" << endl;

    return 0;
}