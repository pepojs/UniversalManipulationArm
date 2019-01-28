#include "KGrafika3D.h"

Grafika3D::~Grafika3D()
{
    //Odlacza atrybuty dla vertex shader
    glDisableVertexAttribArray(0);

    //Usuwa vbo i vao
    glDeleteBuffers(vbo.size(), &vbo[0]);
    glDeleteVertexArrays(vao.size(), &vao[0]);
}

//Funkcja tworzy nowy obiekt na scenie rysowany statycznie, pierwszy argument to zbior puktow tego opiektu, drugi rozmiar tablicy punktow,
//trzeci argument to ilosc wspolrzednych opisujacych punkt
void Grafika3D::NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu)
{
    vao.push_back(0); //Nowa tablica obiektu (mozna w niej umiescic bufor z punktami, kolore itp.)
    vbo.push_back(0); //Nowy bufor obiektu dla punktow obiektu

    //Tworzy nowy voa i ustawia na aktywna
    glGenVertexArrays(1, &vao[vao.size()-1]);
    glBindVertexArray(vao[vao.size()-1]);

    //Tworzy nowy bufor, ustawia na aktywny i umieszcza dane z punktami
    glGenBuffers(1, &vbo[vbo.size()-1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo.size()-1]);
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicy, TablicaPunktow, GL_STATIC_DRAW);

    //Ustawia atrybut dla vertex shader
    if(IloscWspolrzednychPunktu >= 4 || IloscWspolrzednychPunktu == 0)
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    else
        glVertexAttribPointer(0, IloscWspolrzednychPunktu, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    //Dezaktywuje voa
    glBindVertexArray(0);
}

//Funkcja tworzy nowy obiekt na scenie rysowany statycznie oraz okresla jego kolor,
//pierwszy argument to zbior puktow tego opiektu, drugi rozmiar tablicy punktow,
//trzeci argument to ilosc wspolrzednych opisujacych punkt, czwarty argument to kolor odpowiedniego punktu,
//piaty argument to rozmiar tablicy kolorow, szusty ilosc elementow w wektorze opisujacym kolor (np. RGB i Alpha)
void Grafika3D::NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu,
                            GLvoid* TablicaKolorow, size_t RozmiarTablicyKolorow, uint8_t IloscWspolrzednychKoloru)
{
    vao.push_back(0); //Nowa tablica obiektu (mozna w niej umiescic bufor z punktami, kolore itp.)
    vbo.push_back(0); //Nowy bufor obiektu dla punktow obiektu
    vbo.push_back(0); //Nowy bufor obiektu dla kolorow odpowiednich punktow

    //Tworzy nowy voa i ustawia na aktywna
    glGenVertexArrays(1, &vao[vao.size()-1]);
    glBindVertexArray(vao[vao.size()-1]);

    //Punkty obiektu
    //Tworzy nowy bufor, ustawia na aktywny i umieszcza dane z punktami
    glGenBuffers(1, &vbo[vbo.size()-2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo.size()-2]);
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicy, TablicaPunktow, GL_STATIC_DRAW);

    //Ustawia atrybut dla vertex shader
    if(IloscWspolrzednychPunktu >= 4 || IloscWspolrzednychPunktu == 0)
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    else
        glVertexAttribPointer(0, IloscWspolrzednychPunktu, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    //Kolory obiektu
    //Tworzy nowy bufor, ustawia na aktywny i umieszcza dane z kolorem obiektu
    glGenBuffers(1, &vbo[vbo.size()-1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo.size()-1]);
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicyKolorow, TablicaKolorow, GL_STATIC_DRAW);

    //Ustawia atrybut dla vertex shader
        //Ustawia atrybut dla vertex shader
    if(IloscWspolrzednychKoloru >= 4 || IloscWspolrzednychKoloru == 0)
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    else
        glVertexAttribPointer(1, IloscWspolrzednychKoloru, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    //Dezaktywuje voa
    glBindVertexArray(0);
}

//Ustawia perspektywe ortogonalna (prostokatna), parametry to lewa i prawa, dolna i gorna
//krawedz przedniej sciany szescianu oraz odleglosc przedniej i tylniej scian
void Grafika3D::UstawRzutowanieOrtogonalne(GLfloat Lewa, GLfloat Prawa, GLfloat Dol, GLfloat Gora, GLfloat Przod, GLfloat Tyl)
{
    glm::mat4 rzut = glm::mat4(1.0f);
    rzut = glm::ortho(Lewa, Prawa, Dol, Gora, Przod, Tyl);

    shader.PrzekazMacierz4x4("rzutowanie", rzut);
}

//Ustawienie rzutowania perspektywicznego, parametry to kat miedzy liniami od kamery,
//stosunek miedzy szerokoscia, a wysokoscia ekranu oraz odleglosc przedniej i tylniej scian
void Grafika3D::UstawRzutowaniePerspektywiczne(GLfloat Kat, GLfloat ProporcjeEkranu, GLfloat Przod, GLfloat Tyl)
{
    glm::mat4 rzut = glm::mat4(1.0f);
    rzut = glm::perspective(Kat, ProporcjeEkranu, Przod, Tyl);

    shader.PrzekazMacierz4x4("rzutowanie", rzut);
}

void Grafika3D::Rysuj(SDL_Window* GlowneOkno)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); //Ustawia kolor tla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Czysci tlo
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    for(int i = 0; i < vao.size(); i++)
    {
        glBindVertexArray(vao[i]);
        //glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_BYTE, 0);
        glDrawArrays(GL_TRIANGLES, 0 ,36);

        glBindVertexArray(0);
    }

    glFlush();

    SDL_GL_SwapWindow(GlowneOkno);
}
