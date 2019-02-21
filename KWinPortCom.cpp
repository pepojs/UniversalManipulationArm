#include "KWinPortCom.h"

KWinPortCOM::~KWinPortCOM()
{
    CancelIo(hCOM);
    CloseHandle(Odczyt.hEvent);
    CloseHandle(Zapis.hEvent);
    CloseHandle(hCOM);
}

//Metadoa pozwala rozpoczac transmisje przez port szeregowy COM
//Argumentami jest nazwa portu (np. COM23) oraz ustawienia ramki i predkosci przesylu danych
int KWinPortCOM::Start(std::string& Port, int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc)
{
    if(Predkosc <= 0) Predkosc = CBR_110;
    if(Predkosc >= 256000) Predkosc = CBR_256000;

    if(Parzystosc <= 0) Parzystosc = NOPARITY;
    if(Parzystosc >= 4) Parzystosc = SPACEPARITY;

    if(Stopbit <= 0) Stopbit = ONESTOPBIT;
    if(Stopbit >= 2) Stopbit = TWOSTOPBITS;

    if(Rozmiar <= 0) Rozmiar = 5;
    if(Rozmiar >= 8) Rozmiar = 8;


     BOOL fSukces;

     if( !Polaczony.empty() )
     {
        TerminateThread( hCOM, 0 );
        CloseHandle( hCOM );
    }
    Polaczony = "";
    hCOM = CreateFile(Port.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_FLAG_OVERLAPPED, NULL);

    Dcb.DCBlength = sizeof(Dcb);

    Dcb.BaudRate = Predkosc;
    Dcb.fParity = TRUE;
    Dcb.Parity = Parzystosc;
    Dcb.StopBits = Stopbit;
    Dcb.ByteSize = Rozmiar;

    Dcb.fDtrControl = DTR_CONTROL_DISABLE;
    Dcb.fRtsControl = RTS_CONTROL_DISABLE;

    Dcb.fOutxCtsFlow = FALSE;
    Dcb.fOutxDsrFlow = FALSE;
    Dcb.fDsrSensitivity = FALSE;
    Dcb.fAbortOnError = FALSE;
    Dcb.fOutX = FALSE;
    Dcb.fInX = FALSE;
    Dcb.fErrorChar = FALSE;
    Dcb.fNull = FALSE;

    if(SetCommState(hCOM, &Dcb))
    {
       std::cout << "Udalo sie \n";
       this->Polaczony = Port;
    }
    else
    {
        std::cout << "NIE udalo sie \n";
        this->Polaczony = "";
        CancelIo(hCOM);
        CloseHandle(hCOM);
        return 1;
    }

    fSukces = SetCommMask(hCOM, EV_CTS | EV_DSR | EV_RXCHAR | EV_TXEMPTY);

    if (!fSukces)
    {
        std::cout<<"SetCommMask error  " << GetLastError() << std::endl;
        this->Polaczony = "";
        return 1;
    }
    else
    this->Polaczony = Port;


    memset(&Odczyt, 0, sizeof(Odczyt));
    Odczyt.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    Odczyt.Offset = 0;

    memset(&Zapis, 0, sizeof(Zapis));
    Zapis.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    Zapis.Offset = 0;
}

//Metoda sluzy do wyslania zawartosci buforu
//Pierwszy argument to wskaznik na bufor, drugi ile danych chcemy wyslac
void KWinPortCOM::Wysli(char* Buf, DWORD Ile)
{
    if(!this->Polaczony.empty())
    {
        Ile_bitow = 0;
        f_KonOdczyt = 0;

        Res = WriteFile(hCOM, Buf, Ile, NULL, &Zapis );
        if(Res == 0 &&  GetLastError() == 997)
        {
            while(!GetOverlappedResult(hCOM, &Zapis, &Ile_bitow, false))
            {
                if(f_KonOdczyt == 1)
                {
                    std::cout<< "  break " << std::endl;
                    break;

                }else if(GetLastError() == 996)
                {
                    std::cout << "Zapis "<< GetLastError() << "  " << Ile_bitow << std::endl;

                }else if(GetLastError() == 38)
                {
                    std::cout<< " EOF" << std::endl;
                    break;

                }else
                {
                    std::cout<< "Error  " << GetLastError() << std::endl;
                    break;
                }
            }

        }else if(Res == 0 && GetLastError() != ERROR_IO_PENDING)
          std::cout<< " Blad odczytu" << std::endl;
    }
}

//Metoda pozwala odebrac pojedynczy komunikat
//Argumentami jest bufor, do ktorego tradia dane oraz wskaznik na funkcje, ktora zostanie wykonana podczas oczekiwania na dane
void KWinPortCOM::Odbierz(char* Buf, void (*wFunk)())
{
    if(!this->Polaczony.empty())
    {
        bool Wynik = 0;
        Ile_bitow = 0;
        int i = 0;

        Res = ReadFile(hCOM, Buf, 1, &Ile_bitow, &Odczyt );
       // std::cout << Res << " \n" << ile_bitow  << std::endl;
        if(Res == 0 &&  GetLastError() == ERROR_IO_PENDING)
        {
            do
            {
                Wynik = GetOverlappedResult(hCOM, &Odczyt, &Ile_bitow, false);

                if(Wynik)
                {
                    //std::cout << buf << std::endl;
                    ResetEvent(Odczyt.hEvent);
                    break;
                }

                if(f_KonOdczyt == 1)
                {
                    std::cout<< "  break " << std::endl;
                    break;
                }
                else if(GetLastError() == 996)
                {
                   // std::cout << "Odczytuje "<< GetLastError() << "  " << ile_bitow << std::endl;
                    (*wFunk)();

                }else if(GetLastError() == 38)
                {
                    std::cout<< " EOF" << std::endl;
                    break;

                }else
                {
                    std::cout<< "Error  " << GetLastError() << std::endl;
                    break;
                }

            }while(!Wynik);

        }else if(Res == 0 && GetLastError() != ERROR_IO_PENDING)
          std::cout<< " Blad odczytu" << std::endl;

        Odczyt.Offset += Ile_bitow;
        //std::cout<< " \n offset " << odczyt.Offset << std::endl;
    }
}

void KWinPortCOM::OdbierajWPetli(char* Buf, void (*wFunk)())
{
    if(!this->Polaczony.empty())
    {
        bool Wynik = 0;
        Ile_bitow = 0;
        f_KonOdczyt = 0;
        int i = 0;
        do
        {
            Res = ReadFile(hCOM, Buf, 1, &Ile_bitow, &Odczyt );
           // std::cout << Res << " \n" << ile_bitow  << std::endl;
            if(Res == 0 &&  GetLastError() == ERROR_IO_PENDING)
            {
                do
                {
                    Wynik = GetOverlappedResult(hCOM, &Odczyt, &Ile_bitow, false);

                    if(Wynik)
                    {
                        //std::cout << buf << std::endl;
                        ResetEvent(Odczyt.hEvent);
                        break;
                    }

                    if(f_KonOdczyt == 1)
                    {
                        std::cout<< "  break " << std::endl;
                        break;
                    }
                    else if(GetLastError() == 996)
                    {
                       // std::cout << "Odczytuje "<< GetLastError() << "  " << ile_bitow << std::endl;
                        (*wFunk)();

                    }else if(GetLastError() == 38)
                    {
                        std::cout<< " EOF" << std::endl;
                        break;

                    }else
                    {
                        std::cout<< "Error  " << GetLastError() << std::endl;
                        break;
                    }

                }while(!Wynik);

            }else if(Res == 0 && GetLastError() != ERROR_IO_PENDING)
              std::cout<< " Blad odczytu" << std::endl;

            Odczyt.Offset += Ile_bitow;
            //std::cout<< " \n offset " << odczyt.Offset << std::endl;


        }while(!f_KonOdczyt);

    }
}

void KWinPortCOM::KonOdbior()
{
    f_KonOdczyt = 1;
}
