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
float dimensaoCima = 550;
float alteracaoPosicaoPacman = 2;
float alteracaoPosicaoInimigo = 1;
int teste = 1;

//
int pontos = 0;
int quantidadeVidas = 3;

//
float personagemX = 250;
float personagemY = 307;
float personagemComprimento = 30;
float personagemAltura = 25;
float personagemAlturaAux = 5;
PersonagemPacman *Window::pacman = new PersonagemPacman(personagemX, personagemY, abertoFechado);
//
float raioObjeto = 11;


// Variavel auxiliar cor inimigo
float red = 50;
float green = 50;
float blue = 2;
int milisecMovimentoInimigos = 50;


/**
 * Construtor
 */
Window::Window() {
}


class Bloco {
public:
    float x;
    float y;
    float comp;
    float alt;
    char rotulo;
    char direcao;
};

Bloco blocos[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];
int matrizMapa[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];

void Window::iniciar(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(320, 50);
    glutCreateWindow("Pacman");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(dimensaoEsquerda, dimensaoDireita, dimensaoBaixo, dimensaoCima);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(this->exibir);
    glutTimerFunc(milisegundoTimer, this->criarAnimacaoObjeto, abertoFechado);
    glutTimerFunc(milisecMovimentoInimigos, this->criarAnimacaoInimigos, abertoFechado);
    glutKeyboardFunc(this->criarMovimentacaoTecladoObjeto);
    glutMainLoop();
}

void Window::criarMapaMatriz(void) {
    int x = 3;
    int y = 487;

    Arquivo arquivo;
    vector<Matriz> matrizAux = arquivo.carregar("../pacman.txt", TAMANHO_MATRIZ_MAPA);

    for (int z = 0; z < matrizAux.size(); z++) {
        matrizMapa[matrizAux[z].getLinha()][matrizAux[z].getColuna()] = matrizAux[z].getValor();
    }

    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++, x += 11) {
            if (matrizMapa[l][c] == 1) {
                blocos[l][c].rotulo = 'a';
                blocos[l][c].x = x;
                blocos[l][c].y = y;
                blocos[l][c].comp = 10;
                blocos[l][c].alt = 10;
            } else if (matrizMapa[l][c] == 2) {
                blocos[l][c].rotulo = 'b';
                blocos[l][c].x = x + 4;
                blocos[l][c].y = y + 4;
                blocos[l][c].comp = 3;
                blocos[l][c].alt = 3;
            } else if (matrizMapa[l][c] == 3) {
                blocos[l][c].rotulo = 'c';
                blocos[l][c].x = x + 5;
                blocos[l][c].y = y + 5;
                blocos[l][c].comp = 3;
                blocos[l][c].alt = 3;
                blocos[l][c].direcao = 'b';
            }
        }
        x = 3;
        y -= 11;
    }
}

void Window::criarObjetoPrincipal() {
    float theta;
    glClear(GL_COLOR_BUFFER_BIT);

    // Pontos
    glRasterPos2f(50, 520);
    glColor3f(255, 255, 255);
    string teste = "PONTOS: " + to_string(pontos);
    for (int i = 0; i < teste.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, teste[i]);
    }


    // Quantidade de vidas
    float posicaoXAux = 150;
    float posicaoYAux = 525;
    glColor3f(255, 255, 0);
    for(int x =0; x<quantidadeVidas;x++){
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            theta = i * 3.142 / 180;
            glVertex2f(posicaoXAux + raioObjeto * cos(theta), posicaoYAux + raioObjeto * sin(theta));
        }
        posicaoXAux += raioObjeto*2.2;
        glEnd();
    }



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

    if (abertoFechado == 0) { // Objeto para o lado esquerdo com a boca aberta
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAltura);
    } else if (abertoFechado == 1) { // Objeto para o lado esquerdo com a boca fechada
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAlturaAux);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAlturaAux);
        glVertex2f(personagemX - personagemComprimento, personagemY - personagemAlturaAux);
        glVertex2f(personagemX - personagemComprimento, personagemY + personagemAlturaAux);
    } else if (abertoFechado == 2) { // Objeto para o lado direito com a boca aberta
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAltura);
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAltura);
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAltura);
    } else if (abertoFechado == 3) { // Objeto para o lado direito com a boca fechada
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAlturaAux);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAlturaAux);
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAlturaAux);
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAltura);
    } else if (abertoFechado == 4) { // Objeto para cima com a boca aberta
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemAltura, personagemY + personagemAltura);
        glVertex2f(personagemX - personagemAltura, personagemY + personagemAltura);
        glVertex2f(personagemX + personagemAltura, personagemY + personagemAltura);
    } else if (abertoFechado == 5) { // Objeto para cima com a boca fechada
        glVertex2f(personagemX + personagemAlturaAux, personagemY + personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemAlturaAux, personagemY + personagemAltura);
        glVertex2f(personagemX - personagemAlturaAux, personagemY + personagemAltura);
        glVertex2f(personagemX - personagemAlturaAux, personagemY + personagemAltura);
    } else if (abertoFechado == 6) { // Objeto para baixo com a boca aberta
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemAltura, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemAltura, personagemY - personagemAltura);
        glVertex2f(personagemX + personagemAltura, personagemY - personagemAltura);
    } else if (abertoFechado == 7) { // Objeto para baixo com a boca fechada
        glVertex2f(personagemX + personagemAlturaAux, personagemY - personagemAltura);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX, personagemY);
        glVertex2f(personagemX - personagemAlturaAux, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemAlturaAux, personagemY - personagemAltura);
        glVertex2f(personagemX - personagemAlturaAux, personagemY - personagemAltura);
    }
    glEnd();
    glPopMatrix();


    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            if (blocos[l][c].rotulo == 'a') {
                glBegin(GL_QUADS);
                glColor3f(0, 0, 255);
                glVertex2f(blocos[l][c].x, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y + blocos[l][c].alt);
                glVertex2f(blocos[l][c].x, blocos[l][c].y + blocos[l][c].alt);
                glEnd();
            } else if (blocos[l][c].rotulo == 'b') {
                glBegin(GL_QUADS);
                glColor3f(255, 255, 255);
                glVertex2f(blocos[l][c].x, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y);
                glVertex2f(blocos[l][c].x + blocos[l][c].comp, blocos[l][c].y + blocos[l][c].alt);
                glVertex2f(blocos[l][c].x, blocos[l][c].y + blocos[l][c].alt);
                glEnd();
            } else if (blocos[l][c].rotulo == 'c') {
                glColor3f(red, green, blue);
                glBegin(GL_POLYGON);
                for (int i = 0; i < 360; i++) {
                    theta = i * 3.142 / 180;
                    glVertex2f(blocos[l][c].x + raioObjeto * cos(theta), blocos[l][c].y + raioObjeto * sin(theta));
                }
                glEnd();
                red = +50;
                green = +2;
                blue = +20;
            }
        }
    }

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

bool validacaoColisaoDosInimigos(float posicaoX, float posicaoY) {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {

            // Colisão com as paredes do mapa
            if (blocos[l][c].rotulo == 'a') {
                bool colisaoX = posicaoX + raioObjeto >= blocos[l][c].x - 3 &&
                                blocos[l][c].x + (blocos[l][c].comp * 2) + 6 >= posicaoX;
                bool colisaoY = posicaoY + raioObjeto >= blocos[l][c].y - 3 &&
                                blocos[l][c].y + (blocos[l][c].alt * 2) + 7 >= posicaoY;
                if (colisaoX && colisaoY) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Window::criarAnimacaoInimigos(int valor) {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            if (blocos[l][c].rotulo == 'c') {
                if (blocos[l][c].direcao == 'e') {
                    if (!validacaoColisaoDosInimigos(blocos[l][c].x, blocos[l][c].y - (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'b';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x - (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'e';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y + (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'c';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x + (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'd';
                    }
                } else if (blocos[l][c].direcao == 'd') {
                    if (!validacaoColisaoDosInimigos(blocos[l][c].x, blocos[l][c].y + (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'c';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x + (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'd';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y - (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'b';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x - (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'e';
                    }
                } else if (blocos[l][c].direcao == 'c') {
                    if (!validacaoColisaoDosInimigos(blocos[l][c].x - (alteracaoPosicaoInimigo + 5), blocos[l][c].y)) {
                        blocos[l][c].x -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'e';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y + (alteracaoPosicaoPacman))) {
                        blocos[l][c].y += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'c';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x + (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'd';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y - (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'b';
                    }

                } else if (blocos[l][c].direcao == 'b') {
                    if (!validacaoColisaoDosInimigos(blocos[l][c].x + (alteracaoPosicaoInimigo + 5), blocos[l][c].y)) {
                        blocos[l][c].x += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'd';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y - (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'b';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x - (alteracaoPosicaoInimigo + 5),
                                                            blocos[l][c].y)) {
                        blocos[l][c].x -= alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'e';
                    } else if (!validacaoColisaoDosInimigos(blocos[l][c].x,
                                                            blocos[l][c].y + (alteracaoPosicaoInimigo + 5))) {
                        blocos[l][c].y += alteracaoPosicaoInimigo;
                        blocos[l][c].direcao = 'c';
                    }
                }
            }
        }
    }
    criarObjetoPrincipal();
    glutTimerFunc(milisecMovimentoInimigos, criarAnimacaoInimigos, abertoFechado);
}


bool validaColisaoInimigos() {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com as paredes do mapa
            if (blocos[l][c].rotulo == 'c') {
                bool colisaoX = personagemX + raioObjeto >= blocos[l][c].x - 3 &&
                                blocos[l][c].x + (blocos[l][c].comp * 2) + 6 >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= blocos[l][c].y - 3 &&
                                blocos[l][c].y + (blocos[l][c].alt * 2) + 7 >= personagemY;
                if (colisaoX && colisaoY) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool validaColisaoParedes() {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com as paredes do mapa
            if (blocos[l][c].rotulo == 'a') {
                bool colisaoX = personagemX + raioObjeto >= blocos[l][c].x - 3 &&
                                blocos[l][c].x + (blocos[l][c].comp * 2) + 6 >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= blocos[l][c].y - 3 &&
                                blocos[l][c].y + (blocos[l][c].alt * 2) + 7 >= personagemY;
                if (colisaoX && colisaoY) {
                    return true;
                }
            }
        }
    }
    return false;
}

void validacaoColisaoColeta() {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com objetos de coleta
            if (blocos[l][c].rotulo == 'b') {
                bool colisaoX = personagemX >= blocos[l][c].x &&
                                blocos[l][c].x + blocos[l][c].comp >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= blocos[l][c].y &&
                                blocos[l][c].y + blocos[l][c].alt >= personagemY;
                if (colisaoX && colisaoY) {
                    blocos[l][c].rotulo = 'l';
                    pontos++;
                }
            }
        }
    }
}


void Window::criarMovimentacaoTecladoObjeto(unsigned char key, int x, int y) {
    if (key == 97) { // tecla 'a' pressionada
        float auxiliar = personagemX;
        personagemX -= alteracaoPosicaoPacman;
        if (validaColisaoParedes()) {
            personagemX = auxiliar;
        }

        if (validaColisaoInimigos()) {
            personagemX = 250;
            personagemY = 307;
            quantidadeVidas--;
        }

        // Trata colisão de coleta
        validacaoColisaoColeta();


        if (abertoFechado % 2 == 0) {
            abertoFechado = 0;
        } else {
            abertoFechado = 1;
        }
    } else if (key == 100) { // tecla 'd' pressionada
        float auxiliar = personagemX;
        personagemX += alteracaoPosicaoPacman;
        if (validaColisaoParedes()) {
            personagemX = auxiliar;
        }

        if (validaColisaoInimigos()) {
            personagemX = 250;
            personagemY = 307;
            quantidadeVidas--;
        }

        // Trata colisão de coleta
        validacaoColisaoColeta();

        if (abertoFechado % 2 == 0) {
            abertoFechado = 2;
        } else {
            abertoFechado = 3;
        }
    } else if (key == 115) { // tecla 's' pressionada
        float auxiliar = personagemY;
        personagemY -= alteracaoPosicaoPacman;

        if (validaColisaoParedes()) {
            personagemY = auxiliar;
        }

        if (validaColisaoInimigos()) {
            personagemX = 250;
            personagemY = 307;
        }

        // Trata colisão de coleta
        validacaoColisaoColeta();

        if (abertoFechado % 2 == 0) {
            abertoFechado = 6;
        } else {
            abertoFechado = 7;
        }
    } else if (key == 119) { // tecla 'w' pressionada
        float auxiliar = personagemY;
        personagemY += alteracaoPosicaoPacman;
        if (validaColisaoParedes()) {
            personagemY = auxiliar;
        }

        if (validaColisaoInimigos()) {
            personagemX = 250;
            personagemY = 307;
            quantidadeVidas--;
        }

        // Trata colisão de coleta
        validacaoColisaoColeta();

        if (abertoFechado % 2 == 0) {
            abertoFechado = 4;
        } else {
            abertoFechado = 5;
        }
    }
    glutTimerFunc(milisegundoTimer, criarAnimacaoObjeto, abertoFechado);
}


void Window::exibir(void) {
    criarMapaMatriz();
    criarObjetoPrincipal();
}
