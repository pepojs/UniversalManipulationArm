#ifndef STRUKT_LANCUCH_H
#define STRUKT_LANCUCH_H

#include <string>
#include "FPomocnicze.h"

#define GLEW_STATIC
#include <glew.h>

using namespace std;

//Kody artykulacji
enum KodArt
{
    //Przegub odwrotny do drugiej polowy (gdy liczym nie od lewej, a od prawej strony)
    KA_ODWROTNY = -1,
    KA_NIC = 0,

    //Kody dla obrotu wokol osi x, y, z, i v oznaczajacy wektor
    KA_OBROT_OS_X = 1,
    KA_OBROT_OS_Y = 2,
    KA_OBROT_OS_Z = 3,
    KA_OBROT_OS_V = 4,

    //Kody przesuniecia wzdluz osi x, y, z i wszystkich
    KA_PRZE_OS_X = 5,
    KA_PRZE_OS_Y = 6,
    KA_PRZE_OS_Z = 7,
    KA_PRZE_OS_XYZ = 8,

    //Kody skalowania wzgledem osi x, y, z i wszystkich
    KA_SCAL_OS_X = 9,
    KA_SCAL_OS_Y = 10,
    KA_SCAL_OS_Z = 11,
    KA_SCAL_OS_XYZ = 12,



};

//Struktura opisujaca czlon (polaczenie miedzy 2 przegubami)
struct Czlon
{
    string Nazwa; //Nazwa czlonu
    int IleWspol; //Liczba wspolrzednych potrzebnych do opisu czlonu
    int IlePunktow; //Liczba punktow opisujacych czlon

    GLvoid* Punkty; //Tablica punktow opisujaca czlon (przed przeksztalceniem)
    GLvoid* PrzePunkty; //Tablica zawierajaca punkty przeksztalcone w wyniku artykulacji

    GLfloat A[16]; //Macierz przeksztalcen czlonu (opisuje czy czlon jest przesuniety, obrocony itp)
    GLfloat Skala[16]; //Tablica sluzaca do przeskalowania obiektu

    Czlon(); // Konstruktor

    bool operator == (const Czlon& c); //Przeciazenie operatora porownaia
    bool operator != (const Czlon& c); //Przeciazenie operatora roznicy

    friend ostream & operator<< (ostream &wyjscie, const Czlon &c); //Zaprzyjaznione przeciazenie operatora zapisu do strumienia

};

//Struktura opisujaca joint (przegub laczacy dwa lub wiecej czlonow)
struct Joint
{
    string Nazwa; //Nazwa przegubu

    GLfloat F[16]; //Tablica okreslajaca wektor przesuniecia przegubu wzgledem punktu okreslajacego poczatek lancucha
    GLfloat B[16]; //Tablica okreslajaca wektor odwrotny do wektora F (przesuniecie od przegubu do punktu poczatkowego)
    GLfloat R[16]; //Tablica okreslajaca przeksztalcenie przegubu (np. obrot wokol osi)

    KodArt art; // Kod artykulacji (przeksztalcenia)

    Joint(); //Konstruktor

    friend ostream & operator<< (ostream &wyjscie, const Joint &j); //Zaprzyjaznione przeciazenie operatora zapisu do strumienia
};


#endif
