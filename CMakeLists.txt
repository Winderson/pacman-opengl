cmake_minimum_required(VERSION 3.13)
project(PacmanOpengl)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set(CMAKE_CXX_STANDARD 14)
add_executable(PacmanOpengl
        main/main.cpp
        controller/controller.cpp controller/controller.h
        model/model.cpp model/model.h
        view/view.cpp view/view.h model/mapa.cpp model/mapa.h main/window.cpp main/window.h)
target_link_libraries(PacmanOpengl libopengl32.a libglu32.a libfreeglut.a)