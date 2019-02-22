#ifndef _SOGRANICZENIAPRZEGUBU_H
#define _SOGRANICZENIAPRZEGUBU_H

#include <iostream>

#define GLEW_STATIC
#include <glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

using namespace std;

enum TypOgraniczenia
{
    TO_OS_Z = 0,
    TO_OS_Y = 1,
    TO_OS_X = 2
};

enum DzialanieOgraniczenia
{
    DO_Mniejszy = 0,
    DO_MniejszyRowny = 1,
    DO_Wiekszy = 2,
    DO_WiekszyRowny = 3,
    DO_Rowny = 4
};

struct IdentyfikatorOgniwa
{
    uint16_t IDOgniwa;
    GLuint IDObiektuOgniwa;
};

struct OgraniczeniaPrzegubow
{
    GLfloat RozdzielczoscSilnika;
    GLfloat MinimalnyKat;
    GLfloat MaksymalnyKat;
    uint16_t NumerPrzegubu;

    OgraniczeniaPrzegubow(GLfloat NowaRozdzielczosc, GLfloat NowyMinimalnyKat, GLfloat NowyMaksymalnyKat, uint16_t NowyNumerPrzegubu);
    OgraniczeniaPrzegubow() {;}
};

struct OgraniczeniePrzestrzeniZadaniowej
{
    TypOgraniczenia Ograniczenie;
    DzialanieOgraniczenia Dzialanie;
    GLfloat WartoscOgraniczenia;

    bool operator == (const OgraniczeniePrzestrzeniZadaniowej& Ograniczenie);

};

#endif // _SOGRANICZENIAPRZEGUBU_H
