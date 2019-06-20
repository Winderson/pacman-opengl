#ifndef _ARQUIVO_H
#define _ARQUIVO_H
#include <vector>
#include <string>
#include "matriz.h"

class Arquivo {
public:
    Arquivo(){}
    std::vector<Matriz> carregar(std::string caminhoArquivo, int tamanhoMatriz);
    std::vector<std::string> split(std::string str, const char* op);
};


#endif //_ARQUIVO_H
