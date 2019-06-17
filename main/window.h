
#ifndef _WINDOW_H
#define _WINDOW_H
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#include <GL/glu.h>
#include <math.h>

class Window {

public:
    Window();
    void iniciar(int argc, char **argv);
    void static criarMapa(void);
    void static exibir(void);
    void static criarMapaMatriz(void);
    void static criarObjetoPrincipal(void);
    void static criarAnimacaoObjeto(int valor);
    void static criarMovimentacaoTecladoObjeto(unsigned char key, int x, int y);
    static int abertoFechado;
    static int milisegundoTimer;
};


#endif //_WINDOW_H
