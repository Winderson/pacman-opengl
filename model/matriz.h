

#ifndef _MATRIZ_H
#define _MATRIZ_H

class Matriz{

public:
    int getLinha(){return _linha;}
    void setLinha(int linha){_linha = linha;}
    int getColuna(){return _coluna;}
    void setColuna(int coluna){_coluna = coluna;}
    int getValor(){return _valor;}
    void setValor(int valor){_valor = valor;}

private:
    int _linha;
    int _coluna;
    int _valor;
};

#endif //_MATRIZ_H
