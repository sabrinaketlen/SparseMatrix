#include <iostream>
#include "SparseMatrix.h"

using namespace std;

SparseMatrix* soma(SparseMatrix A, SparseMatrix B) {

int linhaA = A.linhas();
int colunaA = A.colunas();
int linhaB = B.linhas();
int colunaB = B.colunas();


double valorA; 
double valorB;

if (linhaA == linhaB && colunaA == colunaB) {
   SparseMatrix *C = new SparseMatrix(linhaA,colunaA);
        for (int i = 1; i <= linhaA; i++)
        {
            for (int j = 1; j <= colunaA; j++)
            {
                valorA = A.get(i,j);
                valorB = B.get(i,j);
                C->insert(i,j,valorA+valorB);       
            }
        }
        return C;
    }
    else {
        cout << "tamanho de linhas ou colunas são diferentes" << endl;
        return nullptr;
    }
}

SparseMatrix* multiplicacao(SparseMatrix A, SparseMatrix B) {

int linhaA = A.linhas();
int colunaA = A.colunas();
int linhaB = B.linhas();
int colunaB = B.colunas();


double valorA; 
double valorB;

if (linhaA == linhaB && colunaA == colunaB) {
   SparseMatrix *C = new SparseMatrix(linhaA,colunaA);
        for (int i = 1; i <= linhaA; i++)
        {
            for (int j = 1; j <= colunaA; j++)
            {
                valorA = A.get(i,j);
                valorB = B.get(i,j);
                C->insert(i,j,valorA*valorB);       
            }
        }
        return C;
    }
    else {
        cout << "tamanho de linhas ou colunas são diferentes" << endl;
        return nullptr;
    }
}

int main(){
    SparseMatrix bibia(7,7);
    SparseMatrix sasa(7,7);
    sasa.insert(7,7,7);
    bibia.insert(7,7,7);
    bibia.insert(6,6,6);
    bibia.insert(5,5,0);
    bibia.print();
    bibia.insert(7,7,0);
    bibia.print();
    bibia.insert(7,7,7);
    bibia.print();
    sasa.insert(6,6,6);
    sasa.insert(5,5,5);
    SparseMatrix *amor = soma(bibia,sasa);
    amor->print();
    SparseMatrix *amor2 = multiplicacao(bibia,sasa);
    amor2->print();

    //bibia.~SparseMatrix();
}
