
#ifndef _WINDOW_H
#define _WINDOW_H
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <vector>
#include "../model/objeto.h"
#include "../model/arquivo.h"
#include "../model/matriz.h"
#include "../model/personagemPacman.h"
#define TAMANHO_MATRIZ_MAPA 45
class Window {

public:
    Window(){};
    void iniciar(int argc, char **argv);
    void static criarMapa(void);
    void static exibir(void);
    void static criarIntro(void);
    void static criarMapa1Matriz(void);
    void static criarMapa2Matriz(void);
    void static converterMapaMatriz(int matrizMapa1[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA]);
    void static criarCenario(void);
    void static criarPersonagemPacman();
    void static criarPainelInformacoes(void);
    void static criarObjetosMatriz(void);
    void static criarAnimacaoPacman(int valor);
    void static criarAnimacaoInimigos(int valor);
    void static criarMovimentacaoTecladoObjeto(unsigned char key, int x, int y);
    void static criarAcaoMouse(int button, int state, int x, int y);
    void static criarAnimacaoPacmanIntro(int valor);
    void static criarTextoIntro();
    static int abertoFechado;
    static int milisegundoTimer;
    static PersonagemPacman *pacman;
};


#endif //_WINDOW_H
