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
    void NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu);
    void NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu,
                     GLvoid* TablicaKolorow, size_t RozmiarTablicyKolorow, uint8_t IloscWspolrzednychKoloru);
    void UstawRzutowanieOrtogonalne(GLfloat Lewa, GLfloat Prawa, GLfloat Dol, GLfloat Gora, GLfloat Przod, GLfloat Tyl);
    void UstawRzutowaniePerspektywiczne(GLfloat Kat, GLfloat ProporcjeEkranu, GLfloat Przod, GLfloat Tyl);

    void Rysuj(SDL_Window* GlowneOkno);

};


#endif
