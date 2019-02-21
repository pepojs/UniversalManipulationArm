/* __________________________________________________________________
  |                                                                  |
  | Klasa KKomuikacja zawsze bedzie posiadac te same metody i bedzie |
  | interfejsem dla komunikacji niezaleznym od tego jaki zostanie    |
  |  rodzaj protokolu, standardu przesylu, rodzaju portu itp.        |
  |__________________________________________________________________|
*/

#ifndef _KKOMUNIKACJA_H
#define _KKOMUNIKACJA_H

#include <string>

#if _WIN32
#include "KWinPortCom.h"

#endif // _WIN32

//Pozniej dorzucic obsluge wielowatkowa oraz odpowiednie mechanizmy synchronizacji

using namespace std;

enum RodzajKomunikacji
{
    RodzajKom_NieWybrano = 0,
    RodzajKom_COM_UART = 1
};


class KKomunikacjaMan01
{
    RodzajKomunikacji TypKomunikacji;
    void* ObiektKomunikacji;

public:

    KKomunikacjaMan01();

    void WybierzKomunikacje(RodzajKomunikacji NowyTypKomunikacji);

    void PodlaczUrzadzenie(string& Port, int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc);
    void OdlaczUrzadzenie();

    void WysliDane(char* Buf, DWORD Ile);
    void WysliDane(uint16_t NumerPrzegubu, uint16_t Kat);

    void OdbierzDane(char* Buf, void (*wFunk)());


    //void PrzerwiOdbior();

};

#endif // KKOMUNIKACJA_H
