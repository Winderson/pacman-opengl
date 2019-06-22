#ifndef _OBJETO_H
#define _OBJETO_H

class Objeto {
public:

    Objeto(){}

    float getPosicaoX() const {
        return _posicaoX;
    }

    void setPosicaoX(float posicaoX) {
        _posicaoX = posicaoX;
    }

    float getPosicaoY() const {
        return _posicaoY;
    }

    void setPosicaoY(float posicaoY) {
        _posicaoY = posicaoY;
    }

    float getComprimento() const {
        return _comprimento;
    }

    void setComprimento(float comprimento) {
        _comprimento = comprimento;
    }

    float getAltura() const {
        return _altura;
    }

    void setAltura(float altura) {
        _altura = altura;
    }

    char getRotulo() const {
        return _rotulo;
    }

    void setRotulo(char rotulo) {
        _rotulo = rotulo;
    }

    char getDirecao() const {
        return _direcao;
    }

    void setDirecao(char direcao) {
        _direcao = direcao;
    }

private:
    float _posicaoX;
    float _posicaoY;
    float _comprimento;
    float _altura;
    char _rotulo;
    char _direcao;
};

#endif //_OBJETO_H
