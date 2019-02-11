#ifndef SCZESCIMANIPULATORA_H
#define SCZESCIMANIPULATORA_H

#define GLEW_STATIC
#include <glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Typ zmiennej pozwalający okreslic rodzaj przegubu
enum RodzajPrzegubu
{
    PrzegubRotacyjny = 0,
    PrzegubTranslacyjny = 1
};

//Struktura zawieajaca potrzebne zmienne do opisu przegubu z punktu widzenia kinematyki
struct Przegub
{
    RodzajPrzegubu TypPrzegubu; //Rodzaj przegubu (rotacyjny albo translacyjny)
    GLfloat WartoscKonfiguracji; //Wartosc, na przyklad dla przegubu rotacyjnego, kata o jaki jest obrocone ogniwo w przegubie od pozycji poczatkowej

    glm::mat4 KinematykaPrzegubu; //Macierz przeksztalcenia ukladu bazowego do ukladu zwiazanego z przegubem (macierz A^{numer przegubu}_{0})

    Przegub(RodzajPrzegubu NowyTypPrzegubu, GLfloat NowaWartoscKonfiguracji, glm::mat4 NowaKinematykaPrzegubu);
    Przegub();
};

//Struktura ogniwa z danymi potrzebnymi do narysowania ogniwa na scenie oraz odpowiednimi macierzami pozwalajacymi
//obliczyc macierz przejscia miedzy ukladem poczatkowego przegubu, a koncowego przegubu
struct Ogniwo
{
    GLvoid* TablicaPunktow; //Tablica zawierajaca punkty ogniwa do rysowania
    size_t RozmiarTablicy; //Rozmiar tablicy potrzebny do narysowania ogniwa
    GLuint IloscWspolrzednych; //Ilosc wspolrzednych przypadajacych na jeden punkt
    GLuint IloscPunktow; //Ilosc punktow, z ktorych sklada sie ogniwo

    //Macierze przeksztalcen zgodne z noacja Denavita-Hartenberga
    //A = RotZ * TransZ * TransX * RotX
    glm::mat4 MacierzRotZ; //Rotacja wokol osi Z
    glm::mat4 MacierzTranZ; //Translacja wzdluz osi Z
    glm::mat4 MacierzTranX; //Translacja wzdluz osi X
    glm::mat4 MacierzRotX; //Rotacja wzdluz osi X

    glm::mat4 MacierzPoczatkowaRotZ; //Macierz przechowuje poczatkowa rotacje ogniwa wokol osi Z
    glm::mat4 MacierzPoczatkowaTranZ; //Macierz przechowuje poczatkowa translacje ogniwa wokol osi Z

    Ogniwo(GLvoid* NowaTablicaPunktow, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX);
    Ogniwo();
    void ZmienMacierzRotZ(glm::mat4 NowaMacierzRotZ){MacierzRotZ = NowaMacierzRotZ;}
};
#endif // SCZESCIMANIPULATORA_H