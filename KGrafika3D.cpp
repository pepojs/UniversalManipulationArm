#include "KGrafika3D.h"

Grafika3D::~Grafika3D()
{
    //Odlacza atrybuty dla vertex shader
    glDisableVertexAttribArray(0);

    //Usuwa vbo i vao
    glDeleteBuffers(vbo.size(), &vbo[0]);
    glDeleteVertexArrays(vao.size(), &vao[0]);
}

void Grafika3D::NowyObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicy)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //Dezaktywuje voa
    glBindVertexArray(0);
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
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glBindVertexArray(0);
    }

    glFlush();

    SDL_GL_SwapWindow(GlowneOkno);
}
