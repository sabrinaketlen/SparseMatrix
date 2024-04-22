#include <iostream>
#include "TNode.h"

using namespace std;

class SparseMatrix{
    private:
    Node *m_head{nullptr};

    public:
    //construtor deve inicializar a matriz com n no sentinelas para linhas e m no sentinelas para colunas
    //tb deve checar se valores sao maiores que 0
    SparseMatrix(int, int);
    ~SparseMatrix();
    // definit/substituir valor na posicao (i,j) por valor, checar se as posicoes sao maiores que zero
    void insert(int, int, double);
    // me diz qual valor tem nessa posicao, deve checar se as posicoes sao maiores que zero
    double get(int, int);
    // imprime a matriz A, inclusive os elementos que sao iguais a zero;
    void print();
    int linhas();
    int colunas();
};