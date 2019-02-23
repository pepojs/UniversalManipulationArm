#include "SCzesciManipulatora.h"NowaMacierzTranZ

Przegub::Przegub(RodzajPrzegubu NowyTypPrzegubu, GLfloat NowaWartoscKonfiguracji, glm::mat4 NowaKinematykaPrzegubu)
: TypPrzegubu(NowyTypPrzegubu), WartoscKonfiguracji(NowaWartoscKonfiguracji), KinematykaPrzegubu(NowaKinematykaPrzegubu){;}

Przegub::Przegub()
: TypPrzegubu(PrzegubRotacyjny), WartoscKonfiguracji(0.0f), KinematykaPrzegubu(glm::mat4(1.0f)){;}


Ogniwo::Ogniwo(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX, GLfloat NowaKonfiguracjaPoczatkowa)
: TablicaPunktow(NowaTablicaPunktow), RozmiarTablicy(NowyRozmiarTablicy), IloscWspolrzednych(NowaIloscWspolrzednych), IloscPunktow(NowaIloscPunktow),
MacierzRotZ(NowaMacierzRotZ), MacierzTranZ(NowaMacierzTranZ), MacierzTranX(NowaMacierzTranX), MacierzRotX(NowaMacierzRotX), KonfiguracjaPoczatkowa(NowaKonfiguracjaPoczatkowa) {;}


Ogniwo::Ogniwo(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych,
       GLuint NowaIloscPunktow, GLfloat RotZ, GLfloat TranZ, GLfloat TranX, GLfloat RotX, GLfloat NowaKonfiguracjaPoczatkowa)
: TablicaPunktow(NowaTablicaPunktow), RozmiarTablicy(NowyRozmiarTablicy), IloscWspolrzednych(NowaIloscWspolrzednych), IloscPunktow(NowaIloscPunktow)
{
    MacierzRotZ = glm::rotate(glm::mat4(1.0f), RotZ, glm::vec3(0.0f, 0.0f, 1.0f));
    MacierzTranZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, TranZ));
    MacierzTranX = glm::translate(glm::mat4(1.0f), glm::vec3(TranX, 0.0f, 0.0f));
    MacierzRotX = glm::rotate(glm::mat4(1.0f), RotX, glm::vec3(1.0f, 0.0f, 0.0f));

    KonfiguracjaPoczatkowa = NowaKonfiguracjaPoczatkowa;
}


Ogniwo::Ogniwo()
: TablicaPunktow(NULL), IloscWspolrzednych(0), IloscPunktow(0), MacierzRotZ(glm::mat4(1.0f)),
MacierzTranZ(glm::mat4(1.0f)), MacierzTranX(glm::mat4(1.0f)), MacierzRotX(glm::mat4(1.0f)),
KonfiguracjaPoczatkowa(0.0f) {;}


Chwytak::Chwytak(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX, GLfloat NowaKonfiguracjaPoczatkowa, glm::mat4 NowaKinematykaChwytaka)
: TablicaPunktow(NowaTablicaPunktow), RozmiarTablicy(NowyRozmiarTablicy), IloscWspolrzednych(NowaIloscWspolrzednych), IloscPunktow(NowaIloscPunktow),
MacierzRotZ(NowaMacierzRotZ), MacierzTranZ(NowaMacierzTranZ), MacierzTranX(NowaMacierzTranX), MacierzRotX(NowaMacierzRotX),
KonfiguracjaPoczatkowa(NowaKonfiguracjaPoczatkowa), KinematykaChwytaka(NowaKinematykaChwytaka) {;}


Chwytak::Chwytak(GLvoid* NowaTablicaPunktow, size_t NowyRozmiarTablicy, GLuint NowaIloscWspolrzednych,
       GLuint NowaIloscPunktow, GLfloat RotZ, GLfloat TranZ, GLfloat TranX, GLfloat RotX, GLfloat NowaKonfiguracjaPoczatkowa, glm::mat4 NowaKinematykaChwytaka)
: TablicaPunktow(NowaTablicaPunktow), RozmiarTablicy(NowyRozmiarTablicy), IloscWspolrzednych(NowaIloscWspolrzednych), IloscPunktow(NowaIloscPunktow)
{
    MacierzRotZ = glm::rotate(glm::mat4(1.0f), RotZ, glm::vec3(0.0f, 0.0f, 1.0f));
    MacierzTranZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, TranZ));
    MacierzTranX = glm::translate(glm::mat4(1.0f), glm::vec3(TranX, 0.0f, 0.0f));
    MacierzRotX = glm::rotate(glm::mat4(1.0f), RotX, glm::vec3(1.0f, 0.0f, 0.0f));

    KonfiguracjaPoczatkowa = NowaKonfiguracjaPoczatkowa;
    KinematykaChwytaka = NowaKinematykaChwytaka;
}


Chwytak::Chwytak()
: TablicaPunktow(NULL), IloscWspolrzednych(0), IloscPunktow(0), MacierzRotZ(glm::mat4(1.0f)),
MacierzTranZ(glm::mat4(1.0f)), MacierzTranX(glm::mat4(1.0f)), MacierzRotX(glm::mat4(1.0f)),
KonfiguracjaPoczatkowa(0.0f), KinematykaChwytaka(glm::mat4(1.0f))  {;}
