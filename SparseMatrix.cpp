#include <iostream>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int m, int n){
if(m > 0 && n > 0){
        // criando o nó novo
        this->m_head = new Node;
        this->m_head->linha = 0;
        this->m_head->coluna = 0;
        this->m_head->direita = m_head;
        this->m_head->abaixo = m_head;

        Node *aux = this->m_head;
        
        // fazendo o novo nó receber o valor de linha e coluna, o ultimo da fila apontar pra ele e ele apontar pro 
        // sentinela da linha
        for(int i = 1; i <= m; i++){
            Node *novo =  new Node;
            novo->coluna = 0;
            novo->linha = i;
            novo->direita = novo;
            novo->abaixo = this->m_head;
            aux->abaixo = novo;
            aux = novo;    
        } 
        
        aux = m_head;
        // mesma coisa, so que pra lista da coluna
        for(int i = 1; i <= n; i++){
            Node *novo =  new Node;
            novo->linha = 0;
            novo->coluna = i;
            novo->abaixo = novo;
            novo->direita = this->m_head;
            aux->direita = novo;
            aux = novo;
        }

        aux = nullptr;
        delete aux;
        
}
else {
    std::cout << "ERRO: impossivel criar matriz com os parametros propostos";
}
}

SparseMatrix::~SparseMatrix(){
    Node* aux = new Node;
    //deletando a matriz
    for (aux = m_head->abaixo; aux != m_head; aux = aux->abaixo)
    {
        while (aux->direita != aux)
        {
            Node* p;
            p = aux->direita->direita;
            delete aux->direita;
            aux->direita = p;
        }
    }
    aux = nullptr;
    delete aux;
    //deletando as sentinelas de colunas
    while (m_head->direita != m_head)
    {
        Node* p;
        p = m_head->direita->direita;
        delete m_head->direita;
        m_head->direita = p;
    }
    //deletando as sentinelas de linhas
    while (m_head->abaixo != m_head)
    {
        Node* p;
        p = m_head->abaixo->abaixo;
        delete m_head->abaixo;
        m_head->abaixo = p;
    }
    //deletando m_head
    delete m_head;
    cout << "matriz deletada" << endl;
}

// definir/substituir valor na posicao (i,j) por valor, checar se as posicoes sao maiores que zero
void SparseMatrix::insert(int i, int j, double valor){
if( i > 0 && j > 0){
Node *auxlinha = this->m_head;
Node *auxcoluna = this->m_head;

// fazendo os auxiliares de linha e coluna apontarem pras listas das respectivas linhas e colunas
while (auxlinha->linha != i){
        auxlinha = auxlinha->abaixo;
    }
while (auxcoluna->coluna != j){
    auxcoluna = auxcoluna->direita;
}
    // caso eu nao tente inserir um 0
    if(valor != 0){
    // crio um novo nó    
    Node *novo = new Node;
    novo->linha = i;
    novo->coluna = j;
    novo->valor = valor;
    // indica se a posicao ja foi sobrescrita
    int sobrescrito = 0;
    // caso da lista nao estar vazinha
    if(auxlinha->direita != auxlinha){
    // crio um nó "caminhador" para percorrer a linha
    Node *walker = auxlinha;
        while(walker->direita != auxlinha){
            // busca se a posicao ja existe
            if(walker->coluna == j){
                sobrescrito++;
                walker->valor = valor;
                //deleto o no que nao vou usar
                delete novo;
                break;
            }
        walker = walker->direita;
        }
        // busca se a posicao ja existe no ultimo elemento da lista
        if(walker->coluna == j && sobrescrito == 0){
                sobrescrito++;
                walker->valor = valor;
                //deleto o no que nao vou usar
                delete novo;

        }
        // se a posicao nao existe, ou seja, nao ouve sobrescricao, faco o ultimo apontar pro novo e o novo
        // apontar pra sentinela da linha
        else if (sobrescrito == 0) {
            novo->direita = auxlinha;
            walker->direita = novo;
        }

    walker = nullptr;
    delete walker;
    }
    else {
            // caso da linha estar vazia
            novo->direita = auxlinha;
            auxlinha->direita = novo;
    }

    // verifica se o valor ja nao foi sobrescrito, e se nao
    if (sobrescrito == 0){
        // cria um segundo no para caminhar pela lista da coluna
        Node *walker2 = auxcoluna;
        while(walker2 -> abaixo != auxcoluna){
            walker2 = walker2->abaixo;
        }
        // fazer o ultimo apontar pro novo, e o novo apontar pro sentinela
        walker2->abaixo = novo;
        novo->abaixo = auxcoluna;
        walker2 = nullptr;
        delete walker2;
    }

    auxcoluna = nullptr;
    auxlinha = nullptr;
    delete auxcoluna;
    delete auxlinha;
    }
    // caso de eu tentar inserir um 0
    else {

        Node *aux1=auxlinha;
        Node *aux2=auxcoluna;
        // sinal para indicar se a posicao nao existe
        int sinal = 0;

        // enquanto o auxliar da lista da linha nao achar um no com o valor da coluna
        while(aux1->direita->coluna != j){
            aux1 = aux1->direita;
            // verifica se chegou no comeco da lista dnv
            if (aux1 == auxlinha){
                // sinalizo que a posicao ainda nao existe
                sinal++;
                break;
            }
        }

        // mesma coisa, so que na lista da coluna
        while(aux2->abaixo->linha != i){
            aux2 = aux2->abaixo;
            if (aux2 == auxcoluna){
                sinal++;
                break;
            }
        }
        
        if(sinal == 0){
        Node *excluir = aux1->direita;

        aux1->direita = aux1->direita->direita;
        aux2->abaixo = aux2->abaixo->abaixo;

        delete excluir;
        aux1 = nullptr;
        aux2 = nullptr;
        delete aux1;
        delete aux2;
        }
        
    }

}
else {
    std::cout << "ERRO: parametros invalidos para o insert";
}
}

// me diz qual valor tem nessa posicao, deve checar se as posicoes sao maiores que zero
double SparseMatrix::get(int i, int j){
if( i > 0 && j > 0){
    Node *auxlinha = this->m_head;
    while (auxlinha->linha != i){
        auxlinha = auxlinha->abaixo;
    }
    double valor = 0;
    int achei = 0;
    Node *aux = auxlinha;

    while(aux->direita != auxlinha){
        if(aux->coluna != j){
            aux = aux->direita;
            continue;
        }
        valor = aux->valor;
        achei++;
        break;
    }

    if(aux->coluna == j && achei == 0){
        valor = aux->valor;
    }

    aux = nullptr;
    auxlinha = nullptr;
    delete aux;
    delete auxlinha;

    return valor;
}
else {
    std::cout << "ERRO: parametros invalidos para o get" << endl;
}

}
// imprime a matriz A, inclusive os elementos que sao iguais a zero;
void SparseMatrix::print(){
    int colunas = 0;
    int linhas = 0;
    Node* aux = new Node;
    //vendo quantidade de colunas
        for (aux = this->m_head->abaixo; aux != this->m_head; aux = aux->abaixo)
        {
            linhas++;
        }

        for (aux = this->m_head->direita; aux != this->m_head; aux = aux->direita)
        {
        colunas++;
        }
    //vendo quantidade de linhas
        
    std::cout <<"Matriz : " << linhas << " x " << colunas << endl;
    // printando a matriz
    Node* auxLin = new Node;
    Node* auxCol = new Node;
    for (auxLin = m_head->abaixo; auxLin != m_head; auxLin = auxLin->abaixo)
    {
        for (auxCol = m_head->direita; auxCol != m_head; auxCol = auxCol->direita)
        {
            if (auxCol != auxCol->abaixo)
            {
                for (aux = auxCol->abaixo; aux != auxCol; aux = aux->abaixo)
                {
                    if (aux->abaixo == auxCol && aux != auxLin->direita)
                    {
                        std::cout << "0 ";
                        break;
                    }
                    else
                        if (aux == auxLin->direita)
                        {
                            std::cout << auxLin->direita->valor << " ";
                            auxLin = auxLin->direita;
                            break;
                        }
                }
            }
            else
                if(auxCol == auxCol->abaixo)
                {
                    std::cout << "0 ";
                }

        }
        auxLin = auxLin->direita;
        std::cout << endl;
    }
    auxCol = nullptr;
    auxLin = nullptr;
    aux = nullptr;
    delete auxCol;
    delete auxLin;
    delete aux;
}

int SparseMatrix::linhas()
{
    int linhas = 0;
    Node* aux = new Node;
    
    for (aux = this->m_head->abaixo; aux != this->m_head; aux = aux->abaixo)
    {
        linhas++;
    }
    aux = nullptr;
    delete aux;
    return linhas;
}

int SparseMatrix::colunas()
{
    int colunas = 0;
    Node* aux = new Node;
    for (aux = this->m_head->direita; aux != this->m_head; aux = aux->direita)
    {
        colunas++;
    }
    aux = nullptr;
    delete aux;
    return colunas;
}