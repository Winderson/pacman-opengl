#include "arquivo.h"
#include <iostream>
#include <fstream>

using namespace std;

vector<Matriz> Arquivo::carregar(string caminhoArquivo, int tamanhoMatriz) {
    ifstream arquivo(caminhoArquivo, ios_base::in);
    char linha[100] = {0};
    vector<Matriz> matriz;
    int l = 0;
    while (!arquivo.eof()) {
        arquivo.getline(linha, 100);
        vector<string> arrayLinha = this->split(((string) linha), ",");
        if (arrayLinha.size() > 0) {
            for (int c = 0; c < tamanhoMatriz; c++) {
                Matriz matrizAux;
                matrizAux.setValor(atoi(arrayLinha[c].c_str()));
                matrizAux.setColuna(c);
                matrizAux.setLinha(l);
                matriz.push_back(matrizAux);
            }
            l += 1;
        }
    }
    arquivo.close();
    return matriz;
}

vector<string> Arquivo::split(string str, const char *op) {
    std::vector<std::string> result;
    std::string rest = str, block;
    size_t operator_position = rest.find_first_of(op);
    while (operator_position != std::string::npos) {
        block = rest.substr(0, operator_position);
        rest = rest.substr(operator_position + 1);
        operator_position = rest.find_first_of(op);
        result.push_back(block);
    }
    if (rest.length() > 0)
        result.push_back(rest);
    return result;
}