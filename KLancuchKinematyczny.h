/* _______________________________________________________________________
  |                                                                       |
  | Caly zamyst opiera sie na kolejnych powlokach, na przyklad na przegub |
  | nakładana jest kolejna klasa przeguby uzywajaca przegubu jako         |
  | pole z danymi oraz zawierajaca na przyklad ID i wskazniki na ogniwy   |
  | przylaczone do przegubu, nasepnie kolejna powloka jest lancuch laczy  |
  | przeguby i ogniwa w jedno doadajac kolejne funkcjie.                  |
  |_______________________________________________________________________|
*/

#ifndef _KLANCUCHKINEMATYCZNY_H
#define _KLANCUCHKINEMATYCZNY_H

#include <vector>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

#include "SCzesciManipulatora.h"
#include "SOgraniczeniaPrzegubu.h"

using namespace std;

template <typename TypPrzegubu>
class Przeguby;

//Ogniwa to klasa pozwalajaca na ogniwo nalozyc dodatkowe informacje potrzebne przy organizacji
//lancucha kinematycznego, a nie potrzebne z punktu widzenia pojedynczego ogniwa na przyklad
//wskazniki na przeguby podlaczone do ogniewa
template <typename TypOgniwa, typename TypPrzegubu>
class Ogniwa
{
    uint16_t IDOgniwa;
    TypOgniwa DaneOgniwa;
    Przeguby<TypPrzegubu>* PoczatkowyPrzegub;
    Przeguby<TypPrzegubu>* KoncowyPrzegub;

public:

    TypOgniwa ZwrocDaneOgniwa(){ return DaneOgniwa;}
    TypOgniwa* ZwrocWskNaDaneOgniwa(){ return &DaneOgniwa;}
    uint16_t ZwrocIDOgniwa() {return IDOgniwa;}
    Przeguby<TypPrzegubu>* ZwrocWskPoczatkowegoPrzegubu(){return PoczatkowyPrzegub;}
    Przeguby<TypPrzegubu>* ZwrocWskKoncowegoPrzegubu(){return KoncowyPrzegub;}
    void ZmienDaneOgniwa(TypOgniwa NoweDane) {this->DaneOgniwa = NoweDane;}
    void ZmienWskNaPoczatkowyPrzegub(Przeguby<TypPrzegubu>* NowyPoczatkowyPrzegub){PoczatkowyPrzegub = NowyPoczatkowyPrzegub;}
    void ZmienWskNaKoncwyPrzegub(Przeguby<TypPrzegubu>* NowyKoncowyPrzegub){KoncowyPrzegub = NowyKoncowyPrzegub;}
    void ZmienIDOgniwa(uint16_t NoweIDOgniwa){IDOgniwa = NoweIDOgniwa;}

};


template <typename TypChwytaka, typename TypPrzegubu>
class Chwytaki
{
    uint16_t IDChwytaka;
    TypChwytaka DaneChwytaka;
    Przeguby<TypPrzegubu>* PoczatkowyPrzegub;

public:

    TypChwytaka ZwrocDaneChwytaka(){ return DaneChwytaka;}
    TypChwytaka* ZwrocWskNaDaneChwytaka(){ return &DaneChwytaka;}
    uint16_t ZwrocIDChwytaka() {return IDChwytaka;}
    Przeguby<TypPrzegubu>* ZwrocWskPoczatkowegoPrzegubu(){return PoczatkowyPrzegub;}
    void ZmienDaneChwytaka(TypChwytaka NoweDane) {this->DaneChwytaka = NoweDane;}
    void ZmienWskNaPoczatkowyPrzegub(Przeguby<TypPrzegubu>* NowyPoczatkowyPrzegub){PoczatkowyPrzegub = NowyPoczatkowyPrzegub;}
    void ZmienIDChwytaka(uint16_t NoweIDChwytaka){IDChwytaka = NoweIDChwytaka;}
};


//Tak samo jak ogniwa, przeguby sa nakladane na przegub pozwalajac dodac kolejne dane do przegubu,
//ale nie potrzebne z punktu widzenia pojedynczego przegubu
template <typename TypPrzegubu>
class Przeguby
{
    uint16_t IDPrzegubu;
    TypPrzegubu DanePrzegubu;
    vector <uint16_t> IDPodlaczonychOgniw;
    vector <uint16_t> IDPodlaczonychChwytakow;

public:

    TypPrzegubu ZwrocDanePrzegubu(){ return DanePrzegubu;}
    TypPrzegubu* ZwrocWskNaDanePrzegubu(){ return &DanePrzegubu;}
    size_t ZwrocIloscOgniw(){return IDPodlaczonychOgniw.size();}
    size_t ZwrocIloscChwytakow(){return IDPodlaczonychChwytakow.size();}
    uint16_t ZwrocIDPodlaczonegoOgniwa(uint16_t NumerOgniwa){return IDPodlaczonychOgniw[NumerOgniwa];}
    uint16_t ZwrocIDPodlaczonegoChwytaka(uint16_t NumerChwytaka){return IDPodlaczonychChwytakow[NumerChwytaka];}
    uint16_t ZwrocIDPrzegubu(){return IDPrzegubu;}
    void ZmienDanePrzegubu(TypPrzegubu NoweDane) {DanePrzegubu = NoweDane;}
    void ZmienIDPrzegubu(uint16_t NoweIDPrzegubu){IDPrzegubu = NoweIDPrzegubu;}
    void DodajPodlaczoneOgniwo(uint16_t IDNowegoOgniwa){IDPodlaczonychOgniw.push_back(IDNowegoOgniwa);}
    void DodajPodlaczonyChwytak(uint16_t IDNowegoChwytaka){IDPodlaczonychChwytakow.push_back(IDNowegoChwytaka);}


};

//Lancuch kinematyczny laczy przeguby i ogniwa w jedna calosc. Dzieki polaczeniu
//ruch w jednym przegubie moze powodowac zmiane polorzenia innych przegubow i ogniw.
template <typename TypOgniwa, typename TypChwytaka, typename TypPrzegubu>
class KLancuchKinematyczny
{
    vector <Ogniwa<TypOgniwa, TypPrzegubu> > ListaOgniw;
    vector <Przeguby<TypPrzegubu> > ListaPrzegubow;
    vector <Chwytaki<TypChwytaka, TypPrzegubu> > ListaChwytakow;

public:

    //***Dodawanie nowego elementu do lancucha***
    uint16_t DodajOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu);
    uint16_t DodajPoczatkoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDKoncowegoPrzegubu);
    uint16_t DodajKoncoweOgniwo(TypOgniwa DaneOgniwa, uint16_t IDPoczatkowegoPrzegubu);
    uint16_t DodajChwytak(TypChwytaka DaneChwytaka, uint16_t IDPoczatkowegoPrzegubu);
    uint16_t DodajPrzegub(TypPrzegubu DanePrzegubu);

    void ZmienKonfiguracjePrzegubu(uint16_t IDPrzegubu, GLfloat NowaKonfiguracja);
    void ZmienKinematykePrzegubu(uint16_t IDPrzegubu, glm::mat4 NowaKinematykaPrzegubu);
    void ZmienMacierzRotZOgniwa(uint16_t IDOgniwa, glm::mat4 NowaMacierzRotZ);
    void ZmienMacierzTranZOgniwa(uint16_t IDOgniwa, glm::mat4 NowaMacierzTranZ);

    void PoliczKinematyke();
    void PoliczKinematyke(uint16_t IDPoczatkowegoPrzegubu, uint16_t IDKoncowegoPrzegubu);
    void PoliczKinematyke(uint16_t IDPoczatkowegoPrzegubu);
    uint8_t PoliczKinematyke(uint16_t IDPoczatkowegoPrzegubu, map <uint16_t, vector <OgraniczeniePrzestrzeniZadaniowej> > Ograniczenia,
                             map <uint16_t, vector <OgraniczeniePrzestrzeniZadaniowej> > OgraniczeniaChwytaka);

    glm::mat4 ZwrocTransformacjeOgniwa(uint16_t IDOgniwa);
    glm::mat4 ZwrocTransformacjeChwytaka(uint16_t IDChwytaka);
    GLfloat ZwrocKonfiguracjePrzegubu(uint16_t IDPrzegubu);

    uint8_t SprawdzOgraniczeniaPrzesZad(glm::mat4 Kinematyka, vector <OgraniczeniePrzestrzeniZadaniowej> Ograniczenia);

    void WyswietlKinematykeKoncowychOgniw();
    void WyswietlKinematykeChwytaka(uint16_t IDChwytaka);

};



#endif // KLANCUCHKINEMATYCZNY_H
