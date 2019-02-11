#include "KLancuchKinematyczny.h"


//Metoda pozwalajaca dodac do lancucha ogniwo zakonczone z obydwoch koncow przegubem
//Argumentami sa wypelniona struktura danymi o ogniwie, identyfikator przegubu na poczatku ogniwa oraz
//identyfikator przegubu konczacego ogniwo, zwraca identyfikator na nowe ogniwo
template <typename TypOgniwa, typename TypPrzegubu>
uint16_t LancuchKinematyczny<TypOgniwa, TypPrzegubu>::DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu)
{
    Ogniwa<TypOgniwa, TypPrzegubu> NoweOgniwo; //Tworzymy ogniwo pomocnicze

    //Wypelnia pomocniczy obiekt
    NoweOgniwo.ZmienWskNaPoczatkowyPrzegub(NULL);
    NoweOgniwo.ZmienWskNaKoncwyPrzegub(NULL);
    NoweOgniwo.ZmienDaneOgniwa(DaneOgniwa);

    //Jezeli nie ma jeszcze ogniw w lancuchu to nowe ogniwo ma identyfikator 0, inaczej nadaje ID + 1 niz ostatnie ogniwo
    if(ListaOgniw.empty())
        NoweOgniwo.ZmienIDOgniwa(0);
    else
        NoweOgniwo.ZmienIDOgniwa(ListaOgniw[ListaOgniw.size()-1].ZwrocIDOgniwa() + 1);

    //Przeszukuje liste przegubuw i dodaje wskazniki na odpowiednie przeguby
    for(size_t i = 0; i < ListaPrzegubow.size(); i++)
    {
        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDPoczatkowegoPrzegubu)
        {
            NoweOgniwo.ZmienWskNaPoczatkowyPrzegub(&ListaPrzegubow[i]);
        }

        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDKoncowegoPrzegubu)
        {
            NoweOgniwo.ZmienWskNaKoncwyPrzegub(&ListaPrzegubow[i]);
        }
    }

    //Jezeli nie znaleziono, ktoregos z przegubow wypisujemy odpowiedni komunikat
    if(NoweOgniwo.ZwrocWskPoczatkowegoPrzegubu() == NULL)
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDPoczatkowegoPrzegubu<<endl;
        return 0;
    }


    if(NoweOgniwo.ZwrocWskKoncowegoPrzegubu() == NULL)
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDKoncowegoPrzegubu<<endl;
        return 0;
    }

    //Dodajemy ogniwo do listy w lancuchu i dodajemy w przegubach ogniwo jako podlaczone do przegubu
    ListaOgniw.push_back(NoweOgniwo);
    NoweOgniwo.ZwrocWskKoncowegoPrzegubu()->DodajPodlaczoneOgniwo(ListaOgniw.back().ZwrocIDOgniwa());
    NoweOgniwo.ZwrocWskPoczatkowegoPrzegubu()->DodajPodlaczoneOgniwo(ListaOgniw.back().ZwrocIDOgniwa());

    //Zwracamy ID ogniwa
    return NoweOgniwo.ZwrocIDOgniwa();

}

//Metoda pozwalajaca dodac do lancucha ogniwo, ktore zaczyna lancuch, nie posiada przegubu na poczatku
//(moze to byc baza manipulatora). Argumentami sa wypelniona struktura danymi o ogniwie
//i identyfikator przegubu na koncu ogniwa, zwraca identyfikaor na nowe ogniwo.
template <typename TypOgniwa, typename TypPrzegubu>
uint16_t LancuchKinematyczny<TypOgniwa, TypPrzegubu>::DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu)
{
    Ogniwa<TypOgniwa, TypPrzegubu> NoweOgniwo; //Tworzymy ogniwo pomocnicze

    //Wypelnia pomocniczy obiekt
    NoweOgniwo.ZmienWskNaPoczatkowyPrzegub(NULL);
    NoweOgniwo.ZmienWskNaKoncwyPrzegub(NULL);
    NoweOgniwo.ZmienDaneOgniwa(DaneOgniwa);

    //Jezeli nie ma jeszcze ogniw w lancuchu to nowe ogniwo ma identyfikator 0, inaczej nadaje ID + 1 niz ostatnie ogniwo
    if(ListaOgniw.empty())
        NoweOgniwo.ZmienIDOgniwa(0);
    else
        NoweOgniwo.ZmienIDOgniwa(ListaOgniw[ListaOgniw.size()-1].ZwrocIDOgniwa() + 1);


    //Przeszukuje liste przegubuw i dodaje wskazniki na odpowiednie przeguby
    for(size_t i = 0; i < ListaPrzegubow.size(); i++)
    {

        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDKoncowegoPrzegubu)
        {
           NoweOgniwo.ZmienWskNaKoncwyPrzegub(&ListaPrzegubow[i]);
            break;
        }
    }

    //Jezeli nie znaleziono, ktoregos z przegubow wypisujemy odpowiedni komunikat
    if(NoweOgniwo.ZwrocWskKoncowegoPrzegubu() == NULL)
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDKoncowegoPrzegubu<<endl;
        return 0;
    }

    //Dodajemy ogniwo do listy w lancuchu i dodajemy w przegubie ogniwo jako podlaczone do przegubu
    ListaOgniw.push_back(NoweOgniwo);
    NoweOgniwo.ZwrocWskKoncowegoPrzegubu()->DodajPodlaczoneOgniwo(ListaOgniw.back().ZwrocIDOgniwa());

    //Zwracamy ID ogniwa
    return NoweOgniwo.ZwrocIDOgniwa();
}

//Metoda pozwalajaca dodac do lancucha ogniwo, ktore konczy lancuch, nie posiada przegubu na koncu
//(moze to byc chwytak manipulatora). Argumentami sa wypelniona struktura danymi o ogniwie
//i identyfikator przegubu na poczatku ogniwa, zwraca identyfikaor na nowe ogniwo.
template <typename TypOgniwa, typename TypPrzegubu>
uint16_t LancuchKinematyczny<TypOgniwa, TypPrzegubu>::DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu)
{
    Ogniwa<TypOgniwa, TypPrzegubu> NoweOgniwo; //Tworzymy ogniwo pomocnicze

    //Wypelnia pomocniczy obiekt
    NoweOgniwo.ZmienWskNaPoczatkowyPrzegub(NULL);
    NoweOgniwo.ZmienWskNaKoncwyPrzegub(NULL);
    NoweOgniwo.ZmienDaneOgniwa(DaneOgniwa);

    //Jezeli nie ma jeszcze ogniw w lancuchu to nowe ogniwo ma identyfikator 0, inaczej nadaje ID + 1 niz ostatnie ogniwo
    if(ListaOgniw.empty())
        NoweOgniwo.ZmienIDOgniwa(0);
    else
        NoweOgniwo.ZmienIDOgniwa(ListaOgniw[ListaOgniw.size()-1].ZwrocIDOgniwa() + 1);


    //Przeszukuje liste przegubuw i dodaje wskazniki na odpowiednie przeguby
    for(size_t i = 0; i < ListaPrzegubow.size(); i++)
    {

        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDPoczatkowegoPrzegubu)
        {
            NoweOgniwo.ZmienWskNaPoczatkowyPrzegub(&ListaPrzegubow[i]);
            break;
        }
    }

    //Jezeli nie znaleziono, ktoregos z przegubow wypisujemy odpowiedni komunikat
    if(NoweOgniwo.ZwrocWskPoczatkowegoPrzegubu() == NULL)
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDPoczatkowegoPrzegubu<<endl;
        return 0;
    }

    //Dodajemy ogniwo do listy w lancuchu i dodajemy w przegubie ogniwo jako podlaczone do przegubu
    ListaOgniw.push_back(NoweOgniwo);
    NoweOgniwo.ZwrocWskPoczatkowegoPrzegubu()->DodajPodlaczoneOgniwo(ListaOgniw.back().ZwrocIDOgniwa());

    //Zwracamy ID ogniwa
    return NoweOgniwo.ZwrocIDOgniwa();
}

//Metoda pozwalajaca dodac do lancucha przegub. Argumente jest wypelniona struktura danymi o przegubie,
//zwraca identyfikaor na nowe przegub.
template <typename TypOgniwa, typename TypPrzegubu>
uint16_t LancuchKinematyczny<TypOgniwa, TypPrzegubu>::DodajPrzegub(TypPrzegubu DanePrzegubu)
{
    Przeguby<TypOgniwa, TypPrzegubu> NowePrzegub; //Tworzymy przegub pomocnicze

    //Zapisuje dane w nowym obiekcie
    NowePrzegub.ZmienDanePrzegubu(DanePrzegubu);

    //Jezeli nie ma jeszcze przegubu w lancuchu to nowe przegub ma identyfikator 0, inaczej nadaje ID + 1 niz ostatnie przegub
    if(ListaPrzegubow.empty())
        NowePrzegub.ZmienIDPrzegubu(0);
    else
        NowePrzegub.ZmienIDPrzegubu(ListaPrzegubow[ListaPrzegubow.size()-1].ZwrocIDPrzegubu() + 1);

    //Dodajemy przegub do listy w lancuchu
    ListaPrzegubow.push_back(NowePrzegub);

    //Zwraca identyfikator przegubu
    return NowePrzegub.ZwrocIDPrzegubu();
}

//Metoda pozwala zmienic konfiguracje przegubu (na przyklad kat pod jaki jest obrocony przegub)
//Argumentami sa identyfikator przegubu oraz nowa wartosc konfiguracji
template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::ZmienKonfiguracjePrzegubu(uint16_t IDPrzegubu, GLfloat NowaKonfiguracja)
{
    size_t i;
    for(i = 0; i < ListaPrzegubow.size(); i++)
    {
        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDPrzegubu)
            break;
    }

    if(i >= ListaPrzegubow.size())
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDPrzegubu<<" Nie mozna zmienic jego konfiguracji"<<endl;
        return;
    }

    ListaPrzegubow[i].ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji = NowaKonfiguracja;
}

template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::ZmienKinematykePrzegubu(uint16_t IDPrzegubu, glm::mat4 NowaKinematykaPrzegubu)
{
    size_t i;
    for(i = 0; i < ListaPrzegubow.size(); i++)
    {
        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDPrzegubu)
            break;
    }

    if(i >= ListaPrzegubow.size())
    {
        cerr<<"Nie istnieje przegub o ID: "<<IDPrzegubu<<" Nie mozna zmienic kinematyki"<<endl;
        return;
    }

    ListaPrzegubow[i].ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu = NowaKinematykaPrzegubu;
}

template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::ZmienMacierzRotZOgniwa(uint16_t IDOgniwa, glm::mat4 NowaMacierzRotZ)
{
    size_t i;
    for(i = 0; i < ListaOgniw.size(); i++)
    {
        if(ListaOgniw[i].ZwrocIDOgniwa() == IDOgniwa)
            break;
    }

    if(i >= ListaOgniw.size())
    {
        cerr<<"Nie istnieje ogniwo o ID: "<<IDOgniwa<<" Nie mozna zmienic jego macierzy rotacji osi Z"<<endl;
        return;
    }

    ListaOgniw[i].ZwrocWskNaDaneOgniwa()->MacierzRotZ = NowaMacierzRotZ;
}

template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::ZmienMacierzTranZOgniwa(uint16_t IDOgniwa, glm::mat4 NowaMacierzTranZ)
{
    size_t i;
    for(i = 0; i < ListaOgniw.size(); i++)
    {
        if(ListaOgniw[i].ZwrocIDOgniwa() == IDOgniwa)
            break;
    }

    if(i >= ListaOgniw.size())
    {
        cerr<<"Nie istnieje ogniwo o ID: "<<IDOgniwa<<" Nie mozna zmienic jego macierzy translacji wzdluz osi Z"<<endl;
        return;
    }

    ListaOgniw[i].ZwrocWskNaDaneOgniwa()->MacierzTranZ = NowaMacierzTranZ;
}

//Metoda pozwala policzyc kolejne macierze kinematyki w przegubach oraz macierze rotacji lub translacji osi Z ogniw.
//Nalezy ja wywolac po stworzeniu lancucha kinematycznego, jak rownierz przy kazdej zmianie konfiguracji przegubow.
template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::PoliczKinematyke()
{
    size_t i;
    size_t k;
    uint16_t IloscGotowychPrzegubow = 0;

    //Petla pozwalajaca przejsc przez wszystkie przeguby znajdujace sie na liscie
    for(uint16_t NumerPrzegubu = 0;;NumerPrzegubu++)
    {
        //Szuka przegubu z identyfikatorem rownym numerowi przegubu
        for(i = 0; i < ListaPrzegubow.size(); i++)
        {
            if(ListaPrzegubow[i].ZwrocIDPrzegubu() == NumerPrzegubu)
                break;
        }

        //Sprawdza czy przegub zostal znaleziony w liscie oraz czy nie zostaly juz obsluzone wszystkie przeguby
        if(i >= ListaPrzegubow.size() && IloscGotowychPrzegubow >= ListaPrzegubow.size())
        {
                return;

        }else if(i >= ListaPrzegubow.size()) //Jezeli przegubu nie ma na liscie, ale nie wszystkie przeguby zostaly obsluzone
        {
                IloscGotowychPrzegubow += 1;
                continue;
        }

        IloscGotowychPrzegubow += 1;

        //Wyszukuje wszystkie podlaczone ogniwa do rozpatrywanego przegubu
        for(size_t j = 0; j < ListaPrzegubow[i].ZwrocIloscOgniw(); j++)
        {
            //Mam ID ogniwa, wyszukuje ogniwo w liscie, potem dla poczatkowego przegubu wyliczam RotZ lub TranZ,
            //a nastepnie dla koncowego kinematyke pod waruniek ze istnieja

            //Petla wyszukujaca z listy ogniw, ogniwa o ID rownym temu znajdujacemu sie na liscie ogniw podlaczonych do przegubu
            for(k = 0; k < ListaOgniw.size(); k++)
            {
                if(ListaOgniw[k].ZwrocIDOgniwa() == ListaPrzegubow[i].ZwrocIDPodlaczonegoOgniwa(j))
                    break;
            }

            //Jezeli ogniwo ma poczatkowy przegub
            if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu() != NULL)
            {
                //Jezeli przegub, dla ktorego szukamy podlaczone ogniwa jest poczatkowym przegubem znalezionego ogniwa
                //to modyfikuje w tym ogniwie macierz RotZ lub TranZ, warunek jest po to aby dwa razy nie modyfikowac tej samej macierzy
                //dla ogniwa podlaczonego z przodu i tylu przegubu
                if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocIDPrzegubu() == NumerPrzegubu)
                {
                    //Dla odpowiedniego rodzaju przegubu modyfikuje odpowiednia macierz
                    if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->TypPrzegubu == PrzegubRotacyjny)
                        ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ = glm::rotate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaRotZ, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji, glm::vec3(0.0f, 0.0f, 1.0f));
                    else
                        ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ = glm::translate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaTranZ, glm::vec3(0.0f, 0.0f, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji));
                }
            }
            else
                continue;

            //Jezeli ogniwo ma kocowy przegub
            if(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu() != NULL)
            {
                //Jezeli przegub, dla ktorego szukalismy podlaczonych ogniw, nie jest koncowym przegubem znalezionego ogniwa
                //to modyfikuje kinematyke przegubu koncowego, warunek rownierz dodany aby dwa razy nie moodyfikowac tej samej macierzy
                //Modyfikujemy tylko macierze ogniw znajdujacych sie za przegubem
                if(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocIDPrzegubu() != NumerPrzegubu)
                {
                    //Kinematyka przegubu koncowego = kinematyka przegubu poczatkowego * RotZ * TranZ * TranX * RotX (Macierze znajduja sie w ogniwie)
                    ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu =  ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu *
                    ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranX * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotX;
                }
            }
        }
    }

}

//Metoda pozwala policzyc kolejne macierze kinematyki w przegubach od przegubu o identyfikatorze podanym jako IDPoczatkowegoPrzegubu
//aż do przegubu o identyfikatorze IDKoncowegoPrzegubu włącznie z nim oraz macierze rotacji lub translacji osi Z ogniw z nimi polaczonych.
//Nalezy ja wywolac po stworzeniu lancucha kinematycznego, jak rownierz przy kazdej zmianie konfiguracji przegubow.
template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::PoliczKinematyke(uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu)
{
    size_t i;
    size_t k;
    uint16_t IloscGotowychPrzegubow = 0;

    //Petla pozwalajaca przejsc przez wszystkie przeguby znajdujace sie na liscie
    for(uint16_t NumerPrzegubu = IDPoczatkowegoPrzegubu; NumerPrzegubu <= IDKoncowegoPrzegubu; NumerPrzegubu++)
    {
        //Szuka przegubu z identyfikatorem rownym numerowi przegubu
        for(i = 0; i < ListaPrzegubow.size(); i++)
        {
            if(ListaPrzegubow[i].ZwrocIDPrzegubu() == NumerPrzegubu)
                break;
        }

        //Sprawdza czy przegub zostal znaleziony w liscie oraz czy nie zostaly juz obsluzone wszystkie przeguby
        if(i >= ListaPrzegubow.size() && IloscGotowychPrzegubow >= ListaPrzegubow.size())
        {
                return;

        }else if(i >= ListaPrzegubow.size()) //Jezeli przegubu nie ma na liscie, ale nie wszystkie przeguby zostaly obsluzone
        {
                IloscGotowychPrzegubow += 1;
                continue;
        }

        IloscGotowychPrzegubow += 1;

        //Wyszukuje wszystkie podlaczone ogniwa do rozpatrywanego przegubu
        for(size_t j = 0; j < ListaPrzegubow[i].ZwrocIloscOgniw(); j++)
        {
            //Mam ID ogniwa, wyszukuje ogniwo w liscie, potem dla poczatkowego przegubu wyliczam RotZ lub TranZ,
            //a nastepnie dla koncowego kinematyke pod waruniek ze istnieja

            //Petla wyszukujaca z listy ogniw, ogniwa o ID rownym temu znajdujacemu sie na liscie ogniw podlaczonych do przegubu
            for(k = 0; k < ListaOgniw.size(); k++)
            {
                if(ListaOgniw[k].ZwrocIDOgniwa() == ListaPrzegubow[i].ZwrocIDPodlaczonegoOgniwa(j))
                    break;
            }

            //Jezeli ogniwo ma poczatkowy przegub
            if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu() != NULL)
            {
                //Jezeli przegub, dla ktorego szukamy podlaczone ogniwa jest poczatkowym przegubem znalezionego ogniwa
                //to modyfikuje w tym ogniwie macierz RotZ lub TranZ, warunek jest po to aby dwa razy nie modyfikowac tej samej macierzy
                //dla ogniwa podlaczonego z przodu i tylu przegubu
                if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocIDPrzegubu() == NumerPrzegubu)
                {
                    //Dla odpowiedniego rodzaju przegubu modyfikuje odpowiednia macierz
                    if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->TypPrzegubu == PrzegubRotacyjny)
                        ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ = glm::rotate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaRotZ, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji, glm::vec3(0.0f, 0.0f, 1.0f));
                    else
                        ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ = glm::translate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaTranZ, glm::vec3(0.0f, 0.0f, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji));
                }
            }
            else
                continue;

            //Jezeli ogniwo ma kocowy przegub
            if(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu() != NULL)
            {
                //Jezeli przegub, dla ktorego szukalismy podlaczonych ogniw, nie jest koncowym przegubem znalezionego ogniwa
                //to modyfikuje kinematyke przegubu koncowego, warunek rownierz dodany aby dwa razy nie moodyfikowac tej samej macierzy
                //Modyfikujemy tylko macierze ogniw znajdujacych sie za przegubem
                if(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocIDPrzegubu() != NumerPrzegubu)
                {
                    //Kinematyka przegubu koncowego = kinematyka przegubu poczatkowego * RotZ * TranZ * TranX * RotX (Macierze znajduja sie w ogniwie)
                    ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu =  ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu *
                    ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranX * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotX;
                }
            }
        }
    }

}

//Metoda pozwala policzyc kolejne macierze kinematyki w przegubach od przegubu o identyfikatorze podanym jako IDPoczatkowegoPrzegubu
//aż do konca lancucha w gore oraz macierze rotacji lub translacji osi Z ogniw z nimi polaczonych.
//Nalezy ja wywolac po stworzeniu lancucha kinematycznego, jak rownierz przy kazdej zmianie konfiguracji przegubow.
template <typename TypOgniwa, typename TypPrzegubu>
void LancuchKinematyczny<TypOgniwa, TypPrzegubu>::PoliczKinematyke(uint16_t IDPoczatkowegoPrzegubu)
{
    size_t i;
    size_t k;

    for(i = 0; i < ListaPrzegubow.size(); i++)
    {
        if(ListaPrzegubow[i].ZwrocIDPrzegubu() == IDPoczatkowegoPrzegubu)
            break;
    }

    //Wyszukuje wszystkie podlaczone ogniwa do rozpatrywanego przegubu
    for(size_t j = 0; j < ListaPrzegubow[i].ZwrocIloscOgniw(); j++)
    {
        //Mam ID ogniwa, wyszukuje ogniwo w liscie, potem dla poczatkowego przegubu wyliczam RotZ lub TranZ,
        //a nastepnie dla koncowego kinematyke pod waruniek ze istnieja

        //Petla wyszukujaca z listy ogniw, ogniwa o ID rownym temu znajdujacemu sie na liscie ogniw podlaczonych do przegubu
        for(k = 0; k < ListaOgniw.size(); k++)
        {
            if(ListaOgniw[k].ZwrocIDOgniwa() == ListaPrzegubow[i].ZwrocIDPodlaczonegoOgniwa(j))
                break;
        }

        //Jezeli ogniwo ma poczatkowy przegub
        if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu() != NULL)
        {
            //Jezeli przegub, dla ktorego szukamy podlaczone ogniwa jest poczatkowym przegubem znalezionego ogniwa
            //to modyfikuje w tym ogniwie macierz RotZ lub TranZ, warunek jest po to aby dwa razy nie modyfikowac tej samej macierzy
            //dla ogniwa podlaczonego z przodu i tylu przegubu
            if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocIDPrzegubu() == IDPoczatkowegoPrzegubu)
            {
                //Dla odpowiedniego rodzaju przegubu modyfikuje odpowiednia macierz
                if(ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->TypPrzegubu == PrzegubRotacyjny)
                    ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ = glm::rotate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaRotZ, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji, glm::vec3(0.0f, 0.0f, 1.0f));
                else
                    ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ = glm::translate(ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzPoczatkowaTranZ, glm::vec3(0.0f, 0.0f, ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->WartoscKonfiguracji));

                //Jezeli ogniwo ma kocowy przegub
                if(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu() != NULL)
                {
                    //Kinematyka przegubu koncowego = kinematyka przegubu poczatkowego * RotZ * TranZ * TranX * RotX (Macierze znajduja sie w ogniwie)
                    ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu =  ListaOgniw[k].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->KinematykaPrzegubu *
                    ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranZ * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzTranX * ListaOgniw[k].ZwrocWskNaDaneOgniwa()->MacierzRotX;

                    PoliczKinematyke(ListaOgniw[k].ZwrocWskKoncowegoPrzegubu()->ZwrocIDPrzegubu());
                }

            }
        }
    }


}

//Metoda zwraca macierz transformujaca ogniwo tak aby znajdowalo sie w odpowiednim miejscu i orientacji na scenie
//Argumentem jest identyfikator ogniwa, dla ktorego chcemy otrzymac macierz
template <typename TypOgniwa, typename TypPrzegubu>
glm::mat4 LancuchKinematyczny<TypOgniwa, TypPrzegubu>::ZwrocTransformacjeOgniwa(uint16_t IDOgniwa)
{
    size_t i;
    for(i = 0; i < ListaOgniw.size(); i++)
    {
        if(ListaOgniw[i].ZwrocIDOgniwa() == IDOgniwa)
            break;
    }

    if(i >= ListaOgniw.size())
    {
        cerr<<"Nie ma ogniwa o ID: "<<IDOgniwa<<endl;
        return glm::mat4(1.0f);
    }

    if(ListaOgniw[i].ZwrocWskPoczatkowegoPrzegubu() != NULL)
    {
        if(ListaOgniw[i].ZwrocWskPoczatkowegoPrzegubu()->ZwrocWskNaDanePrzegubu()->TypPrzegubu == PrzegubRotacyjny)
        {
            return ListaOgniw[i].ZwrocWskPoczatkowegoPrzegubu()->ZwrocDanePrzegubu().KinematykaPrzegubu * ListaOgniw[i].ZwrocDaneOgniwa().MacierzRotZ;

        }else
        {
           return ListaOgniw[i].ZwrocWskPoczatkowegoPrzegubu()->ZwrocDanePrzegubu().KinematykaPrzegubu * ListaOgniw[i].ZwrocDaneOgniwa().MacierzTranZ;
        }

    }else
    {
        return glm::mat4(1.0f);
    }

}

template class LancuchKinematyczny<Ogniwo,Przegub>;
