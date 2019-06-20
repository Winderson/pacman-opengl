#ifndef _PERSONAGEM_H_
#define _PERSONAGEM_H_
#include "../main/window.h"

class Personagem{

public:
    Personagem(){};
    Personagem(float posicaoX, float posicaoY):_posicaoX(posicaoX),_posicaoY(posicaoY){};
    virtual void criarPersonagem(float posicaoX, float posicaoY);

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
};


#endif //_PERSONAGEM_H_
