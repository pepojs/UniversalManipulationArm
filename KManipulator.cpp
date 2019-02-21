#include "KManipulator.h"

template <typename TypOgniwa, typename TypPrzegubu>
KManipulator<TypOgniwa, TypPrzegubu>::KManipulator(Grafika3D* PobranaScena)
: Scena(PobranaScena), PrzesylajKonfiguracje(0) {;}

//Metoda pozawala dodac ogniwo do manipulatora,
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na poczatku ogniwa, identyfikator przegubu na koncu ogniwa,
//tablica z kolorami kolejnych punktow ogniwa oraz rozmiar teablicy z kolorami
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu, IDKoncowegoPrzegubu); //Dodaje ogniwo do lancucha

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);
}

//Metoda pozawala dodac ogniwo do manipulatora,
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na poczatku ogniwa, identyfikator przegubu na koncu ogniwa
//oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu, IDKoncowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwanie tablicy
    delete [] TablicaKolorow;
}

//Metoda pozawala dodac ogniwo do manipulatora,
//Argumentami sa tablica z punktami opisujacymi ogniwo, rozmiar tej tablicy, ilosc wspolrzednych potrzebnych do opisu jednego punktu,
//ilosc punktow opisujacych ogniwo, kat obrotu wokol osi Z, translacja po osi Z, translacja po osi X, kat obrotu wokol osi X
//(odczytane z tabelki D-H), konfiguracja poczatkowa (staly kat lub przesuniecie wzgledem osi Z, ktore nie jest wliczane do wartosc konfiguracji
//przegubu, czyli jezeli w tabelce dla RotZ jest q+PI/2 to to jest to PI/2), idetyfikator przegubu na poczatku ogniwa,
//identyfikator przegubu na koncu ogniwa oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow,
                     GLfloat RotZ, GLfloat TranZ, GLfloat TranX, GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDPoczatkowegoPrzegubu,
                     uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    TypOgniwa DaneOgniwa(TablicaPunktow, RozmiarTablicy, IloscWspolrzednych, IloscPunktow, RotZ, TranZ, TranX, RotX, KonfiguracjaPoczatkowa);

    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu, IDKoncowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwa niepotrzebna tablice kolorow
    delete [] TablicaKolorow;
}

//Metoda pozawala dodac ogniwo na poczatku manipulatora, nie posiada poczatkowego przegubu
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na koncu ogniwa, tablica z kolorami kolejnych punktow ogniwa
//oraz rozmiar teablicy z kolorami
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajPoczatkoweOgniwo(DaneOgniwa, IDKoncowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);
}

//Metoda pozawala dodac ogniwo na poczatku manipulatora, nie posiada poczatkowego przegubu
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na koncu ogniwa, oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajPoczatkoweOgniwo(DaneOgniwa, IDKoncowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwa tablice kolorow
    delete [] TablicaKolorow;
}

//Metoda pozawala dodac ogniwo na poczatku manipulatora, nie posiada poczatkowego przegubu
//Argumentami sa tablica z punktami opisujacymi ogniwo, rozmiar tej tablicy, ilosc wspolrzednych potrzebnych do opisu jednego punktu,
//ilosc punktow opisujacych ogniwo, kat obrotu wokol osi Z, translacja po osi Z, translacja po osi X, kat obrotu wokol osi X
//(odczytane z tabelki D-H), konfiguracja poczatkowa (staly kat lub przesuniecie wzgledem osi Z, ktore nie jest wliczane do wartosc konfiguracji
//przegubu, czyli jezeli w tabelce dla RotZ jest q+PI/2 to to jest to PI/2), identyfikator przegubu na koncu ogniwa
//oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajPoczatkoweOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow, GLfloat RotZ, GLfloat TranZ,
                               GLfloat TranX, GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDKoncowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    TypOgniwa DaneOgniwa(TablicaPunktow, RozmiarTablicy, IloscWspolrzednych, IloscPunktow, RotZ, TranZ, TranX, RotX, KonfiguracjaPoczatkowa);

    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajPoczatkoweOgniwo(DaneOgniwa, IDKoncowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwa tablice kolorow
    delete [] TablicaKolorow;
}

//Metoda pozawala dodac ogniwo na koncu manipulatora, nie posiada koncowego przegubu
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na poczatku ogniwa, tablica z kolorami kolejnych punktow ogniwa
//oraz rozmiar teablicy z kolorami
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, GLvoid* TablicaKolorow, size_t RozmiarTablicy)
{
    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajKoncoweOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych,
                                                          TablicaKolorow, RozmiarTablicy, 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);
}

//Metoda pozawala dodac ogniwo na koncu manipulatora, nie posiada koncowego przegubu
//Argumentami sa dane nowego ogniwa, idetyfikator przegubu na poczatku ogniwa, oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajKoncoweOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwa tablice kolorow
    delete [] TablicaKolorow;
}

//Metoda pozawala dodac ogniwo na koncu manipulatora, nie posiada koncowego przegubu
//Argumentami sa tablica z punktami opisujacymi ogniwo, rozmiar tej tablicy, ilosc wspolrzednych potrzebnych do opisu jednego punktu,
//ilosc punktow opisujacych ogniwo, kat obrotu wokol osi Z, translacja po osi Z, translacja po osi X, kat obrotu wokol osi X
//(odczytane z tabelki D-H), konfiguracja poczatkowa (staly kat lub przesuniecie wzgledem osi Z, ktore nie jest wliczane do wartosc konfiguracji
//przegubu, czyli jezeli w tabelce dla RotZ jest q+PI/2 to to jest to PI/2), identyfikator przegubu na poczatku ogniwa
//oraz kolor ogniwa podany jako wektor (RGBA)
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajKoncoweOgniwo(GLvoid* TablicaPunktow, size_t RozmiarTablicy, GLuint IloscWspolrzednych, GLuint IloscPunktow, GLfloat RotZ, GLfloat TranZ,
                               GLfloat TranX, GLfloat RotX, GLfloat KonfiguracjaPoczatkowa, uint16_t IDPoczatkowegoPrzegubu, glm::vec4 KolorOgniwa)
{
    TypOgniwa DaneOgniwa(TablicaPunktow, RozmiarTablicy, IloscWspolrzednych, IloscPunktow, RotZ, TranZ, TranX, RotX, KonfiguracjaPoczatkowa);

    //Dynamiczna alokacja tablicy kolorow potrzebnej przy dodawaniu obiektu do sceny, utworzona z wektoru koloru
    glm::vec4* TablicaKolorow = new glm::vec4 [DaneOgniwa.IloscPunktow];
    for(int i = 0; i < DaneOgniwa.IloscPunktow; i++)
        TablicaKolorow[i] = KolorOgniwa;

    //Tworzy nowy identyfikator ogniwa skladajacy sie z IDObiektu i IDOgniwa
    IdentyfikatorOgniwa NowyIdentyfikator;
    NowyIdentyfikator.IDOgniwa = LancuchManipulatora.DodajKoncoweOgniwo(DaneOgniwa, IDPoczatkowegoPrzegubu);

    //Tworzy nowy obiekt na scenie, ktory bedzie symulowal ogniwo
    NowyIdentyfikator.IDObiektuOgniwa = Scena->DodajObiekt(DaneOgniwa.TablicaPunktow, DaneOgniwa.RozmiarTablicy, DaneOgniwa.IloscWspolrzednych, TablicaKolorow,
                                                           DaneOgniwa.IloscPunktow * 4 * sizeof(GLfloat), 4, DaneOgniwa.IloscPunktow, Graf3D_PolaczonaKrawedz);

    //Liczy kinematyke calego lancucha oraz aktualizuje macierz transformacji danego ogniwa aby bylo odpowiednie umieszczone na scenie
    LancuchManipulatora.PoliczKinematyke();
    Scena->UstawMacierzTransformacji(NowyIdentyfikator.IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(NowyIdentyfikator.IDOgniwa));

    //Dodaje identyfikatory do listy
    IDOgniw.push_back(NowyIdentyfikator);

    //Usuwa tablice kolorow
    delete [] TablicaKolorow;
}


//Metoda pozwala dodac przegub do manipulatora,
//Argumentem sa dane przegubu, zwraca identyfikator przegubu
template <typename TypOgniwa, typename TypPrzegubu>
uint16_t KManipulator<TypOgniwa, TypPrzegubu>::DodajPrzegub(TypPrzegubu DanePrzegubu)
{
    return LancuchManipulatora.DodajPrzegub(DanePrzegubu);
}

//Metoda pozwala dodac ograniczenia przegubu, tak rzeby byl on rzeczywisty
//Jako argumenty przyjmuje identyfikator przegubu oraz strukture z podanymi ograniczeniami
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgraniczeniePrzegubu(uint16_t IDPrzegubu, OgraniczeniaPrzegubow Ograniczenie)
{
    if(Ograniczenia.find(IDPrzegubu) == Ograniczenia.end())
    {
        Ograniczenia[IDPrzegubu] = Ograniczenie;

    }else
    {
        cout<<"Ograniczenia dla przegubu o ID: "<<IDPrzegubu<<" juz istnieja ! Ograniczenia zostana zastapione"<<endl;
        Ograniczenia[IDPrzegubu] = Ograniczenie;
    }
}

//Metoda pozwala dodac ograniczenia przegubu, tak rzeby byl on rzeczywisty
//Jako argumenty przyjmuje identyfikator przegubu, rozdzielczosc silnika (najmniejsza wartosc o jaka silnik moze przesunac obrocic/przegub),
//minimalny kat jaki moze osiagnac przegub oraz maksymalny kat jaki moze osiagnac przegub
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgraniczeniePrzegubu(uint16_t IDPrzegubu, GLfloat Rozdzielczosc, GLfloat MinmalnyKat, GLfloat MaksymalnyKat, uint16_t NumerPrzegubu)
{
    OgraniczeniaPrzegubow NoweOgraniczenie(Rozdzielczosc, MinmalnyKat, MaksymalnyKat, NumerPrzegubu);

    if(Ograniczenia.find(IDPrzegubu) == Ograniczenia.end())
    {
        Ograniczenia[IDPrzegubu] = NoweOgraniczenie;

    }else
    {
        cout<<"Ograniczenia dla przegubu o ID: "<<IDPrzegubu<<" juz istnieja ! Ograniczenia zostana zastapione"<<endl;
        Ograniczenia[IDPrzegubu] = NoweOgraniczenie;
    }
}

template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::DodajOgranizczeniePrzesZadPrzegubu(uint16_t IDPrzegubu, OgraniczeniePrzestrzeniZadaniowej Ograniczenie)
{

    if(OgraniczeniaPrzestrzenZad.find(IDPrzegubu) == OgraniczeniaPrzestrzenZad.end())
    {
        OgraniczeniaPrzestrzenZad[IDPrzegubu].push_back(Ograniczenie);

    }else
    {
        vector<OgraniczeniePrzestrzeniZadaniowej>::iterator i = OgraniczeniaPrzestrzenZad[IDPrzegubu].begin();

        for(; i != OgraniczeniaPrzestrzenZad[IDPrzegubu].end(); i++)
            if(*i == Ograniczenie)
                return;

        OgraniczeniaPrzestrzenZad[IDPrzegubu].push_back(Ograniczenie);
    }

}


//Metoda pozwala zmienic ustawienie przegubu
//Argumentami sa identyfikator przegubu oraz nowa wartosc konfiguracji
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::ZmienKonfiguracjePrzegubu(uint16_t IDPrzegubu, GLfloat NowaKonfiguracja)
{
    map<uint16_t, OgraniczeniaPrzegubow>::iterator ItrPomocniczy = Ograniczenia.find(IDPrzegubu);
    GLfloat Pomocniczy;

    //Sprawdzenie czyprzegub ma jakies ograniczenia
    if(ItrPomocniczy != Ograniczenia.end())
    {
        //Sprawdza czy minimalny kat zostal odpowiednio ustawiony to znaczy czy jest wielokrotnoscia rozdzielczosci obrotu silnika
        //Z uwagni na typ float roznica moze wynosic pewien blad dlatego zamiast 0 jest 0.9999990, np float 244.999995 (ktory mial byc 245)
        //po rzutowaniu na int da 244 co w roznicy |244.999995 - 244| da 0.999995
        if(abs(ItrPomocniczy->second.MinimalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika - (int)(ItrPomocniczy->second.MinimalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika)) < 0.999990 &&
           abs((int)(ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) - ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) != 0)
            ItrPomocniczy->second.MinimalnyKat = ceil(ItrPomocniczy->second.MinimalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika)*ItrPomocniczy->second.RozdzielczoscSilnika;

        //Sprawdza czy minimalny kat zostal odpowiednio ustawiony to znaczy czy jest wielokrotnoscia rozdzielczosci obrotu silnika
        if(abs((int)(ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) - ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) < 0.999990 &&
           abs((int)(ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) - ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika) != 0)
            ItrPomocniczy->second.MaksymalnyKat = floor(ItrPomocniczy->second.MaksymalnyKat/ItrPomocniczy->second.RozdzielczoscSilnika)*ItrPomocniczy->second.RozdzielczoscSilnika;

        //Oblicza nowa konfiguracje tak zeby byla wielokrotnosciazaokroglonej liczby rownej podanemu katowi podzielonemu przez rozdzielczosc silnika
        //pozwala to ustaic rzeczywisty manipulator w pozycji, ktora jest dla niego mozliwa do osiagniecia
        Pomocniczy = NowaKonfiguracja/ItrPomocniczy->second.RozdzielczoscSilnika;
        Pomocniczy = round(Pomocniczy);
        NowaKonfiguracja = ItrPomocniczy->second.RozdzielczoscSilnika * Pomocniczy;

        //Sprawdza czy kat nie jest z poza dopuszczalnego przedzialu dla przegubu
        if(NowaKonfiguracja < ItrPomocniczy->second.MinimalnyKat)
            NowaKonfiguracja = ItrPomocniczy->second.MinimalnyKat;

        else if(NowaKonfiguracja > ItrPomocniczy->second.MaksymalnyKat)
            NowaKonfiguracja = ItrPomocniczy->second.MaksymalnyKat;

        cout<<"Numer przegubu: "<<ItrPomocniczy->second.NumerPrzegubu<<". Kat na kroki: "<<abs(NowaKonfiguracja/ItrPomocniczy->second.RozdzielczoscSilnika)<<endl;

        if(PrzesylajKonfiguracje == 1)
            Komunikacja.WysliDane(ItrPomocniczy->second.NumerPrzegubu, (uint16_t)abs(NowaKonfiguracja/ItrPomocniczy->second.RozdzielczoscSilnika));

    }

    Pomocniczy = LancuchManipulatora.ZwrocKonfiguracjePrzegubu(IDPrzegubu);

    LancuchManipulatora.ZmienKonfiguracjePrzegubu(IDPrzegubu, NowaKonfiguracja);

    if(!LancuchManipulatora.PoliczKinematyke(IDPrzegubu, OgraniczeniaPrzestrzenZad))
    {
        LancuchManipulatora.ZmienKonfiguracjePrzegubu(IDPrzegubu, Pomocniczy);
        LancuchManipulatora.PoliczKinematyke(IDPrzegubu);
    }


    for(size_t i = 0; i < IDOgniw.size(); i++)
        Scena->UstawMacierzTransformacji(IDOgniw[i].IDObiektuOgniwa, LancuchManipulatora.ZwrocTransformacjeOgniwa(IDOgniw[i].IDOgniwa));


    //Zmien konfiguracje rzeczywistego manipulatora (poczekaj) i jesli to mozliwe odczytaj z czujnikow pozycje rzeczywistego manipulatora,
    //i czy udalo mu sie osiagnac zadana pozycje (katy na przegubac)
}

//Metoda pozwala wyswietlic po koleji wszystkie kinematyki koncowych ogniw
template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::WyswietlKinematykeKoncowychOgniw()
{
    LancuchManipulatora.PoliczKinematyke();
    LancuchManipulatora.WyswietlKinematykeKoncowychOgniw();
}

template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::WybierzKomunikacje(RodzajKomunikacji NowyTyp)
{
    Komunikacja.WybierzKomunikacje(NowyTyp);
}

template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::PodlaczUrzadzenie(std::string& Port, int Parzystosc, int Rozmiar, int Stopbit, DWORD Predkosc)
{
    PrzesylajKonfiguracje = 0;
    Komunikacja.PodlaczUrzadzenie(Port, Parzystosc, Rozmiar, Stopbit, Predkosc);
}

template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::OdlaczUrzadzenie()
{
    Komunikacja.OdlaczUrzadzenie();
}

template <typename TypOgniwa, typename TypPrzegubu>
void KManipulator<TypOgniwa, TypPrzegubu>::WysliKonfiguracjePrzegubu(uint16_t NumerPrzegubu, uint16_t Kat)
{
    Komunikacja.WysliDane(NumerPrzegubu, Kat);
}

template class KManipulator<Ogniwo, Przegub>;


