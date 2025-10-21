cmake_minimum_required(VERSION 4.0)
project(Practica3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Practica3 main.cpp
        VDinamico.h
        PaMedicamento.cpp
        PaMedicamento.h
        Laboratorio.cpp
        Laboratorio.h
        Lista.h
        MediExpress.cpp
        MediExpress.h
        AVL.h
        Farmacia.cpp
        Farmacia.h)
