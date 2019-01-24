#ifndef KLASA_LANCUCH_H
#define KLASA_LANCUCH_H

#include <string>
#include "Klasa_graf.hpp"
#include "FPomocnicze.h"

#define GLEW_STATIC
#include <glew.h>

using namespace std;

class Lancuch
{
    Graf<Joint, Czlon> LanKine;

public:

    void DodajCzlon(Czlon c);


    void DodajCzlon(string Nazwa, int IlePunktow,
                    GLvoid* Punkty, GLvoid* PrzePunkty, GLfloat A[16], GLfloat Skala[16]);

    void DodajJoint(Joint j, string czlon1, string czlon2);
    Czlon ZwrocZawCzlonu(string czlon);
    Joint ZwrocZawJoint(string joint);
    void UstawMacierzF(string joint, GLfloat* NF);
    void UstawMacierzB(string joint, GLfloat* NB);
    void ObliczMacierzR(string joint, GLfloat* NowyParametr, int IleParametrow);
    void WyswietlLancuch(){LanKine.WyswietlGraf();}
    void ObliczMacierzA(string czlonPoczatkowy, string czlonKoncowy);





};



#endif
