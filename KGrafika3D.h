#ifndef KGRAFIKA3D_H
#define KGRAFIKA3D_H

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <SDL.h>

#define GLEW_STATIC
#include <glew.h>

#include "Shader.h"

using namespace std;

class Grafika3D
{
    Shader shader;
    vector<GLuint> vbo;
    vector<GLuint> vao;

    public:
    ~Grafika3D();
    Shader* ZwrocAdresShadera(){return &shader;}
    void NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy);
    void Rysuj(SDL_Window* GlowneOkno);

};


#endif
