#ifndef KGRAFIKA3D_H
#define KGRAFIKA3D_H

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <SDL.h>
#include <SOIL.h>
#include <cstdio>

#define GLEW_STATIC
#include <glew.h>

#include "Shader.h"
#include "SObiektNaScenie.h"

using namespace std;

class Grafika3D
{
    Shader shader;
    vector<GLuint> vbo;
    vector<GLuint> vao;
    vector<ObiektNaScenie> ObiektyNaScenie;

    glm::vec3 PozycjaKamery; //Pozycja kamery na scenie (wspolrzedne globalne)
    glm::vec3 CelKamery; //Punkt, na ktory "patrzy" kamera
    glm::vec3 OsZKamery; //Wektor wskazujacy kierunek osi wychodzacej z gornej czesci kamery, prostopadly do gornej powierzchni

    public:
    ~Grafika3D();
    Shader* ZwrocAdresShadera(){return &shader;}

    //***Metody Tworzenie, kopiowanie, dodawanie i usuwanie Obiektow***
    GLuint TworzObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu);
    GLuint TworzObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu,
                       GLvoid* TablicaKolorow, size_t RozmiarTablicyKolorow, uint8_t IloscWspolrzednychKoloru);
    GLuint TworzObiekt(GLvoid* WspolnaTablica, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu, uint8_t IloscWspolrzednychKoloru,
                       uint8_t IloscWspolrzednychTekstury);
    GLuint DodajObiektDoSceny(GLuint vaoObiektu, GLuint IloscPunktowWObiekcie);
    void UsunObiektZeSceny(GLuint IDObiektu);
    GLuint KopiujObiekt(GLuint IDObiektu);

    //***Metoda laczaca tworzenie i dodawanie obiektu na scene
    GLuint DodajObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu, GLuint IloscPunktowWObiekcie);
    GLuint DodajObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu, GLvoid* TablicaKolorow,
                       size_t RozmiarTablicyKolorow, uint8_t IloscWspolrzednychKoloru, GLuint IloscPunktowWObiekcie);
    GLuint DodajObiekt(GLvoid* WspolnaTablica, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu, uint8_t IloscWspolrzednychKoloru,
                       uint8_t IloscWspolrzednychTekstury, GLuint IloscPunktowWObiekcie);

    //***Metody Transformacja Obiektu
    void PrzesunObiekt(GLuint IDObiektu, glm::vec3 Przesuniecie);
    void ObrocObiekt(GLuint IDObiektu, GLfloat KatObrotu, glm::vec3 OsObrotu);
    void PrzeskalujObiekt(GLuint IDObiektu, glm::vec3 WektorSkali);

    //***Metody Rzutowanie***
    void UstawRzutowanieOrtogonalne(GLfloat Lewa, GLfloat Prawa, GLfloat Dol, GLfloat Gora, GLfloat Przod, GLfloat Tyl);
    void UstawRzutowaniePerspektywiczne(GLfloat Kat, GLfloat ProporcjeEkranu, GLfloat Przod, GLfloat Tyl);

    //***Metody Kamera***
    void UstawKamere(glm::vec3 Pozycja, glm::vec3 Cel, glm::vec3 OsZ);
    glm::vec3 ZwrocPozycjeKamery(){return PozycjaKamery;}
    glm::vec3 ZwrocCelKamery(){return CelKamery;}
    glm::vec3 ZwrocOsZKamery(){return OsZKamery;}

    //***Metody Tekstury**
    GLuint GenerujTeksture2D(const char* NazwaObrazka, GLint ZawijanieTekstury, GLint FiltracjaTekstury);
    void DodajTekstureDoObiektu(GLuint IDTekstury, GLuint IDObiektu);
    void UsunTekstureZObiektu(GLuint IDTekstury, GLuint IDObiektu);

    void Rysuj(SDL_Window* GlowneOkno);

};


#endif
