#ifndef KLASA_GRAF_HPP
#define KLASA_GRAF_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <typeinfo>
#include "Klasa_wierz_kraw.hpp"


using namespace std;


template <typename TypKrawedzi, typename TypWierzcholka>
class Graf
{
    vector <Krawedz<TypKrawedzi, TypWierzcholka> > K;
    vector <Wierzcholek<TypKrawedzi, TypWierzcholka> > W;

    void DFSRekurencja(TypWierzcholka cel, Wierzcholek<TypKrawedzi, TypWierzcholka> wenzel, vector <Wierzcholek<TypKrawedzi, TypWierzcholka> > &w, vector <Wierzcholek<TypKrawedzi, TypWierzcholka> >odw);
public:


    void DodajWierzcholek(TypWierzcholka wartosc);
    int DodajKrawedz(TypKrawedzi wartosc,Wierzcholek<TypKrawedzi, TypWierzcholka> * wartoscL,Wierzcholek<TypKrawedzi, TypWierzcholka> * wartoscP);
    Wierzcholek<TypKrawedzi, TypWierzcholka>* ZwrocWskWierz(TypWierzcholka wartosc);
    void TworzGraf(char kon, char wierza, char krol);
    void WyswietlGraf();
    vector <TypWierzcholka> DFS(TypWierzcholka poczatek, TypWierzcholka cel);
    void ZmienDaneWierz(TypWierzcholka Ktory, TypWierzcholka NoweDane);
    unsigned int ZwrocIleWierz() {return W.size();}
    unsigned int ZwrocIleKraw() {return K.size();}
    TypWierzcholka ZwrocZawWierz( unsigned int Ktory) {return W[Ktory].ZwrocDane();}
    TypKrawedzi ZwrocZawKraw( unsigned int Ktory) {return K[Ktory].ZwrocWartKraw();}
    Krawedz<TypKrawedzi, TypWierzcholka> ZwrocKraw(unsigned int Ktory) {return K[Ktory];}

    void ZmienDaneKraw(unsigned int Ktora, TypKrawedzi NoweDane){K[Ktora].ZmienWartKraw(NoweDane);}
};


#endif // KLASA_GRAF_HPP
