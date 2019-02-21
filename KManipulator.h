#ifndef _KMANIPULATOR_H
#define _KMANIPULATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "KGrafika3D.h"
#include "KLancuchKinematyczny.h"
#include "KKomunikacja.h"
#include "SOgraniczeniaPrzegubu.h"


template <typename TypOgniwa, typename TypPrzegubu>
class KManipulator
{
    Grafika3D* Scena;
    KLancuchKinematyczny<TypOgniwa,TypPrzegubu> LancuchManipulatora;
    KKomunikacjaMan01 Komunikacja;
    uint8_t PrzesylajKonfiguracje;

    vector <IdentyfikatorOgniwa> IDOgniw;
    map <uint16_t, OgraniczeniaPrzegubow> Ograniczenia;
    map <uint16_t, vector <OgraniczeniePrzestrzeniZadaniowej> > OgraniczeniaPrzestrzenZad;

public:

    KManipulator(Grafika3D* Scena);
    void DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    void DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa);
    void DodajOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow, GLfloat RotZ, GLfloat TranZ, GLfloat TranX,
                     GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa);

    void DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    void DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa);
    void DodajPoczatkoweOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow, GLfloat RotZ, GLfloat TranZ,
                               GLfloat TranX, GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDPoczatkowegoPrzegubu, glm::vec4 KolorOgniwa);

    void DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy);
    void DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, glm::vec4 KolorOgniwa);
    void DodajKoncoweOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow, GLfloat RotZ, GLfloat TranZ,
                            GLfloat TranX, GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa);

    uint16_t DodajPrzegub(TypPrzegubu NowyPrzegub);

    void DodajOgraniczeniePrzegubu(uint16_t IDPrzegubu, OgraniczeniaPrzegubow Ograniczenie);
    void DodajOgraniczeniePrzegubu(uint16_t IDPrzegubu, GLfloat Rozdzielczosc, GLfloat MinmalnyKat, GLfloat MaksymalnyKat, uint16_t NumerPrzegubu);
    void DodajOgranizczeniePrzesZadPrzegubu(uint16_t IDPrzegubu, OgraniczeniePrzestrzeniZadaniowej Ograniczenie);

    void ZmienKonfiguracjePrzegubu(uint16_t IDPrzegubu, GLfloat NowaKonfiguracja);

    void WyswietlKinematykeKoncowychOgniw();

    //***Komunikacja z rzeczywistym manipulatorem
    void WybierzKomunikacje(RodzajKomunikacji NowyRodzaj);
    void PodlaczUrzadzenie(std::string& Port, int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc);
    void OdlaczUrzadzenie();
    void WysliKonfiguracjePrzegubu(uint16_t NumerPrzegubu, uint16_t Kat);
    void WlaczPrzesylanieKonfiguracji(){PrzesylajKonfiguracje = 1;}
    void WylaczPrzesylanieKonfiguracji(){PrzesylajKonfiguracje = 0;}

};

#endif // KMANIPULATOR_H
