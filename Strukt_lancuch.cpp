#include "Strukt_lancuch.h"

//Konstruktor Czlon
Czlon::Czlon()
{
    Nazwa = "";
    IleWspol = 0;
    IlePunktow = 0;

    Punkty = NULL;
    PrzePunkty = NULL;
    M4x4Jednof(A);
    M4x4Jednof(Skala);
}

bool Czlon::operator == (const Czlon& c)
{
    if(c.Nazwa == Nazwa)
        return 1;
    else
        return 0;
}

bool Czlon::operator != (const Czlon& c)
{
    if(c.Nazwa != Nazwa)
        return 1;
    else
        return 0;
}

ostream & operator<< (ostream &wyjscie, const Czlon &c)
{
    return wyjscie<<c.Nazwa;
}

Joint::Joint()
{
    Nazwa = "";

    art = KA_ODWROTNY;

    //tworzy macierze jednostkowe
    M4x4Jednof(F);
    M4x4Jednof(B);
    M4x4Jednof(R);
}

ostream & operator<< (ostream &wyjscie, const Joint &j)
{
    return wyjscie<<j.Nazwa;
}

