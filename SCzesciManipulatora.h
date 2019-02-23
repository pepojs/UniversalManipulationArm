#ifndef _SCZESCIMANIPULATORA_H
#define _SCZESCIMANIPULATORA_H

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

    GLfloat KonfiguracjaPoczatkowa; //Wartosc jaka nalezy dodac do konfiguracji przegubow, wynikajaca z pozycji poczatkowej manipulatora

    Ogniwo(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX, GLfloat NowaKonfiguracjaPoczatkowa);
    Ogniwo(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, GLfloat RotZ, GLfloat TranZ,
           GLfloat TranX, GLfloat RotX, GLfloat NowaKonfiguracjaPoczatkowa);
    Ogniwo();


};

struct Chwytak
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

    glm::mat4 KinematykaChwytaka; //Macierz przeksztalceni z ukladu bazowego do ukladu punktu wyznaczajacego punkt "pracy" chwytaka
                                  //(punkt miedzy palcami chwytaka, koncowka pistoletu malarskiego itp)

    GLfloat KonfiguracjaPoczatkowa; //Wartosc jaka nalezy dodac do konfiguracji przegubow, wynikajaca z pozycji poczatkowej manipulatora

    Chwytak(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX, GLfloat NowaKonfiguracjaPoczatkowa, glm::mat4 NowaKinematykaChwytaka);
    Chwytak(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, GLfloat RotZ, GLfloat TranZ,
           GLfloat TranX, GLfloat RotX, GLfloat NowaKonfiguracjaPoczatkowa, glm::mat4 NowaKinematykaChwytaka);
    Chwytak();
};

#endif // SCZESCIMANIPULATORA_H
