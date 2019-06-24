#include "windowExercicios.h"

float WindowExercicios::translacaoPositiva = 20;
float WindowExercicios::translacaoNegativa = -20;
float WindowExercicios::escalaPositiva = 0.1;
float WindowExercicios::escalaNegativa = -0.1;
int quantidadeTriangulos = 0;

Objeto objetosOriginais[45][45];
Objeto objetosHegonos[3][3];


void WindowExercicios::iniciar(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(420, 50);
    glutCreateWindow("Exercicios");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glutTimerFunc(1000, criarTriangulosAleatorios, 1);
    this->criarTriangulosAleatorios();
    this->criarHexagonos();
    glutDisplayFunc(this->exibir);
    //glutTimerFunc(1000, criarTriangulosAleatorios, 5);
    glutSpecialFunc(this->criarMovimentoTecladoEspecial);
    glutKeyboardFunc(this->criarMovimentoTeclado);
    glutMainLoop();
}

void WindowExercicios::exibir() {
    glClear(GL_COLOR_BUFFER_BIT);
    //criarTriangulo();
    //exibirTriangulos();
    exibirHexagonos();
    glutTimerFunc(350, movimentoHexagono, 0);
    glutSwapBuffers();
}

void WindowExercicios::exibirTriangulos() {
    int opcao = 0;
    int qt1 = 0;
    int qt2 = 0;
    int qt3 = 0;
    int qt4 = 0;
    int qt5 = 0;
    int qt6 = 0;
    int qt7 = 0;

    for (int l = 0; l < quantidadeTriangulos; l++) {
        for (int c = 0; c < quantidadeTriangulos; c++) {
            int total = quantidadeTriangulos / 5;
            if (qt1 <= total && opcao == 0) {
                int translacao = rand() % 50 + 10;
                glTranslatef(0, 20, 0);
                opcao = 1;
            } else if (qt2 <= total && opcao == 1) {
                glScalef(1.1, 1.1, 1);
                opcao = 2;
            } else if (qt3 <= total && opcao == 2) {
                glScalef(1.5, 1.5, 1);
                opcao = 3;
            } else if (qt4 <= total && opcao == 3) {
                glScalef(0.9, 0.9, 1);
                opcao = 4;
            } else if (qt5 <= total && opcao == 4) {
                glTranslatef(20, 0, 0);
                opcao = 5;
            } else if (qt6 <= total && opcao == 5) {
                glTranslatef(0, -20, 0);
                opcao = 6;
            } else if (qt7 <= total && opcao == 6) {
                glTranslatef(-20, 0, 0);
                opcao = 0;
            }
            glBegin(GL_TRIANGLES);
            glColor3f(objetosOriginais[l][c].getRed(), objetosOriginais[l][c].getGreen(),
                      objetosOriginais[l][c].getBlue());
            glVertex2i(objetosOriginais[l][c].getPosicaoX(),
                       objetosOriginais[l][c].getPosicaoY() + objetosOriginais[l][c].getAltura());
            glVertex2i(objetosOriginais[l][c].getPosicaoX() - objetosOriginais[l][c].getComprimento(),
                       objetosOriginais[l][c].getPosicaoY());
            glVertex2i(objetosOriginais[l][c].getPosicaoX() + objetosOriginais[l][c].getComprimento(),
                       objetosOriginais[l][c].getPosicaoY());
            glEnd();
        }
    }
}

void WindowExercicios::exibirHexagonos() {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (objetosHegonos[l][c].getRotulo() == 'h') {
                glBegin(GL_POLYGON);
                glColor3f(1.0, 0.0, 0.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX(), objetosHegonos[l][c].getPosicaoY());
                glColor3f(0.0, 1.0, 0.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX() - 25, objetosHegonos[l][c].getPosicaoY() - 25);
                glColor3f(0.0, 0.0, 1.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX(),
                           objetosHegonos[l][c].getPosicaoY() - objetosHegonos[l][c].getAltura());
                glColor3f(1.0, 0.0, 0.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX() + objetosHegonos[l][c].getComprimento(),
                           objetosHegonos[l][c].getPosicaoY() - objetosHegonos[l][c].getAltura());
                glColor3f(0.0, 1.0, 0.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX() + objetosHegonos[l][c].getComprimento() + 25,
                           objetosHegonos[l][c].getPosicaoY() - 25);
                glColor3f(0.0, 0.0, 1.0);
                glVertex2i(objetosHegonos[l][c].getPosicaoX() + objetosHegonos[l][c].getComprimento(),
                           objetosHegonos[l][c].getPosicaoY());
                glEnd();
            }
        }
    }
}

void WindowExercicios::criarMovimentoTeclado(unsigned char key, int x, int y) {
    if (key == 43) { //+
        glScalef(1.1, 1.1, 1);
        //glScalef(1.1, 0.9, 1);
    } else if (key == 45) { //-
        glScalef(0.9, 0.9, 1);

    } else if (key == 97) { // a
        glTranslatef(0, translacaoPositiva, 0);
    } else if (key == 100) { // d
        glTranslatef(0, translacaoNegativa, 0);
    }
    glutPostRedisplay();
}

void WindowExercicios::criarTriangulo() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(250, 350);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(190, 250);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(320, 250);
    glEnd();
}

void WindowExercicios::criarMovimentoTecladoEspecial(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        glTranslatef(translacaoNegativa, 0, 0);
    } else if (key == GLUT_KEY_RIGHT) {
        glTranslatef(translacaoPositiva, 0, 0);
    } else if (key == GLUT_KEY_UP) {
        glTranslatef(0, translacaoPositiva, 0);
    } else if (key == GLUT_KEY_DOWN) {
        glTranslatef(0, translacaoNegativa, 0);
    }
    glutPostRedisplay();
}

void WindowExercicios::criarTriangulosAleatorios() {
    int x = 100;
    int y = 100;
    quantidadeTriangulos = rand() % 40 + 15;
    for (int l = 0; l < quantidadeTriangulos; l++) {
        for (int c = 0; c < quantidadeTriangulos; c++, x += 15) {
            objetosOriginais[l][c].setPosicaoX(x);
            objetosOriginais[l][c].setPosicaoY(y);
            objetosOriginais[l][c].setComprimento(60);
            objetosOriginais[l][c].setAltura(100);
            objetosOriginais[l][c].setRed(rand() % 3);
            objetosOriginais[l][c].setGreen(rand() % 3);
            objetosOriginais[l][c].setBlue(rand() % 3);
        }
        x = 100;
        y -= 11;
    }
}

void WindowExercicios::criarHexagonos() {
    int x = 225;
    int y = 387;
    bool objetoMovimentoCima = false;
    for (int l = 0; l < 3; l++) {
        objetosHegonos[l][1].setRotulo('h');
        objetosHegonos[l][1].setPosicaoX(x);
        objetosHegonos[l][1].setPosicaoY(y);
        objetosHegonos[l][1].setComprimento(50);
        objetosHegonos[l][1].setAltura(50);

        if(!objetoMovimentoCima){
            objetosHegonos[l][1].setDirecao('c');
            objetoMovimentoCima = true;
        } else {
            objetosHegonos[l][1].setDirecao('e');
        }

        x = 225;
        y -= 100;
    }
    glEnd();
}

void WindowExercicios::movimentoHexagono(int valor) {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (objetosHegonos[l][c].getRotulo() == 'h') {
                float posX = objetosHegonos[l][c].getPosicaoX() + objetosHegonos[l][c].getComprimento();
                float posY = objetosHegonos[l][c].getPosicaoY() + objetosHegonos[l][c].getAltura();
                if (objetosHegonos[l][c].getDirecao() == 'd') {
                    if (!validaColisaoHexagono(posX + 20, posY)) {
                        objetosHegonos[l][c].setPosicaoX(objetosHegonos[l][c].getPosicaoX() + 20);
                    } else {
                        objetosHegonos[l][c].setDirecao('e');
                    }
                } else if (objetosHegonos[l][c].getDirecao() == 'e') {
                    if (!validaColisaoHexagono(posX - 20, posY)) {
                        objetosHegonos[l][c].setPosicaoX(objetosHegonos[l][c].getPosicaoX() - 20);
                    }else {
                        objetosHegonos[l][c].setDirecao('d');
                    }
                } else if (objetosHegonos[l][c].getDirecao() == 'b') {
                    if (!validaColisaoHexagono(posX, posY-20)) {
                        objetosHegonos[l][c].setPosicaoY(objetosHegonos[l][c].getPosicaoY() - 20);
                    }else {
                        objetosHegonos[l][c].setDirecao('c');
                    }
                } else if (objetosHegonos[l][c].getDirecao() == 'c') {
                    if (!validaColisaoHexagono(posX, posY+20)) {
                        objetosHegonos[l][c].setPosicaoY(objetosHegonos[l][c].getPosicaoY() + 20);
                    }else {
                        objetosHegonos[l][c].setDirecao('b');
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    //glutTimerFunc(350,movimentoHexagono,0);
}

bool WindowExercicios::validaColisaoHexagono(float posicaoX, float posicaoY) {
    bool colisaoX = posicaoX >= 480 || posicaoX <= 60;
    bool colisaoY = posicaoY >= 560 || posicaoY <= 80;
    if (colisaoX || colisaoY) {
        return true;
    }
    return false;
}

