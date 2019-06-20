
#include "personagemPacman.h"

void PersonagemPacman::criarPersonagem(float posicaoX, float posicaoY, int status) {
    float theta;
    glClear(GL_COLOR_BUFFER_BIT);

    // Circulo
    glColor3f(255, 255, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(this->getPosicaoX() + this->_raio * cos(theta), this->getPosicaoY() + this->_raio * sin(theta));
    }
    glEnd();

    // Triangulo
    glPushMatrix();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);

    // Triangulo
    glPushMatrix();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    if(this->_status == 0) { // Objeto para o lado esquerdo com a boca aberta
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY() + this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY() - this->_ajuste2);
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY() - this->_ajuste2);
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY() + this->_ajuste2);
    } else if(this->_status == 1) { // Objeto para o lado esquerdo com a boca fechada
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY()+this->_ajuste3);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY()-this->_ajuste3);
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY()-this->_ajuste3);
        glVertex2f(this->getPosicaoX() - this->_ajuste1, this->getPosicaoY()+this->_ajuste3);
    } else if (this->_status == 2) { // Objeto para o lado direito com a boca aberta
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
    } else if (this->_status == 3) { // Objeto para o lado direito com a boca fechada
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste3);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste3);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste3);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
    } else if (this->_status == 4) { // Objeto para cima com a boca aberta
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()-this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()+this->_ajuste2);
    } else if (this->_status == 5) { // Objeto para cima com a boca fechada
        glVertex2f(this->getPosicaoX()+this->_ajuste3, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()+this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()+this->_ajuste2);
    } else if (this->_status == 6) { // Objeto para baixo com a boca aberta
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()-this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()+this->_ajuste2, this->getPosicaoY()-this->_ajuste2);
    } else if (this->_status == 7) { // Objeto para baixo com a boca fechada
        glVertex2f(this->getPosicaoX()+this->_ajuste3, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX(), this->getPosicaoY());
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()-this->_ajuste2);
        glVertex2f(this->getPosicaoX()-this->_ajuste3, this->getPosicaoY()-this->_ajuste2);
    }
    glEnd();
    glPopMatrix();
}