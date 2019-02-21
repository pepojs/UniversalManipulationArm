#include "KKomunikacja.h"

KKomunikacjaMan01::KKomunikacjaMan01() :TypKomunikacji(RodzajKom_NieWybrano), ObiektKomunikacji(NULL) {;}

void KKomunikacjaMan01::WybierzKomunikacje(RodzajKomunikacji NowyTypKomunikacji)
{
    TypKomunikacji = NowyTypKomunikacji;

    switch(TypKomunikacji)
    {
        case RodzajKom_COM_UART:
            if(ObiektKomunikacji != NULL)
                delete ObiektKomunikacji;

            ObiektKomunikacji = new KWinPortCOM;
        break;

        default:
        break;
    }
}

void KKomunikacjaMan01::PodlaczUrzadzenie(std::string& Port, int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc)
{
    if(TypKomunikacji == RodzajKom_COM_UART)
    {
        ((KWinPortCOM*)ObiektKomunikacji)->Start(Port, Parzystosc, Rozmiar, Stopbit, Predkosc);

    }else if(TypKomunikacji == RodzajKom_NieWybrano)
    {
        cout<<"Nie wybrano rodzaju komunikacji !!!"<<endl;

    }else
        cout<<"Niewlasciwe dane dla wybranej komunikacji"<<endl;

}

void KKomunikacjaMan01::OdlaczUrzadzenie()
{
    if(TypKomunikacji == RodzajKom_COM_UART)
    {
        ((KWinPortCOM*)ObiektKomunikacji)->~KWinPortCOM();

    }else if(TypKomunikacji == RodzajKom_NieWybrano)
    {
        cout<<"Nie wybrano rodzaju komunikacji !!!"<<endl;

    }
}

void KKomunikacjaMan01::WysliDane(char* Buf, DWORD Ile)
{
    if(TypKomunikacji == RodzajKom_COM_UART)
    {
        ((KWinPortCOM*)ObiektKomunikacji)->Wysli(Buf, Ile);

    }else if(TypKomunikacji == RodzajKom_NieWybrano)
    {
        cout<<"Nie wybrano rodzaju komunikacji !!!"<<endl;

    }
}

void KKomunikacjaMan01::WysliDane(uint16_t NumerPrzegubu, uint16_t Kat)
{
    char Buf[2];

    if(NumerPrzegubu > 255)
    {
        cout<<"Zbyt duzy numer przegubu! Przerywam wysylanie."<<endl;
        return;
    }

    if(Kat > 255)
    {
        cout<<"Zbyt duzy kat! Przerywam wysylanie."<<endl;
        return;
    }

    Buf[0] = (uint8_t)NumerPrzegubu;
    Buf[1] = (uint8_t)Kat;

    cout<<"Buf: "<<(int)Buf[0]<<" ,"<<(uint8_t)Buf[1]<<endl;
    if(TypKomunikacji == RodzajKom_COM_UART)
    {
        ((KWinPortCOM*)ObiektKomunikacji)->Wysli(Buf, 2);

    }else if(TypKomunikacji == RodzajKom_NieWybrano)
    {
        cout<<"Nie wybrano rodzaju komunikacji !!!"<<endl;

    }
}

void KKomunikacjaMan01::OdbierzDane(char* Buf, void (*wFunk)())
{
    if(TypKomunikacji == RodzajKom_COM_UART)
    {
        ((KWinPortCOM*)ObiektKomunikacji)->Odbierz(Buf, wFunk);

    }else if(TypKomunikacji == RodzajKom_NieWybrano)
    {
        cout<<"Nie wybrano rodzaju komunikacji !!!"<<endl;

    }
}
