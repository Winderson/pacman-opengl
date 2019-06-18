#include "window.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define TAMANHO_MATRIZ_MAPA 45

int Window::abertoFechado = 2;
int Window::milisegundoTimer = 350;
float zoom = 0;

// Movimento do objeto
float dimensaoEsquerda = 0;
float dimensaoDireita = 500;
float dimensaoBaixo = 0;
float dimensaoCima = 500;
float alteracaoPosicao = 3;
int teste = 1;

//
float personagemX = 250;
float personagemY = 250;
float personagemComprimento = 30;
float personagemAltura = 100;
float personagemAlturaAux = 5;

//
float raioObjeto = 12;

// Posicao de objeto auxiliar

// 0 = esquerda
// 1 = direita
// 2 = cima
// 3 = baixo


//

/**
 * Construtor
 */
Window::Window() {

}


class Bloco{
public:
    float x;
    float y;
    float comp;
    float alt;
    char rotulo;
};

Bloco blocos[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];                                                  //
int matrizMapa[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


void Window::iniciar(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(320, 50);
    //glutInitWindowPosition(0, 0);
    glutCreateWindow("Pacman");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(dimensaoEsquerda, dimensaoDireita, dimensaoBaixo, dimensaoCima);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(this->exibir);
    glutTimerFunc(milisegundoTimer, this->criarAnimacaoObjeto, abertoFechado);
    glutKeyboardFunc(this->criarMovimentacaoTecladoObjeto);
    //glutSpecialFunc(this->criarMovimentacaoTecladoObjeto);
    //glutIdleFunc(this->exibir);
    glutMainLoop();
}

void Window::criarMapaMatriz(void) {
    int x = 0;
    int y = 490;
    for(int l = 0; l<TAMANHO_MATRIZ_MAPA; l++){
        for(int c=0; c<TAMANHO_MATRIZ_MAPA; c++, x += 11){

            if(matrizMapa[l][c] == 1){
                blocos[l][c].rotulo = 'o';
            } else if (matrizMapa[l][c] == 0){
                blocos[l][c].rotulo = 'l';
            }

            blocos[l][c].x = x;
            blocos[l][c].y = y;
            blocos[l][c].comp = 10;
            blocos[l][c].alt = 10;
        }
        x = 0;
        y -=11;
    }

}

void Window::criarMapa(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(153, 204, 255);

    glBegin(GL_QUADS);
    glVertex2f(1.5, 3.0);
    glVertex2f(-1.5, 3.0);
    glVertex2f(-1.5, 3.3);
    glVertex2f(1.5, 3.3);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.1, 2.0);
    glVertex2f(-0.1, 2.0);
    glVertex2f(-0.1, 3.0);
    glVertex2f(0.1, 3.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.1, 2.0);
    glVertex2f(-0.1, 2.0);
    glVertex2f(-0.1, 3.0);
    glVertex2f(0.1, 3.0);
    glEnd();

    // Lado direito do mapa
    glBegin(GL_LINES);
    glVertex2f(1, 2.0);
    glVertex2f(2.2, 2.0);
    glVertex2f(2.2, 2.0);
    glVertex2f(2.2, 0.4);
    glVertex2f(2.2, 0.4);
    glVertex2f(2.4, 0.4);
    glVertex2f(2.4, 0.4);
    glVertex2f(2.4, 2.0);
    glVertex2f(2.4, 2.0);
    glVertex2f(3.0, 2.0);
    glVertex2f(3.0, 2.0);
    glVertex2f(3.0, 2.2);
    glVertex2f(3.0, 2.2);
    glVertex2f(1, 2.2);
    glVertex2f(1, 2.2);
    glVertex2f(1, 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(2.2, -0.4);
    glVertex2f(2.2, -1);
    glVertex2f(2.2, -1);
    glVertex2f(2.4, -1);
    glVertex2f(2.4, -1);
    glVertex2f(2.4, -0.4);
    glVertex2f(2.4, -0.4);
    glVertex2f(2.2, -0.4);

    glBegin(GL_LINES);
    glVertex2f(1, -2.0);
    glVertex2f(3.0, -2.0);
    glVertex2f(3.0, -2.0);
    glVertex2f(3.0, -2.2);
    glVertex2f(3.0, -2.2);
    glVertex2f(1, -2.2);
    glVertex2f(1, -2.2);
    glVertex2f(1, -2.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.8, 2.0);
    glVertex2f(4.0, 2.0);
    glVertex2f(4.0, 2.0);
    glVertex2f(4.0, 2.2);
    glVertex2f(4.0, 2.2);
    glVertex2f(3.8, 2.2);
    glVertex2f(3.8, 2.2);
    glVertex2f(3.8, 2.0);
    glEnd();

    // Lado esquerdo do mapa
    glBegin(GL_LINES);
    glVertex2f(-1, 2.0);
    glVertex2f(-2.2, 2.0);
    glVertex2f(-2.2, 2.0);
    glVertex2f(-2.2, 0.4);
    glVertex2f(-2.2, 0.4);
    glVertex2f(-2.4, 0.4);
    glVertex2f(-2.4, 0.4);
    glVertex2f(-2.4, 2.0);
    glVertex2f(-2.4, 2.0);
    glVertex2f(-3.0, 2.0);
    glVertex2f(-3.0, 2.0);
    glVertex2f(-3.0, 2.2);
    glVertex2f(-3.0, 2.2);
    glVertex2f(-1, 2.2);
    glVertex2f(-1, 2.2);
    glVertex2f(-1, 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-2.2, -0.4);
    glVertex2f(-2.2, -1);
    glVertex2f(-2.2, -1);
    glVertex2f(-2.4, -1);
    glVertex2f(-2.4, -1);
    glVertex2f(-2.4, -0.4);
    glVertex2f(-2.4, -0.4);
    glVertex2f(-2.2, -0.4);

    glBegin(GL_LINES);
    glVertex2f(-1, -2.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(-3.0, -2.2);
    glVertex2f(-3.0, -2.2);
    glVertex2f(-1, -2.2);
    glVertex2f(-1, -2.2);
    glVertex2f(-1, -2.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3.8, 2.0);
    glVertex2f(-4.0, 2.0);
    glVertex2f(-4.0, 2.0);
    glVertex2f(-4.0, 2.2);
    glVertex2f(-4.0, 2.2);
    glVertex2f(-3.8, 2.2);
    glVertex2f(-3.8, 2.2);
    glVertex2f(-3.8, 2.0);
    glEnd();

    // Ponto central
//    glBegin(GL_QUADS);
//        glVertex2f(1.5,-1);
//        glVertex2f(-1.5,-1);
//        glVertex2f(-1.5,1);
//        glVertex2f(1.5,1);

    glBegin(GL_LINES);
    glVertex2f(0.5, 1);
    glVertex2f(1.5, 1);
    glVertex2f(1.5, 1);
    glVertex2f(1.5, -1);
    glVertex2f(1.5, -1);
    glVertex2f(-1.5, -1);
    glVertex2f(-1.5, -1);
    glVertex2f(-1.5, 1);
    glVertex2f(-1.5, 1);
    glVertex2f(-0.5, 1);
    glVertex2f(-0.5, 1);
    glVertex2f(-0.5, 0.8);
    glVertex2f(-0.5, 0.8);
    glVertex2f(-1.3, 0.8);
    glVertex2f(-1.3, 0.8);
    glVertex2f(-1.3, -0.8);
    glVertex2f(-1.3, -0.8);
    glVertex2f(1.3, -0.8);
    glVertex2f(1.3, -0.8);
    glVertex2f(1.3, 0.8);
    glVertex2f(1.3, 0.8);
    glVertex2f(0.5, 0.8);
    glVertex2f(0.5, 0.8);
    glVertex2f(0.5, 1);
    glEnd();

    // Contorno Topo
    glBegin(GL_LINES);
    glVertex2f(4.8, 0.4);
    glVertex2f(3.2, 0.4);
    glVertex2f(3.2, 0.4);
    glVertex2f(3.2, 1.0);
    glVertex2f(3.2, 1.0);
    glVertex2f(4.8, 1.0);
    glVertex2f(4.8, 1.0);
    glVertex2f(4.8, 0.8);
    glVertex2f(4.8, 0.8);
    glVertex2f(3.4, 0.8);
    glVertex2f(3.4, 0.8);
    glVertex2f(3.4, 0.6);
    glVertex2f(3.4, 0.6);
    glVertex2f(4.8, 0.6);
    glVertex2f(4.8, 1.0);
    glVertex2f(4.8, 4.8);
    glVertex2f(4.8, 4.8);
    glVertex2f(0.1, 4.8);
    glVertex2f(0.1, 4.8);
    glVertex2f(0.1, 4.2);
    glVertex2f(0.1, 4.2);
    glVertex2f(-0.1, 4.2);
    glVertex2f(-0.1, 4.2);
    glVertex2f(-0.1, 4.8);
    glVertex2f(-0.1, 4.8);
    glVertex2f(-4.8, 4.8);
    glVertex2f(-4.8, 4.8);
    glVertex2f(-4.8, 1.0);
    glVertex2f(-4.8, 1.0);
    glVertex2f(-3.2, 1.0);
    glVertex2f(-3.2, 1.0);
    glVertex2f(-3.2, 0.4);
    glVertex2f(-3.2, 0.4);
    glVertex2f(-4.8, 0.4);
    glVertex2f(-4.8, 1.0);
    glVertex2f(-4.8, 0.8);
    glVertex2f(-4.8, 0.8);
    glVertex2f(-3.4, 0.8);
    glVertex2f(-3.4, 0.8);
    glVertex2f(-3.4, 0.6);
    glVertex2f(-3.4, 0.6);
    glVertex2f(-4.8, 0.6);
    glEnd();

    // Contorno BOTTOM
    glBegin(GL_LINES);
    glVertex2f(4.8, -0.4);
    glVertex2f(3.2, -0.4);
    glVertex2f(3.2, -0.4);
    glVertex2f(3.2, -1.0);
    glVertex2f(3.2, -1.0);
    glVertex2f(4.8, -1.0);
    glVertex2f(4.8, -0.6);
    glVertex2f(3.4, -0.6);
    glVertex2f(3.4, -0.6);
    glVertex2f(3.4, -0.8);
    glVertex2f(3.4, -0.8);
    glVertex2f(4.8, -0.8);
    glVertex2f(4.8, -0.8);
    glVertex2f(4.8, -4.8);
    glVertex2f(4.8, -4.8);
    glVertex2f(0.1, -4.8);
    glVertex2f(0.1, -4.8);
    glVertex2f(0.1, -4.2);
    glVertex2f(0.1, -4.2);
    glVertex2f(-0.1, -4.2);
    glVertex2f(-0.1, -4.2);
    glVertex2f(-0.1, -4.8);
    glVertex2f(-0.1, -4.8);
    glVertex2f(-4.8, -4.8);
    glVertex2f(-4.8, -4.8);
    glVertex2f(-4.8, -0.6);
    glVertex2f(-4.8, -0.6);
    glVertex2f(-3.4, -0.6);
    glVertex2f(-3.4, -0.6);
    glVertex2f(-3.4, -0.8);
    glVertex2f(-3.4, -0.8);
    glVertex2f(-4.8, -0.8);
    glVertex2f(-4.8, -0.4);
    glVertex2f(-3.2, -0.4);
    glVertex2f(-3.2, -0.4);
    glVertex2f(-3.2, -1.0);
    glVertex2f(-3.2, -1.0);
    glVertex2f(-4.8, -1.0);
    //glVertex2f(3.2, -1.4);
    glEnd();

}

void Window::criarObjetoPrincipal() {
    float theta;
    glClear(GL_COLOR_BUFFER_BIT);

    // Circulo
    glColor3f(255, 255, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(personagemX + raioObjeto * cos(theta), personagemY + raioObjeto * sin(theta));
    }
    glEnd();

    // Triangulo
    glPushMatrix();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);

    if(abertoFechado == 0) {
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAltura);
    } else if(abertoFechado == 1) {
        glVertex2f(personagemX - personagemComprimento, personagemY+personagemAlturaAux);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemComprimento, personagemY-personagemAlturaAux);
        glVertex2f(personagemX - personagemComprimento, personagemY-personagemAlturaAux);
        glVertex2f(personagemX - personagemComprimento, personagemY+personagemAlturaAux);
    } else if (abertoFechado == 2) { // Objeto para o lado direito com a boca aberta
        glVertex2f(personagemX+20, personagemY+personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX+20, personagemY-personagemAltura);
        glVertex2f(personagemX+20, personagemY-personagemAltura);
        glVertex2f(personagemX+20, personagemY+personagemAltura);
    } else if (abertoFechado == 3) { // Objeto para o lado direito com a boca aberta
        glVertex2f(personagemX+20, personagemY+personagemAlturaAux);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX+20, personagemY-personagemAlturaAux);
        glVertex2f(personagemX+20, personagemY-personagemAlturaAux);
        glVertex2f(personagemX+20, personagemY+personagemAltura);
    } else if (abertoFechado == 4) { // Objeto para cima com a boca aberta
        glVertex2f(personagemX+100, personagemY+20);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX-90, personagemY+20);
        glVertex2f(personagemX-90, personagemY+20);
        glVertex2f(personagemX+100, personagemY+20);
    } else if (abertoFechado == 5) { // Objeto para cima com a boca fechada
        glVertex2f(personagemX+personagemAlturaAux, personagemY+20);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX-personagemAlturaAux, personagemY+20);
        glVertex2f(personagemX-personagemAlturaAux, personagemY+20);
        glVertex2f(personagemX-personagemAlturaAux, personagemY+20);
    } else if (abertoFechado == 6) { // Objeto para baixo com a boca fechada
        glVertex2f(personagemX+100, personagemY-20);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX-90, personagemY-20);
        glVertex2f(personagemX-90, personagemY-20);
        glVertex2f(personagemX+100, personagemY-20);
    } else if (abertoFechado == 7) { // Objeto para baixo com a boca fechada
        glVertex2f(personagemX+personagemAlturaAux, personagemY-20);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX-personagemAlturaAux, personagemY-20);
        glVertex2f(personagemX-personagemAlturaAux, personagemY-20);
        glVertex2f(personagemX-personagemAlturaAux, personagemY-20);
    }

    glEnd();
    glPopMatrix();
    glBegin(GL_QUADS);
    glColor3f(0,0,255);
    for(int l = 0; l<TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA ; c++) {
            if(blocos[l][c].rotulo == 'o'){
                glVertex2f(blocos[l][c].x, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y + blocos[l][c].alt);
                glVertex2f(blocos[l][c].x, blocos[l][c].y + blocos[l][c].alt);
            }
        }
    }
    glEnd();

//    if (abertoFechado == 0) { // Objeto para o lado esquerdo com a boca aberta
//        glVertex2f(230, 350);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(230, 150);
//        glVertex2f(230, 150);
//        glVertex2f(230, 350);
//    } else if (abertoFechado == 1) { // Objeto para o lado esquerdo com a boca fechado
//        glVertex2f(230, 255);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(230, 245);
//        glVertex2f(230, 245);
//        glVertex2f(230, 355);
//    } else if (abertoFechado == 2) { // Objeto para o lado direito com a boca aberta
//        glVertex2f(270, 350);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(270, 150);
//        glVertex2f(270, 150);
//        glVertex2f(270, 350);
//    } else if (abertoFechado == 3) { // Objeto para o lado direito com a boca aberta
//        glVertex2f(270, 255);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(270, 245);
//        glVertex2f(270, 245);
//        glVertex2f(270, 355);
//    } else if (abertoFechado == 4) { // Objeto para cima com a boca aberta
//        glVertex2f(350, 270);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(160, 270);
//        glVertex2f(160, 270);
//        glVertex2f(350, 270);
//    } else if (abertoFechado == 5) { // Objeto para cima com a boca fechada
//        glVertex2f(255, 270);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(245, 270);
//        glVertex2f(245, 270);
//        glVertex2f(245, 270);
//    } else if (abertoFechado == 6) { // Objeto para baixo com a boca fechada
//        glVertex2f(350, 230);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(160, 230);
//        glVertex2f(160, 230);
//        glVertex2f(350, 230);
//    } else if (abertoFechado == 7) { // Objeto para baixo com a boca fechada
//        glVertex2f(255, 230);
//        glVertex2f(250, 250);
//        glVertex2f(250, 250);
//        glVertex2f(245, 230);
//        glVertex2f(245, 230);
//        glVertex2f(245, 230);
//    }
    glEnd();
    glutSwapBuffers();
}

void Window::criarAnimacaoObjeto(int valor) {
    if (valor == 0) {
        abertoFechado = 1;
    } else if (valor == 1) {
        abertoFechado = 0;
    } else if (valor == 2) {
        abertoFechado = 3;
    } else if (valor == 3) {
        abertoFechado = 2;
    } else if (valor == 4) {
        abertoFechado = 5;
    } else if (valor == 5) {
        abertoFechado = 4;
    } else if (valor == 6) {
        abertoFechado = 7;
    } else if (valor == 7) {
        abertoFechado = 6;
    }
    criarObjetoPrincipal();
}

bool validaColisao(){
    for(int l = 0; l<TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA ; c++) {
            if(blocos[l][c].rotulo == 'o'){
//                glVertex2f(blocos[l][c].x, blocos[l][c].y);
//                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y);
//                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y + blocos[l][c].alt);
//                glVertex2f(blocos[l][c].x, blocos[l][c].y + blocos[l][c].alt);
                bool colisaoX = personagemX+(raioObjeto*1) >= blocos[l][c].x &&
                                blocos[l][c].x+(blocos[l][c].comp * 2)+3 >= personagemX;

                bool colisaoY = personagemY+(raioObjeto*1)>= blocos[l][c].y &&
                                blocos[l][c].y+(blocos[l][c].alt * 2)+3 >= personagemY;

                if(colisaoX && colisaoY){
                    return true;
                }
            }
        }
    }

    return false;
}


void Window::criarMovimentacaoTecladoObjeto(unsigned char key, int x, int y) {
    if (key == 97) { // tecla 'a' pressionada
        float auxiliar = personagemX;
        personagemX -= alteracaoPosicao;
        if(validaColisao()) {
            personagemX = auxiliar;
        }
        if(abertoFechado%2 == 0) {
            abertoFechado = 0;
        } else {
            abertoFechado = 1;
        }
    } else if (key == 100) { // tecla 'd' pressionada
        float auxiliar = personagemX;
        personagemX += alteracaoPosicao;
        if(validaColisao()) {
            personagemX = auxiliar;
        }
        if(abertoFechado%2 == 0) {
            abertoFechado = 2;
        } else {
            abertoFechado = 3;
        }
    } else if (key == 115) { // tecla 's' pressionada
        float auxiliar = personagemY;
        personagemY -= alteracaoPosicao;
        if(validaColisao()) {
            personagemY = auxiliar;
        }
        if(abertoFechado%2 == 0) {
            abertoFechado = 6;
        } else {
            abertoFechado = 7;
        }
    } else if (key == 119) { // tecla 'w' pressionada
        float auxiliar = personagemY;
        personagemY += alteracaoPosicao;
        if(validaColisao()) {
            personagemY = auxiliar;
        }
        if(abertoFechado%2 == 0) {
            abertoFechado = 4;
        } else {
            abertoFechado = 5;
        }
    }


//    if(personagemX < 20){
//        personagemX = 20;
//    } else if (personagemX+personagemComprimento > 510){
//        personagemX = 510 - personagemComprimento;
//    }

    glutTimerFunc(milisegundoTimer, criarAnimacaoObjeto, abertoFechado);
}



void Window::exibir(void) {
    criarMapaMatriz();
    criarObjetoPrincipal();
}
