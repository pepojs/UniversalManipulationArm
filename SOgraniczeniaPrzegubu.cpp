#include "SOgraniczeniaPrzegubu.h"

//******Metody dotyczace struktuty OgraniczeniaPrzegubu********
//
//
//*************************************************************
OgraniczeniaPrzegubow::OgraniczeniaPrzegubow(GLfloat NowaRozdzielczosc, GLfloat NowyMinimalnyKat, GLfloat NowyMaksymalnyKat, uint16_t NowyNumerPrzegubu)
: RozdzielczoscSilnika(NowaRozdzielczosc)
{
    MinimalnyKat = ceil(NowyMinimalnyKat/NowaRozdzielczosc)*NowaRozdzielczosc;
    MaksymalnyKat = floor(NowyMaksymalnyKat/NowaRozdzielczosc)*NowaRozdzielczosc;
    NumerPrzegubu = NowyNumerPrzegubu;
}

//******Metody dotyczace struktuty OgraniczeniePrzestrzeniZadaniowej********
//
//
//*************************************************************
bool OgraniczeniePrzestrzeniZadaniowej::operator == (const OgraniczeniePrzestrzeniZadaniowej& Ograniczenie)
{
    if((this->Dzialanie == Ograniczenie.Dzialanie) && (this->Ograniczenie == Ograniczenie.Ograniczenie) && (this->WartoscOgraniczenia == Ograniczenie.WartoscOgraniczenia) )
        return true;
    else
        return false;
}
