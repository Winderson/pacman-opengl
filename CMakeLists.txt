cmake_minimum_required(VERSION 3.13)
project(PacmanOpengl)

set(CMAKE_CXX_STANDARD 14)

add_executable(PacmanOpengl main/main.cpp controller/controller.cpp controller/controller.h model/model.cpp model/model.h view/view.cpp view/view.h)