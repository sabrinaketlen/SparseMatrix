#include <iostream>

using namespace std;

struct Node{
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;
};