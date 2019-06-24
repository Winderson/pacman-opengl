#ifndef _WINDOWEXERCICIOS_H
#define _WINDOWEXERCICIOS_H
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#include <GL/glu.h>
#include "../model/objeto.h"

class WindowExercicios {
public:
    WindowExercicios(){};
    void iniciar(int argc, char **argv);
    void static exibir(void);
    void static criarMovimentoTecladoEspecial(int key, int x, int y);
    void static criarMovimentoTeclado(unsigned char key, int x, int y);
    void static criarTriangulosAleatorios();
    void static criarHexagonos();
    void static exibirTriangulos();
    void static exibirHexagonos();
    void static criarTriangulo();
    float static translacaoPositiva;
    float static translacaoNegativa;
    float static escalaPositiva;
    float static escalaNegativa;
    bool static  validaColisaoHexagono(float posicaoX, float posicaoY);
    void static movimentoHexagono(int valor);
};


#endif //_WINDOWEXERCICIOS_H
