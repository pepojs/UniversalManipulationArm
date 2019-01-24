#include "Klasa_graf.hpp"

//Dodawanie wierzcholka do grafu
template <typename TypKrawedzi, typename TypWierzcholka>
void Graf<TypKrawedzi, TypWierzcholka>::DodajWierzcholek(TypWierzcholka wartosc)
{
    //Sprawdzenie czy taki wierzcholek juz istnieje
    for(unsigned int i = 0; i < W.size(); i++)
    {
        if(W[i].ZwrocDane() == wartosc)
        {
            //cout<<"Wezel o tej wartosci juz istnieje"<<endl;
            return;
        }
    }
    //jezeli wierzcholek nie istnieje to dodaje wierzcholka do grafu
    W.push_back(Wierzcholek<TypKrawedzi, TypWierzcholka>(wartosc));
}

//Zwraca wskaznik na wierzcholek
template <typename TypKrawedzi, typename TypWierzcholka>
Wierzcholek<TypKrawedzi, TypWierzcholka>* Graf<TypKrawedzi, TypWierzcholka>::ZwrocWskWierz(TypWierzcholka wartosc)
{
    //jezeli wierzcholek istnieje zwraca wskaznik na niego
    for(unsigned int i = 0; i < W.size(); i++)
    {
        if(W[i].ZwrocDane() == wartosc) return &W[i];
    }

    //inaczej null
    return NULL;
}

//Dodaje krawedz miedzy dwoma wierzcholkami
template <typename TypKrawedzi, typename TypWierzcholka>
int Graf<TypKrawedzi, TypWierzcholka>::DodajKrawedz(TypKrawedzi wartosc, Wierzcholek<TypKrawedzi, TypWierzcholka>* L,
                                                    Wierzcholek<TypKrawedzi, TypWierzcholka>* P)
{
    //Sprawdza czy krawedz juz istnieje
    for(unsigned int i = 0; i < K.size(); i++)
    {
        if((K[i].ZwrocWartWierzL() == L->ZwrocDane() && K[i].ZwrocWartWierzP() == P->ZwrocDane()))// ||
           //(K[i].ZwrocWartWierzL() == P->ZwrocDane() && K[i].ZwrocWartWierzP() == L->ZwrocDane()))
        {
            //cout<<"Krawedz o tej wartosci juz istnieje"<<endl;
            return 1;
        }
    }

    //Tworzy krawedz miedzy wierzcholkami L i P o wartosci
    Krawedz<TypKrawedzi, TypWierzcholka> pom(wartosc, L, P);
    K.push_back(pom); //Dodaje do listy krawedzi
    L->UstawKrawedz(K.back());
    P->UstawKrawedz(K.back());
    return 0;
}

//Tworzy graf
/*template <typename TypKrawedzi, typename TypWierzcholka>
void Graf<TypKrawedzi, TypWierzcholka>::TworzGraf(char kon, char wierza, char krol)
{
    //Czysci liste krawedzi i wierzcholkow grafu
    K.clear();
    W.clear();

    int wierza_j = 0, wierza_i = 0, i, j;
    char tab_pom[5][5]; //Tworzy tablice pomocnicza 5x5 odpowiadajaca planszy
    const int ruchy_rzad[] = {1, 2, 2, 1, -1, -2, -2, -1};
    const int ruchy_kolu[] = {-2, -1, 1, 2,2, 1, -1, -2};

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
        {
            if(wierza == 'A'+j+(i*5)) //zapisuje kolumne i rzad w ktorej stoji wierza
            {
                wierza_i = i;
                wierza_j = j;
            }

            tab_pom[i][j] = 'A'+j+(i*5); //Wypelnia tablice kolejnymi nazwami pol

        }

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
        {
            if(i == wierza_i || j == wierza_j) //Zaznacza pola w ktorych kon nie moze stanac
                tab_pom[i][j] = 0;
            else
                DodajWierzcholek(tab_pom[i][j]);

        }


    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
        {
            if(tab_pom[i][j] != 0)
            {
                //Sprawdza wszystkie ruchy konia
                for(int k = 0; k < 8; k++)
                {
                    //jezeli ruch jest mozliwy (nie wychodzi poza tablice i nie staje na polu bicia wierzy)
                    if((j + ruchy_rzad[k] >= 0 && j + ruchy_rzad[k] < 5) &&
                    (i + ruchy_kolu[k] >= 0 && i + ruchy_kolu[k] < 5) &&
                    (tab_pom[i + ruchy_kolu[k]][j + ruchy_rzad[k]] != 0))
                    {
                        //Dodaje wierzcholek i tworzy krawedz miedzy wierzcholkami
                        DodajWierzcholek(tab_pom[i + ruchy_kolu[k]][j + ruchy_rzad[k]]);
                        DodajKrawedz(3, ZwrocWskWierz(tab_pom[i][j]), ZwrocWskWierz(tab_pom[i + ruchy_kolu[k]][j + ruchy_rzad[k]]));

                    }

                }
            }
        }

}
*/
//Wyswietla wszystkie wierzcholki w grafie wraz z krawedziami
template <typename TypKrawedzi, typename TypWierzcholka>
void Graf<TypKrawedzi, TypWierzcholka>::WyswietlGraf()
{
    for(unsigned int i = 0; i < W.size(); i++)
    {
        W[i].Wyswietl();
    }

}

//Metoda uzywana podczas przeszukiwania w glab grafu
template <typename TypKrawedzi, typename TypWierzcholka>
void Graf<TypKrawedzi, TypWierzcholka>::DFSRekurencja(TypWierzcholka cel, Wierzcholek<TypKrawedzi, TypWierzcholka> wenzel,
                                                      vector <Wierzcholek<TypKrawedzi, TypWierzcholka> > &w,
                                                      vector <Wierzcholek<TypKrawedzi, TypWierzcholka> >odw)
{
    int flaga = 0;

    //Sprawdzanie wszystkich krawedzi przypisanych wierzcholkowi
    for(unsigned int i = 0; i < wenzel.IloscKrawedzi(); i++)
    {
        //jezeli krawedz zaczyna sie i konczy tym samym wierzcholkiem
        if((wenzel.ZwrocKrawedz(i).ZwrocWskWierzP())->ZwrocDane() == wenzel.ZwrocDane()) continue;

        //Sprawdza czy wierzcholek na koncu krawedzi (nastepny) nie byl juz odwiedzony
        for(unsigned int j = 0; j < odw.size(); j++)
        {
            if(odw[j].ZwrocDane() == (wenzel.ZwrocKrawedz(i).ZwrocWskWierzP())->ZwrocDane())
            {
                flaga = 1;
                break;
            }
        }

        //jezeli wierzcholek byl odwiedzony to sprawdza nastepna krawedz
        if(flaga)
        {
            if(wenzel.ZwrocDane() == cel)
            {
                if(!odw.empty())
                {
                    //jezeli dany wirzcholek nie byl dodany do list odwiedzonych
                    if(odw.back().ZwrocDane() != wenzel.ZwrocDane())
                    odw.push_back(wenzel);
                }
                else odw.push_back(wenzel);

                //jezeli lista odwiedzonych wierzcholkow jest krotsza od wyniku
                if(w.size() != 0 && w.size() > odw.size())
                {
                    w.swap(odw);//Zamienia liste wynik z odwiedzonymi wierzcholkami

                }else if(w.size() == 0)
                {
                    w.swap(odw);
                }
                return;
            }

            flaga = 0;
            continue;
        }

        if(!odw.empty())
        {
            //jezeli dany wirzcholek nie byl dodany do list odwiedzonych
            if(odw.back().ZwrocDane() != wenzel.ZwrocDane())
            odw.push_back(wenzel);
        }
        else odw.push_back(wenzel);

        //jezeli osiagnieto pole, na ktorym stoi krol
        if(wenzel.ZwrocDane() == cel)
        {

            //jezeli lista odwiedzonych wierzcholkow jest krotsza od wyniku
            if(w.size() != 0 && w.size() > odw.size())
            {
                w.swap(odw);//Zamienia liste wynik z odwiedzonymi wierzcholkami

            }else if(w.size() == 0)
            {
                w.swap(odw);
            }
            return;
        }


        //Rekurencja
        DFSRekurencja(cel, *wenzel.ZwrocKrawedz(i).ZwrocWskWierzP(), w, odw);
    }

}


//DFS
template <typename TypKrawedzi, typename TypWierzcholka>
vector<TypWierzcholka> Graf<TypKrawedzi, TypWierzcholka>::DFS(TypWierzcholka poczatek, TypWierzcholka cel)
{
    Czlon c;
    Wierzcholek<TypKrawedzi, TypWierzcholka> Pierwszy(c);
    vector<Wierzcholek<TypKrawedzi, TypWierzcholka> > Odwiedzone;
    vector<Wierzcholek<TypKrawedzi, TypWierzcholka> > Wynik;

    vector<TypWierzcholka> Zwracane;

    //Szuka w grafie pierwszego wierzcholka, na ktorym stoi kon
    for(unsigned int i = 0; i < W.size(); i++)
    {
        if(W[i].ZwrocDane() == poczatek)
        {
            Pierwszy = W[i];
            break;
        }
    }

    //Rekurencyjne wywolanie DFS
    DFSRekurencja(cel, Pierwszy,Wynik, Odwiedzone);

    //Wyswietla wynik przeszukiwania


    if(Wynik.size() == 0)
    {
        cout<<endl<<"Wynik dla DFS: "<<endl;
        cout<<"Brak rozwiazania !"<<endl;

    }/*else
    {
        cout<<endl<<"Wynik dla DFS: "<<endl;
        for(unsigned int i = 0; i < Wynik.size(); i++)
        {
            cout<<Wynik[i].ZwrocDane()<<" ";
        }
        cout<<endl;
    }
*/
    for(unsigned int i = 0; i < Wynik.size(); i++)
    {
        Zwracane.push_back(Wynik[i].ZwrocDane());
    }

    return Zwracane;


}

template <typename TypKrawedzi, typename TypWierzcholka>
void Graf<TypKrawedzi, TypWierzcholka>::ZmienDaneWierz(TypWierzcholka Ktory, TypWierzcholka NoweDane)
{
    for(unsigned int i = 0; i < W.size(); i++)
    {
        if(Ktory == W[i].ZwrocDane())
        {
            W[i].ZmienDane(NoweDane);
            return;
        }
    }

    cout<<"Nie ma takiego wierzcholka"<<endl;
    return;
}

template class Graf<Joint,Czlon>;

