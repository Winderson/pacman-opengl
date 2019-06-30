#include <iostream>
#include <fstream>
#include <string>
#include "window.h"

using namespace std;


int Window::abertoFechado = 2;
int Window::milisegundoTimer = 150;

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

// Variavel responsavel pela definição do mapa corrente
int mapaCorrente = 1;

// Variavel responsavel pela exibicao da intro
bool intro = false;
bool triangulos = false;
bool flagMudancaMapa = true;

// Variavel direcao
int direcaoPacman = 0;
bool cameraAtiva = false;

bool animacoesSetadas = false;

Objeto objetos[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];
int matrizMapa1[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];
int matrizMapa2[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA];

/**
 * Configurações de inicialização
 * @param argc
 * @param argv
 */
void Window::iniciar(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(420, 50);
    glutCreateWindow("Pacman");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(dimensaoEsquerda, dimensaoDireita, dimensaoBaixo, dimensaoCima);
    glutDisplayFunc(this->exibir);
    glutMainLoop();
}

void Window::criarIntro() {
    glClear(GL_COLOR_BUFFER_BIT);
    criarTextoIntro();
    criarPersonagemPacman();
    //glutTimerFunc(milisegundoTimer, criarAnimacaoPacmanIntro, abertoFechado);
    glutSwapBuffers();
}

/**
 * Efetua a criação de matriz do mapa 1 de inteiros a partir do
 * vector de vector retornado na leitura do arquivo
 */
void Window::criarMapa1Matriz(void) {
    Arquivo arquivo;
    vector<Matriz> matrizAux1 = arquivo.carregar("../pacman_mapa1.txt", TAMANHO_MATRIZ_MAPA);

    // Define a matriz do mapa 1
    for (int z = 0; z < matrizAux1.size(); z++) {
        matrizMapa1[matrizAux1[z].getLinha()][matrizAux1[z].getColuna()] = matrizAux1[z].getValor();
    }

    converterMapaMatriz(matrizMapa1);
}

/**
 * Efetua a criação de matriz do mapa 2 de inteiros a partir do
 * vector de vector retornado na leitura do arquivo
 */
void Window::criarMapa2Matriz() {
    Arquivo arquivo;
    vector<Matriz> matrizAux2 = arquivo.carregar("../pacman_mapa2.txt", TAMANHO_MATRIZ_MAPA);
    // Define a matriz do mapa 2
    for (int z = 0; z < matrizAux2.size(); z++) {
        matrizMapa2[matrizAux2[z].getLinha()][matrizAux2[z].getColuna()] = matrizAux2[z].getValor();
    }

    converterMapaMatriz(matrizMapa2);
}

/**
 * Efetua a conversão da matriz de inteiros para a matriz de objetos
 * definindo as posições, o rotulo, o comprimento e a altura para cada
 * objeto presente na matriz
 * @param matrizMapa1
 */
void Window::converterMapaMatriz(int matrizMapa[TAMANHO_MATRIZ_MAPA][TAMANHO_MATRIZ_MAPA]) {
    int x = 3;
    int y = 487;
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++, x += 11) {
            if (matrizMapa[l][c] == 1) {
                objetos[l][c].setRotulo('a');
                objetos[l][c].setPosicaoX(x);
                objetos[l][c].setPosicaoY(y);
                objetos[l][c].setComprimento(10);
                objetos[l][c].setAltura(10);
            } else if (matrizMapa[l][c] == 2) {
                objetos[l][c].setRotulo('b');
                objetos[l][c].setPosicaoX(x + 4);
                objetos[l][c].setPosicaoY(y + 4);
                objetos[l][c].setComprimento(3);
                objetos[l][c].setAltura(3);
            } else if (matrizMapa[l][c] == 3) {
                objetos[l][c].setRotulo('c');
                objetos[l][c].setPosicaoX(x + 5);
                objetos[l][c].setPosicaoY(y + 5);
                objetos[l][c].setComprimento(3);
                objetos[l][c].setAltura(3);
                objetos[l][c].setDirecao('b');
            } else if (matrizMapa[l][c] == 4) {
                objetos[l][c].setRotulo('d');
                objetos[l][c].setPosicaoX(x);
                objetos[l][c].setPosicaoY(y);
                objetos[l][c].setComprimento(10);
                objetos[l][c].setAltura(10);
            } else {
                objetos[l][c].setRotulo(' ');
                objetos[l][c].setPosicaoX(0);
                objetos[l][c].setPosicaoY(0);
                objetos[l][c].setComprimento(0);
                objetos[l][c].setAltura(0);
            }
        }
        x = 3;
        y -= 11;
    }
}

/**
 * Desenho do personagem pacman
 */
void Window::criarPersonagemPacman() {
    float theta;

    if(!flagMudancaMapa){
        flagMudancaMapa = true;
        for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
            for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
                if(objetos[l][c].getRotulo() == 'd'){
                    if(mapaCorrente == 2) {
                        personagemX = objetos[l][c].getPosicaoX() + 10;
                        personagemY = objetos[l][c].getPosicaoY() + 6;
                    } else {
                        personagemX = objetos[l][c].getPosicaoX() - 10;
                        personagemY = objetos[l][c].getPosicaoY() + 6;
                    }
                    break;
                }
            }
        }
    }


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
}

/**
 * Desenho das informações de pontos e quantidade de vidas
 */
void Window::criarPainelInformacoes() {
    float theta;
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
    for (int x = 0; x < quantidadeVidas; x++) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            theta = i * 3.142 / 180;
            glVertex2f(posicaoXAux + raioObjeto * cos(theta), posicaoYAux + raioObjeto * sin(theta));
        }
        posicaoXAux += raioObjeto * 2.2;
        glEnd();
    }
}

/**
 * Desenho dos objetos mapeados na matriz dos arquivos de
 * mapas
 */
void Window::criarObjetosMatriz(void) {
    float theta;
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            if (objetos[l][c].getRotulo() == 'a') {
                glBegin(GL_QUADS);
                if (mapaCorrente == 1)
                    glColor3f(0, 0, 255);
                else if (mapaCorrente == 2) {
                    glColor3f(0, 255, 0);
                }
                glVertex2f(objetos[l][c].getPosicaoX(), objetos[l][c].getPosicaoY());
                glVertex2f(objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento(), objetos[l][c].getPosicaoY());
                glVertex2f(objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento(),
                           objetos[l][c].getPosicaoY() + objetos[l][c].getAltura());
                glVertex2f(objetos[l][c].getPosicaoX(), objetos[l][c].getPosicaoY() + objetos[l][c].getAltura());
                glEnd();
            } else if (objetos[l][c].getRotulo() == 'b') {
                glBegin(GL_QUADS);
                glColor3f(255, 255, 255);
                glVertex2f(objetos[l][c].getPosicaoX(), objetos[l][c].getPosicaoY());
                glVertex2f(objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento(), objetos[l][c].getPosicaoY());
                glVertex2f(objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento(),
                           objetos[l][c].getPosicaoY() + objetos[l][c].getAltura());
                glVertex2f(objetos[l][c].getPosicaoX(), objetos[l][c].getPosicaoY() + objetos[l][c].getAltura());
                glEnd();
            } else if (objetos[l][c].getRotulo() == 'c') {
                glColor3f(244, 144, 255);
                glBegin(GL_POLYGON);
                for (int i = 0; i < 360; i++) {
                    theta = i * 3.142 / 180;
                    glVertex2f(objetos[l][c].getPosicaoX() + raioObjeto * cos(theta),
                               objetos[l][c].getPosicaoY() + raioObjeto * sin(theta));
                }
                glEnd();
                red += 50;
                green += 2;
                blue += 20;
            }
        }
    }
}

/**
 * Efetua a criação do cenario
 */
void Window::criarCenario() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Criação de painel de informações
    criarPainelInformacoes();

    // Criação do personagem pacman
    criarPersonagemPacman();

    // Criação dos objetos da matriz
    criarObjetosMatriz();
    glutSwapBuffers();
}

/**
 * Efetua a criação da animação do pacman
 * ato de abrir e fechar a boca
 * @param valor
 */
void Window::criarAnimacaoPacman(int valor) {
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
    criarCenario();
}

void Window::validacaoColisaoTrocaMapa() {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com as paredes do mapa
            if (objetos[l][c].getRotulo() == 'd') {
//                bool colisaoX = personagemX - raioObjeto >= objetos[l][c].getPosicaoX() &&
//                                objetos[l][c].getPosicaoX() + (objetos[l][c].getComprimento()) >=
//                                personagemX - raioObjeto;
//                bool colisaoY = personagemY - raioObjeto >= objetos[l][c].getPosicaoY() &&
//                                objetos[l][c].getPosicaoY() + (objetos[l][c].getAltura()) >= personagemY - raioObjeto;
                bool colisaoX = personagemX >= objetos[l][c].getPosicaoX() &&
                                objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento() >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= objetos[l][c].getPosicaoY() &&
                                objetos[l][c].getPosicaoY() + objetos[l][c].getAltura() >= personagemY;
                if (colisaoX && colisaoY) {
                    if(mapaCorrente == 1){
                        mapaCorrente = 2;
                    } else {
                        mapaCorrente = 1;
                    }
                    flagMudancaMapa = false;
                    glutPostRedisplay();
                }
            }
        }
    }
}

void Window::mudarCamera(){
    if(cameraAtiva){
        dimensaoDireita = 500;
        dimensaoEsquerda = 0;
        dimensaoCima = 500;
        dimensaoBaixo = 0;
        cameraAtiva = false;
    } else {
        dimensaoDireita = personagemX+125;
        dimensaoEsquerda = personagemX-125;
        dimensaoBaixo = personagemY-125;
        dimensaoCima = personagemY+125;
        cameraAtiva = true;
    }
}

bool validacaoColisaoDosInimigos(float posicaoX, float posicaoY) {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com as paredes do mapa
            if (objetos[l][c].getRotulo() == 'a') {
                bool colisaoX = posicaoX + raioObjeto >= objetos[l][c].getPosicaoX() - 3 &&
                                objetos[l][c].getPosicaoX() + (objetos[l][c].getComprimento() * 2) + 6 >= posicaoX;
                bool colisaoY = posicaoY + raioObjeto >= objetos[l][c].getPosicaoY() - 3 &&
                                objetos[l][c].getPosicaoY() + (objetos[l][c].getAltura() * 2) + 7 >= posicaoY;
                if (colisaoX && colisaoY) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Window::criarTriangulosAleatorios() {
    glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    int numeroAleatorio = rand() % 100;

    //for(int indice=0; indice<numeroAleatorio;indice++){

    //glTranslatef(100.0, 100.0, 0.0);
    //glRotatef(90,0,0,0);
    glScaled(1,2,1);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(250, 350);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(190, 250);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(320, 250);
    glEnd();
    //}
    glutSwapBuffers();
}

void Window::criarTextoIntro() {
    glRasterPos2f(200, 250);
    glColor3f(0, 0, 255);
    glRasterPos2f(200, 250);
    string texto = "PACMAN";
    for (int i = 0; i < texto.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }

    glColor3f(255, 255, 0);
    glRasterPos2f(210, 220);
    string textoOpcao1 = "<<< PLAY >>>";
    for (int i = 0; i < textoOpcao1.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoOpcao1[i]);
    }

//    glColor3f(255, 255, 0);
//    glRasterPos2f(220, 190);
//    string textoOpcao2 = "Triangulos.";
//    for (int i = 0; i < textoOpcao2.size(); i++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoOpcao2[i]);
//    }


    glColor3f(0, 255, 0);
    glRasterPos2f(140, 70);
    string texto2 = "Computacao Grafica / Prof.: Diogenes";
    for (int i = 0; i < texto2.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto2[i]);
    }

    glColor3f(255, 255, 0);
    glRasterPos2f(142, 50);
    string texto3 = "Winderson Jose Barboza dos Santos";
    for (int i = 0; i < texto2.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto3[i]);
    }
}

void Window::criarAnimacaoPacmanIntro(int valor) {
    if (valor == 2) {
        abertoFechado = 3;
    } else {
        abertoFechado = 2;
    }

    if (personagemX < 250) {
        personagemX += alteracaoPosicaoPacman;
    }

    // Criação do personagem pacman
    criarIntro();
}

void Window::criarAnimacaoInimigos(int valor) {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            if (objetos[l][c].getRotulo() == 'c') {
                if (objetos[l][c].getDirecao() == 'e') {
                    if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                     objetos[l][c].getPosicaoY() - (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('b');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() - (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('e');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() +
                                                            (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('c');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() + (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('d');
                    }
                } else if (objetos[l][c].getDirecao() == 'd') {
                    if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                     objetos[l][c].getPosicaoY() + (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('c');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() + (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('d');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() -
                                                            (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('b');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() - (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('e');
                    }
                } else if (objetos[l][c].getDirecao() == 'c') {
                    if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() - (alteracaoPosicaoInimigo + 5),
                                                     objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('e');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() + (alteracaoPosicaoPacman))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('c');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() + (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('d');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() -
                                                            (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('b');
                    }

                } else if (objetos[l][c].getDirecao() == 'b') {
                    if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() + (alteracaoPosicaoInimigo + 5),
                                                     objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('d');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() -
                                                            (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('b');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX() - (alteracaoPosicaoInimigo + 5),
                                                            objetos[l][c].getPosicaoY())) {
                        objetos[l][c].setPosicaoX(objetos[l][c].getPosicaoX() - alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('e');
                    } else if (!validacaoColisaoDosInimigos(objetos[l][c].getPosicaoX(),
                                                            objetos[l][c].getPosicaoY() +
                                                            (alteracaoPosicaoInimigo + 5))) {
                        objetos[l][c].setPosicaoY(objetos[l][c].getPosicaoY() + alteracaoPosicaoInimigo);
                        objetos[l][c].setDirecao('c');
                    }
                }
            }
        }
    }
    criarCenario();
    //glutPostRedisplay();
    glutTimerFunc(milisecMovimentoInimigos, criarAnimacaoInimigos, abertoFechado);
}


bool validaColisaoInimigos() {
    for (int l = 0; l < TAMANHO_MATRIZ_MAPA; l++) {
        for (int c = 0; c < TAMANHO_MATRIZ_MAPA; c++) {
            // Colisão com as paredes do mapa
            if (objetos[l][c].getRotulo() == 'c') {
                bool colisaoX = personagemX + raioObjeto >= objetos[l][c].getPosicaoX() - 3 &&
                                objetos[l][c].getPosicaoX() + (objetos[l][c].getComprimento() * 2) + 6 >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= objetos[l][c].getPosicaoY() - 3 &&
                                objetos[l][c].getPosicaoY() + (objetos[l][c].getAltura() * 2) + 7 >= personagemY;
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
            if (objetos[l][c].getRotulo() == 'a') {
                bool colisaoX = personagemX + raioObjeto >= objetos[l][c].getPosicaoX() - 3 &&
                                objetos[l][c].getPosicaoX() + (objetos[l][c].getComprimento() * 2) + 6 >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= objetos[l][c].getPosicaoY() - 3 &&
                                objetos[l][c].getPosicaoY() + (objetos[l][c].getAltura() * 2) + 7 >= personagemY;
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
            if (objetos[l][c].getRotulo() == 'b') {
                bool colisaoX = personagemX >= objetos[l][c].getPosicaoX() &&
                                objetos[l][c].getPosicaoX() + objetos[l][c].getComprimento() >= personagemX;
                bool colisaoY = personagemY + raioObjeto >= objetos[l][c].getPosicaoY() &&
                                objetos[l][c].getPosicaoY() + objetos[l][c].getAltura() >= personagemY;
                if (colisaoX && colisaoY) {
                    objetos[l][c].setRotulo('l');
                    pontos++;
                }
            }
        }
    }
}

void Window::criarAcaoMouse(int button, int state, int x, int y) {
    int aux = 0;
    if (x >= 215 && x <= 306 && y >= 220 && y < 298) {
        intro = true;
        raioObjeto = 11;
        alteracaoPosicaoPacman = 2;
        personagemX = 250;
        glutPostRedisplay();
    } else if (x >= 230 && x <= 306 && y >= 312 && y <= 324) {
        triangulos = true;
        intro = false;
    }
}

void Window::criarAnimacaoMovimentoPacman(char direcao){

    while(!validaColisaoParedes()) {
        if (direcao == 'E') {
            personagemX -= alteracaoPosicaoPacman;
        } else if (direcao == 'D') {
            personagemX += alteracaoPosicaoPacman;
        } else if (direcao == 'C') {
            personagemY += alteracaoPosicaoPacman;
        } else if (direcao == 'B') {
            personagemY -= alteracaoPosicaoPacman;
        }
    }

}

void Window::criarMovimentacaoTecladoObjeto(unsigned char key, int x, int y) {
    if(key == 99) { //tecla 'c'
        mudarCamera();
        glLoadIdentity();
        gluOrtho2D(dimensaoEsquerda, dimensaoDireita, dimensaoBaixo, dimensaoCima);
    } else if (key == 97) { // tecla 'a' pressionada
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

        // Trata colisão mudanca de mapa
        validacaoColisaoTrocaMapa();

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

        // Trata colisão mudanca de mapa
        validacaoColisaoTrocaMapa();

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

        // Trata colisão mudanca de mapa
        validacaoColisaoTrocaMapa();

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

        // Trata colisão mudanca de mapa
        validacaoColisaoTrocaMapa();

        if (abertoFechado % 2 == 0) {
            abertoFechado = 4;
        } else {
            abertoFechado = 5;
        }
    }

    if(cameraAtiva) {
        dimensaoDireita = personagemX + 125;
        dimensaoEsquerda = personagemX - 125;
        dimensaoBaixo = personagemY - 125;
        dimensaoCima = personagemY + 125;
        glLoadIdentity();
        gluOrtho2D(dimensaoEsquerda, dimensaoDireita, dimensaoBaixo, dimensaoCima);
    }

    // Criação de timer
    glutTimerFunc(milisegundoTimer, criarAnimacaoPacman, abertoFechado);
}


/**
 * Efetua a exibição
 */
void Window::exibir(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    if (!triangulos) {
        if (intro) {
            if (mapaCorrente == 1) {
                criarMapa1Matriz();
            } else if (mapaCorrente == 2) {
                criarMapa2Matriz();
            }

            if(!animacoesSetadas) {
                glutTimerFunc(milisegundoTimer, criarAnimacaoPacman, abertoFechado);
                glutTimerFunc(milisecMovimentoInimigos, criarAnimacaoInimigos, abertoFechado);
                glutKeyboardFunc(criarMovimentacaoTecladoObjeto);
                animacoesSetadas = true;
            }
        } else {
            raioObjeto = 25;
            //alteracaoPosicaoPacman = 20;
            //personagemX = 250;
            glutMouseFunc(criarAcaoMouse);
            criarIntro();
        }
    } else {
        criarTriangulosAleatorios();
    }
}
