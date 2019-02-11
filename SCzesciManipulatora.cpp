#include "SCzesciManipulatora.h"NowaMacierzTranZ

Przegub::Przegub(RodzajPrzegubu NowyTypPrzegubu, GLfloat NowaWartoscKonfiguracji, glm::mat4 NowaKinematykaPrzegubu)
: TypPrzegubu(NowyTypPrzegubu), WartoscKonfiguracji(NowaWartoscKonfiguracji), KinematykaPrzegubu(NowaKinematykaPrzegubu){;}

Przegub::Przegub()
: TypPrzegubu(PrzegubRotacyjny), WartoscKonfiguracji(0.0f), KinematykaPrzegubu(glm::mat4(1.0f)){;}

Ogniwo::Ogniwo(GLvoid* NowaTablicaPunktow, GLuint NowaIloscWspolrzednych, GLuint NowaIloscPunktow, glm::mat4 NowaMacierzRotZ,
           glm::mat4 NowaMacierzTranZ, glm::mat4 NowaMacierzTranX, glm::mat4 NowaMacierzRotX)
: TablicaPunktow(NowaTablicaPunktow), IloscWspolrzednych(NowaIloscWspolrzednych), IloscPunktow(NowaIloscPunktow), MacierzRotZ(NowaMacierzRotZ),
MacierzTranZ(NowaMacierzTranZ), MacierzTranX(NowaMacierzTranX), MacierzRotX(NowaMacierzRotX), MacierzPoczatkowaRotZ(NowaMacierzRotZ),
MacierzPoczatkowaTranZ(NowaMacierzTranZ) {;}

Ogniwo::Ogniwo()
: TablicaPunktow(NULL), IloscWspolrzednych(0), IloscPunktow(0), MacierzRotZ(glm::mat4(1.0f)),
MacierzTranZ(glm::mat4(1.0f)), MacierzTranX(glm::mat4(1.0f)), MacierzRotX(glm::mat4(1.0f)),
MacierzPoczatkowaRotZ(glm::mat4(1.0f)), MacierzPoczatkowaTranZ(glm::mat4(1.0f)) {;}
