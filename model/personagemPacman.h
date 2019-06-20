#ifndef _PERSONAGEM_PACMAN_H_
#define _PERSONAGEM_PACMAN_H_
#include "personagemPacman.h"
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#include <GL/glu.h>
#include <math.h>

class PersonagemPacman{
public:
    PersonagemPacman(){
        this->_raio = 13;
        this->_status = 2;
        this->_ajuste1 = 30;
        this->_ajuste2 = 25;
        this->_ajuste3 = 5;
    }
    PersonagemPacman(float posicaoX, float posicaoY, int status){
        this->setPosicaoX(posicaoX);
        this->setPosicaoY(posicaoY);
        this->_raio = 13;
        this->_status = status;
        this->_ajuste1 = 30;
        this->_ajuste2 = 25;
        this->_ajuste3 = 5;
        this->criarPersonagem(this->getPosicaoX(), this->getPosicaoY(), this->_status);
    }
    void criarPersonagem(float posicaoX, float posicaoY, int status);

    // Métodos mutantes
    float getPosicaoX(){
        return this->_posicaoX;
    }

    void setPosicaoX(float posicaoX){
        this->_posicaoX = _posicaoY;
    }

    float getPosicaoY(){
        return this->_posicaoY;
    }

    void setPosicaoY(float posicaoY){
        this->_posicaoY = posicaoY;
    }

private:
    float _posicaoX;
    float _posicaoY;
    float _raio;
    float _status;
    float _ajuste1;
    float _ajuste2;
    float _ajuste3;
};


#endif //_PERSONAGEM_PACMAN_H_
