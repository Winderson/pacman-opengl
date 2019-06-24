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

    int getRed() const {
        return red;
    }

    void setRed(int red) {
        Objeto::red = red;
    }

    int getGreen() const {
        return green;
    }

    void setGreen(int green) {
        Objeto::green = green;
    }

    int getBlue() const {
        return blue;
    }

    void setBlue(int blue) {
        Objeto::blue = blue;
    }


private:
    float _posicaoX;
    float _posicaoY;
    float _comprimento;
    float _altura;
    char _rotulo;
    char _direcao;
    int red;
    int green;
    int blue;
};

#endif //_OBJETO_H
