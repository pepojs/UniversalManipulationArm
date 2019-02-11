#include "KManipulator.h"

template <typename TypOgniwa, typename TypPrzegubu>
Manipulator<TypOgniwa, TypPrzegubu>::Manipulator(Grafika3D* PobranaScena)
: Scena(PobranaScena) {;}

template <typename TypOgniwa, typename TypPrzegubu>
void Manipulator<TypOgniwa, TypPrzegubu>::DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu, IDKoncowegoPrzegubu);

    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    IDOgniw.push_back(NowyIdentyfikator);
}

template <typename TypOgniwa, typename TypPrzegubu>
void Manipulator<TypOgniwa, TypPrzegubu>::DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajPoczatkoweOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu);

    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    IDOgniw.push_back(NowyIdentyfikator);
}

template <typename TypOgniwa, typename TypPrzegubu>
void Manipulator<TypOgniwa, TypPrzegubu>::DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajKoncoweOgniwo(DaneOgniwa, IDKoncowegoPrzegubu);

    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    IDOgniw.push_back(NowyIdentyfikator);
}

template <typename TypOgniwa, typename TypPrzegubu>
uint16_t Manipulator<TypOgniwa, TypPrzegubu>::DodajPrzegub(TypPrzegubu DanePrzegubu)
{
    return LancuchManipulatora.DodajPrzegub(DanePrzegubu);
}

template class Manipulator<Ogniwo, Przegub>;
