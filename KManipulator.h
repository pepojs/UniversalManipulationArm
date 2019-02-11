#ifndef KMANIPULATOR_H
#define KMANIPULATOR_H

#include <iostream>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "KGrafika3D.h"
#include "KLancuchKinematyczny.h"

using namespace std;

struct IdentyfikatorOgniwa
{
    uint16_t IDOgniwa;
    GLuint IDObiektuOgniwa;
};

template <typename TypOgniwa, typename TypPrzegubu>
class Manipulator
{
    Grafika3D* Scena;
    LancuchKinematyczny<TypOgniwa,TypPrzegubu> LancuchManipulatora;
    vector <IdentyfikatorOgniwa> IDOgniw;

public:

    Manipulator(Grafika3D* Scena);
    void DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    void DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    void DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    uint16_t DodajPrzegub(TypPrzegubu NowyPrzegub);

};

#endif // KMANIPULATOR_H
