#include <iostream>
#include <GL/gl.h>
#include <Gl/glut.h>
#include "window.h"
#include "windowExercicios.h"

int main(int argc, char **argv) {
    //Window window;
    //window.iniciar(argc, argv);
    WindowExercicios windowExercicios;
    windowExercicios.iniciar(argc,argv);
    return 0;
}