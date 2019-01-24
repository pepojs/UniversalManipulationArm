#include "Klasa_wierz_kraw.hpp"


//Tworzy krawedz miedzy dwoma wierzcholkami grafu
template <typename TypKrawedzi, typename TypWierzcholka>
void Wierzcholek<TypKrawedzi, TypWierzcholka>::UstawKrawedz(Krawedz<TypKrawedzi, TypWierzcholka> kra)
{
    //Zamienia kolejnosc tak aby wezel do ktorego dodajemy krawedz byl zapisany w lewym wierzcholku krawedzi
    //if(kra.ZwrocWartWierzL() == Dane)
        Kra.push_back(kra);
    //else
        //Kra.push_back(Krawedz<TypKrawedzi, TypWierzcholka>(kra.ZwrocWartKraw(),kra.ZwrocWskWierzP(), kra.ZwrocWskWierzL()));
}

template class Wierzcholek<Joint,Czlon>;
