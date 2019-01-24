//http://headerphile.com/sdl2/opengl-part-1-sdl-opengl-awesome/

#include <SDL.h>
#define GLEW_STATIC
#include <glew.h>

#include <iostream>
#include <ctime>
#include "KGrafika3D.h"


#undef main

using namespace std;

GLfloat Obiekt1[] ={
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

GLfloat Obiekt2[] ={
    -0.2f, -0.2f, 0.0f,
    0.8f, -0.8f, 0.0f,
    0.0f, 0.1f, 0.0f
};

const float rozmiar_sceny = 25;

//Zmienne dla TransBlock
GLuint trbi, trbuf;
GLint trbsize, trbofs[3];
/*
//Pole obserwatora
int win_wysokosc, win_szerokosc;
float lewa, prawa, dol, gora, przod, tyl;

//Pozycja obserwatora
const float obser_poz0[4] = {0.0, 0.0, 10, 1.0};
int ostatniX, ostatniY;

float obser_obrvec[3] = {1.0, 0.0, 0.0};
float obser_obrkat = 0.0;

int opcja = 0;

//Zmienne do animacji
float model_obrot_os[3] = {0.0, 1.0, 0.0};
float model_obrot_kat0 = 0.0;
float model_obrot_kat;

clock_t zegar0;
float czas_app, czas_app0;

uint8_t wl_anim = 0;

float RDOS(float r) {return r*180.0/M_PI;}
double RDOS(double r) {return r*180.0/M_PI;}
*/
uint8_t Inicjacja(SDL_Window** GlowneOkno, SDL_GLContext* GlownyKonteks)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout<<" Nieudana inicjalizacja SDL : "<<SDL_GetError()<<endl;
        return -1;
    }

    *GlowneOkno = SDL_CreateWindow("Manipulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
    if(GlowneOkno == NULL)
    {
        cout<<" Nieudalo sie stworzyc okna : "<<SDL_GetError()<<endl;
        return -1;
    }

    *GlownyKonteks = SDL_GL_CreateContext(*GlowneOkno);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    return 0;
}

uint8_t UstawianieShaderow(Shader *shader)
{
    shader->Init();
    if(!shader->WczytajShader("Vert.glsl", GL_VERTEX_SHADER))
        return -1;

    if(!shader->WczytajShader("Frag.glsl", GL_FRAGMENT_SHADER))
        return -1;

    if(!shader->LinkowanieShader())
        return -1;

    return 0;
}

/*
uint8_t UstawianieShaderow(Shader *shader)
{
    //TransBlock to macierze przekazywane do shadera
    static const GLchar* UTBNazwy[] =
    {"TransBlock", "TransBlock.mm", "TransBlock.vm", "TransBlock.pm"};

    GLuint ind[3];

    shader->Init();
    if(!shader->WczytajShader("Vertex.glsl", GL_VERTEX_SHADER))
        return -1;

    if(!shader->WczytajShader("Fragment.glsl", GL_FRAGMENT_SHADER))
        return -1;

    if(!shader->LinkowanieShader())
        return -1;

    //Zwraca identyfikator bloku zmiennych jednolitych (utworzonych w programie shadera)
    trbi = glGetUniformBlockIndex(shader->ZwrocProgramID(), UTBNazwy[0]);

    //Pobiera rozmiar bloku i zapisuje do zmiennej trbsize
    glGetActiveUniformBlockiv(shader->ZwrocProgramID(), trbi, GL_UNIFORM_BLOCK_DATA_SIZE, &trbsize);

    //Pobiera z programu informacje o poszczegulnych polach struktury i zapisuje indeksy tych pol do ind
    glGetUniformIndices(shader->ZwrocProgramID(), 3, &UTBNazwy[1], ind);

    //Pobiera przesuniecie poszczegolnych pol struktury wzgledem poczatku i zapisuje do trbofs[3]
    glGetActiveUniformsiv(shader->ZwrocProgramID(), 3, ind, GL_UNIFORM_OFFSET, trbofs);

    //Dowiazuje blok zmiennych jednolitych TransBlock z punktem 0 w GL_UNIFORM_BUFFER
    glUniformBlockBinding(shader->ZwrocProgramID(), trbi, 0);

    //Tworzy obiekt buforu
    glGenBuffers(1, &trbuf);

    //Przywiazanie buforu do celu 0 z GL_UNIFORM_BUFFER
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, trbuf);

    //Przesyla dane, w tym przypadku dane sa NULL, funkcja ustawia rozmiar buforu i sposob jego uzycia
    glBufferData(GL_UNIFORM_BUFFER, trbsize, NULL, GL_DYNAMIC_DRAW);

    return 0;
    //return SprawdzGLError();

    //shader.Uzyjprogramu();
}
*/
/*
uint8_t UstawMacierzModelu(float os[3], float kat)
{
    GLfloat m[16];

    M4x4ObrotVf(m, os[0], os[1], os[2], kat);
    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[0], 16*sizeof(GLfloat), m);

    return SprawdzGLError();
}

uint8_t UstawMacierzModelu(const GLfloat nm[16])
{
    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[0], 16*sizeof(GLfloat), nm);

    return SprawdzGLError();
}

uint8_t UstawMacierzModelu(float os[3], float kat, const GLfloat nm[16])
{
    GLfloat m[16];
    GLfloat m1[16];

    M4x4ObrotVf(m1, os[0], os[1], os[2], kat);
    M4x4Mnozenief(m, nm, m1);

    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[0], 16*sizeof(GLfloat), m);

    return SprawdzGLError();
}

uint8_t InicMacierzObserwatora()
{
    GLfloat m[16];

    M4x4Translacjaf(m, -obser_poz0[0], -obser_poz0[1], -obser_poz0[2]);

    //Przywiazuje UBO do celu GL_UNIFORM_BUFFER
    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);

    //Wpisuje podana liczbe bajtow (3 parametr) do bufora
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[1], 16*sizeof(GLfloat), m);

    return SprawdzGLError();
}

uint8_t ZmienKsztalt(SDL_Window** GlowneOkno)
{
    GLfloat m[16];
    float lp;

    SDL_GetWindowSize(*GlowneOkno, &win_szerokosc, &win_wysokosc);

    //Klatka jest calym oknem
    glViewport(0, 0, win_szerokosc, win_wysokosc);
    lp = rozmiar_sceny*(float)win_szerokosc/(float)win_wysokosc;
    M4x4OstScietyf(m, NULL, -lp, lp, -rozmiar_sceny, rozmiar_sceny, 5, 15);

    //Przywiazuje UBO do celu GL_UNIFORM_BUFFER
    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);

    //Wpisuje podana liczbe bajtow (3 parametr) do bufora
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[2], 16*sizeof(GLfloat), m);

    //Zapisuje obszar obserwacji
    lewa = -(prawa = lp);
    dol = -(gora = rozmiar_sceny/2);
    przod = 5.0;
    tyl = 15.0;

    return SprawdzGLError();
}

uint8_t ObrocObserwatora(int deltaX, int deltaY)
{
    float v1[3], lgt, kat1, v2[3], kat2;
    GLfloat tm[16], vm[16], rm[16];

    //Blad dzielenia przez zero
    if(deltaX == 0 && deltaY == 0)
        return 2;

    v1[0] = (float)deltaY*(prawa-lewa)/(float)win_wysokosc;
    v1[1] = (float)deltaX*(gora-dol)/(float)win_szerokosc;
    v1[2] = 0.0;

    lgt = sqrt(V3IloczynSka(v1, v1));
    v1[0] /= lgt; v1[1] /= lgt;

    kat1 = -0.052359878; //-3 stopnie

    V3ZlozObrot(v2, &kat2, obser_obrvec, obser_obrkat, v1, kat1);
    for(int i = 0; i < 3; i++) obser_obrvec[i] = v2[i];
    obser_obrkat = kat2;

    M4x4Translacjaf(tm, -obser_poz0[0], -obser_poz0[1], -obser_poz0[2]);
    M4x4ObrotVf(rm, obser_obrvec[0], obser_obrvec[1], obser_obrvec[2], -obser_obrkat);
    M4x4Mnozenief(vm, tm, rm);

    glBindBuffer(GL_UNIFORM_BUFFER, trbuf);
    glBufferSubData(GL_UNIFORM_BUFFER, trbofs[1], 16*sizeof(GLfloat), vm);

    return SprawdzGLError();
}

void Rysuj(SDL_Window* GlowneOkno, GLuint vbo[9], GLuint vao[4], Lancuch Lan)
{
    GLfloat m[16];
    M4x4Jednof(m);
    switch(opcja)
    {
        case 0:
            glClearColor(0.0, 0.0, 0.0, 1.0); //Ustawia kolor tla
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Czysci tlo
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);

            glLineWidth(1.0);
            UstawMacierzModelu(m);
            glBindVertexArray(vao[3]);
            glDrawArrays(GL_LINES, 0, 6);

            UstawMacierzModelu(Lan.ZwrocZawCzlonu("L0").A);
            glBindVertexArray(vao[0]);
            glPointSize(5.0);
            glDrawArrays(GL_POINTS, 0, 1);

            glLineWidth(3.0);
            UstawMacierzModelu(Lan.ZwrocZawCzlonu("L1").A);
            glBindVertexArray(vao[1]);
            glDrawArrays(GL_LINES, 0, 2);

            UstawMacierzModelu(Lan.ZwrocZawCzlonu("L2").A);
            glBindVertexArray(vao[2]);
            glDrawArrays(GL_LINES, 0, 2);

            UstawMacierzModelu(Lan.ZwrocZawCzlonu("L3").A);
            glBindVertexArray(vao[4]);
            glDrawArrays(GL_LINES, 0, 2);

            glFlush();

            SDL_GL_SwapWindow(GlowneOkno);
        break;

        case 1:
            glClearColor(0.0, 0.0, 0.0, 1.0); //Ustawia kolor tla
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Czysci tlo
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_BYTE, 0);

            glFlush();

            SDL_GL_SwapWindow(GlowneOkno);
        break;

        case 2:
            glClearColor(0.0, 0.0, 0.0, 1.0); //Ustawia kolor tla
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Czysci tlo
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
            glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_BYTE, 0);

            glFlush();

            SDL_GL_SwapWindow(GlowneOkno);//Wstawia buff na okno
        break;

        default:
        break;
    }

}

void UstawObjektyBuff(GLuint *vbo, GLuint *vao, Lancuch Lan)
{
    zegar0 = clock();
    czas_app = czas_app0 = 0.0;
    UstawMacierzModelu(model_obrot_os, model_obrot_kat0);

    // Tworzy nowy pusty VAO (vertex array object)
    glGenVertexArrays(5, vao);

    // Przywiazuje nowy VAO (staje sie biezacy w kontekscie)
    glBindVertexArray(vao[0]);

    // Tworzy 3 nowe puste VBO (vertex buffer object)
    glGenBuffers(11, vbo);

    //Punkty
    //Przywiazywanie do GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    //Wypelnianie danymi
    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L0").IlePunktow*Lan.ZwrocZawCzlonu("L0").IleWspol)*sizeof(GLfloat), Lan.ZwrocZawCzlonu("L0").Punkty, GL_STATIC_DRAW);


    //Przekazuje informacje natemat tablicy umieszczonej w buforze do VAO
    glVertexAttribPointer(pozycjaAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Wlacza pobieranie atrybutu z tablicy VAO
    glEnableVertexAttribArray(pozycjaAttributeIndex);

    //Kolor
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L0").IlePunktow*(Lan.ZwrocZawCzlonu("L0").IleWspol+1))*sizeof(GLfloat), kczlon1, GL_STATIC_DRAW);

    glVertexAttribPointer(kolorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(kolorAttributeIndex);


    glBindBuffer(GL_ARRAY_BUFFER, 0);




    glBindVertexArray(vao[1]);

    //Punkty
    //Przywiazywanie do GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

    //Wypelnianie danymi
    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L1").IlePunktow*Lan.ZwrocZawCzlonu("L1").IleWspol)*sizeof(GLfloat), Lan.ZwrocZawCzlonu("L1").Punkty, GL_STATIC_DRAW);

    //Przekazuje informacje natemat tablicy umieszczonej w buforze do VAO
    glVertexAttribPointer(pozycjaAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Wlacza pobieranie atrybutu z tablicy VAO
    glEnableVertexAttribArray(pozycjaAttributeIndex);

    //Kolor
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);

    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L1").IlePunktow*(Lan.ZwrocZawCzlonu("L1").IleWspol+1))*sizeof(GLfloat), kczlon2, GL_STATIC_DRAW);

    glVertexAttribPointer(kolorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(kolorAttributeIndex);


    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(vao[2]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);

    //Wypelnianie danymi
    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L2").IlePunktow*Lan.ZwrocZawCzlonu("L2").IleWspol)*sizeof(GLfloat), Lan.ZwrocZawCzlonu("L2").Punkty, GL_STATIC_DRAW);


    //Przekazuje informacje natemat tablicy umieszczonej w buforze do VAO
    glVertexAttribPointer(pozycjaAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Wlacza pobieranie atrybutu z tablicy VAO
    glEnableVertexAttribArray(pozycjaAttributeIndex);

    //Kolor
    glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);

    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L2").IlePunktow*(Lan.ZwrocZawCzlonu("L2").IleWspol+1))*sizeof(GLfloat), kczlon3, GL_STATIC_DRAW);

    glVertexAttribPointer(kolorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(kolorAttributeIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glBindVertexArray(vao[3]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);

    //Wypelnianie danymi

    glBufferData(GL_ARRAY_BUFFER, (floatsNaPunkt*punkty)*sizeof(GLfloat), obiekt, GL_STATIC_DRAW);


    //Przekazuje informacje natemat tablicy umieszczonej w buforze do VAO
    glVertexAttribPointer(pozycjaAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Wlacza pobieranie atrybutu z tablicy VAO
    glEnableVertexAttribArray(pozycjaAttributeIndex);

    //Kolor
    glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);

    glBufferData(GL_ARRAY_BUFFER, (floatsNaKolor*punkty)*sizeof(GLfloat), kolor, GL_STATIC_DRAW);

    glVertexAttribPointer(kolorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(kolorAttributeIndex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[8]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesNaKsztalt*sizeof(GLbyte), ksztalt, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glBindVertexArray(vao[4]);

    //Punkty
    //Przywiazywanie do GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);

    //Wypelnianie danymi
    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L3").IlePunktow*Lan.ZwrocZawCzlonu("L3").IleWspol)*sizeof(GLfloat), Lan.ZwrocZawCzlonu("L3").Punkty, GL_STATIC_DRAW);

    //Przekazuje informacje natemat tablicy umieszczonej w buforze do VAO
    glVertexAttribPointer(pozycjaAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Wlacza pobieranie atrybutu z tablicy VAO
    glEnableVertexAttribArray(pozycjaAttributeIndex);

    //Kolor
    glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);

    glBufferData(GL_ARRAY_BUFFER, (Lan.ZwrocZawCzlonu("L3").IlePunktow*(Lan.ZwrocZawCzlonu("L3").IleWspol+1))*sizeof(GLfloat), kczlon4, GL_STATIC_DRAW);

    glVertexAttribPointer(kolorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(kolorAttributeIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void PrzelaczAnimacja()
{
    if(wl_anim == 0)
    {
        wl_anim = 1;
        czas_app0 = czas_app = (float)(clock() - zegar0)/CLOCKS_PER_SEC;
        model_obrot_kat = model_obrot_kat0;

    }else
    {
        wl_anim = 0;
        model_obrot_kat0 = model_obrot_kat;
    }
}

void Animacja(SDL_Window* GlowneOkno, GLuint vbo[11], GLuint vao[5], Lancuch Lan)
{
    if(wl_anim == 1)
    {
        czas_app = (float)(clock() - czas_app0)/CLOCKS_PER_SEC;
        model_obrot_kat = model_obrot_kat0 + 0.78539816*(czas_app - czas_app0);

        if(model_obrot_kat>= 2*M_PI)model_obrot_kat -= 2*M_PI;

        //UstawMacierzModelu(model_obrot_os, model_obrot_kat);
        Lan.ObliczMacierzR("J0", &model_obrot_kat, 1);
        Lan.ObliczMacierzR("J1", &model_obrot_kat, 1);
        Lan.ObliczMacierzR("J2", &model_obrot_kat, 1);

        Lan.ObliczMacierzA("L0", "L3");
        Rysuj(GlowneOkno, vbo, vao, Lan);
    }
}

*/
int main()
{
    SDL_Window* GlowneOkno;
    SDL_GLContext GlownyKonteks;
    Grafika3D Scena;


    //GLuint vbo[11], vao[5];
   // Shader shader;
   // Joint tempJ;
   // GLfloat m[16];
   // Lancuch Lan;
   // GLfloat nowyArt = 0;
   // float xk = 20;
   // float yk = 20;


    //int mysz_lewy_wcisniety = 0;

    if(Inicjacja(&GlowneOkno, &GlownyKonteks) == 1)
        return -1;

    if(UstawianieShaderow(Scena.ZwrocAdresShadera()) == 1)
        return -1;
/*
    if(InicMacierzObserwatora() == 1)
        return -1;

    if(ZmienKsztalt(&GlowneOkno) == 1)
        return -1;
*/
    glDepthFunc(GL_LEQUAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Scena.NowyObiekt(Obiekt1, sizeof(Obiekt1));
    Scena.NowyObiekt(Obiekt2, sizeof(Obiekt2));
//    UstawObjektyBuff(vbo, vao, Lan);

    Scena.ZwrocAdresShadera()->Uzyjprogramu();

    //Petla glowna, obsluga zdarzen{
    char petla = 1;
    SDL_Event zdarzenie;

    while(petla)
    {

        while(SDL_PollEvent(&zdarzenie))
        {
            if(zdarzenie.type == SDL_QUIT)
                petla = 0;

            if(zdarzenie.type == SDL_KEYDOWN)
            {
                switch(zdarzenie.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        petla = 0;
                    break;

                    case SDLK_r:
                    Scena.Rysuj(GlowneOkno);
                    break;

                    default:
                    break;

                }
            }
        }

    }
    //}

    //Czyszczenie {
    Scena.ZwrocAdresShadera()->Sprzatanie();

   // glDisableVertexAttribArray(0);

//    glDeleteBuffers(1, &trbuf);

//	glDeleteBuffers(3, vbo);

//    glDeleteVertexArrays(1, vao);

    SDL_GL_DeleteContext(GlownyKonteks);

    SDL_DestroyWindow(GlowneOkno);

    SDL_Quit();
    //}

    return 0;
}
