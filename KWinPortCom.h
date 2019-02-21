#ifndef _KWINPORTCOM_H
#define _KWINPORTCOM_H

#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

class KWinPortCOM
{
    private :

    DCB Dcb;
    HANDLE hCOM;
    COMSTAT Status;
    bool f_Sukces;
    bool f_KonOdczyt;
    OVERLAPPED Odczyt, Zapis;
    DWORD Ile_bitow;
    bool Res;
    public :

    std::string Polaczony;

    ~KWinPortCOM();
    int Start (std::string& Port,int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc);
    void Wysli (char* Buf, DWORD Ile);
    void Odbierz (char* Buf, void (*wFunk)());
    void OdbierajWPetli(char* Buf, void (*wFunk)());
    void KonOdbior ();

};


#endif // KWINPORTCOM_H
