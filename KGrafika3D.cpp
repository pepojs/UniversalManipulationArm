#include "KGrafika3D.h"

Grafika3D::~Grafika3D()
{
    //Odlacza atrybuty dla vertex shader
    glDisableVertexAttribArray(0);

    //Usuwa vbo i vao
    glDeleteBuffers(vbo.size(), &vbo[0]);
    glDeleteVertexArrays(vao.size(), &vao[0]);
}

//Metoda tworzy nowy obiekt rysowany statycznie, pierwszy argument to zbior puktow tego opiektu,
//drugi argument to ilosc wspolrzednych opisujacych punkt, zwraca vao obiektu
GLuint Grafika3D::TworzObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu)
{
    vao.push_back(0); //Nowa tablica obiektu (mozna w niej umiescic bufor z punktami, kolore itp.)
    vbo.push_back(0); //Nowy bufor obiektu dla punktow obiektu

    //Tworzy nowy voa i ustawia na aktywna
    glGenVertexArrays(1, &vao[vao.size()-1]);
    glBindVertexArray(vao[vao.size()-1]);

    //Tworzy nowy bufor, ustawia na aktywny i umieszcza dane z punktami
    glGenBuffers(1, &vbo[vbo.size()-1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo.size()-1]);
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicyPunktow, TablicaPunktow, GL_STATIC_DRAW);

    //Ustawia atrybut dla vertex shader
    if(IloscWspolrzednychPunktu >= 4 || IloscWspolrzednychPunktu == 0)
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    else
        glVertexAttribPointer(0, IloscWspolrzednychPunktu, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    //Dezaktywuje voa
    glBindVertexArray(0);

    return vao[vao.size()-1];
}

//Metoda tworzy nowy obiekt rysowany statycznie oraz okresla jego kolor,
//pierwszy argument to zbior puktow tego obiektu, drugi argument to ilosc wspolrzednych opisujacych punkt,
//trzeci argument to tablica z kolorami odpowiednich punktow, czwarty ilosc elementow w wektorze
//opisujacym kolor (np. RGB i Alpha), zwraca vao obiektu
GLuint Grafika3D::TworzObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu,
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
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicyPunktow, TablicaPunktow, GL_STATIC_DRAW);

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

    return vao[vao.size()-1];
}

//Metoda tworzy nowy obiekt rysowany statycznie oraz okresla jego kolor,
//pierwszy argument to tablica zepunktami, kolorami, i rozmieszczeniem tekstur, drugi argument to ilosc wspolrzednych opisujacych punkt,
//trzeci to ilosc wspolrzednych opisujacych kolor (np. RGB i Alpha), czwarty to ilosc wspolrzednych tekstur, zwraca vao obiektu
GLuint Grafika3D::TworzObiekt(GLvoid* WspolnaTablica, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu, uint8_t IloscWspolrzednychKoloru, uint8_t IloscWspolrzednychTekstury)
{
    //Ilosc wszystkich danych potrzebnych do opisanie jednego punktu
    int SumaWspolrzednych = IloscWspolrzednychPunktu + IloscWspolrzednychKoloru + IloscWspolrzednychTekstury;

    vao.push_back(0); //Nowa tablica obiektu (mozna w niej umiescic bufor z punktami, kolore itp.)
    vbo.push_back(0); //Nowy bufor obiektu dla punktow obiektu

    //Tworzy nowy voa i ustawia na aktywna
    glGenVertexArrays(1, &vao[vao.size()-1]);
    glBindVertexArray(vao[vao.size()-1]);

    //Tworzy nowy bufor, ustawia na aktywny i umieszcza dane z punktami
    glGenBuffers(1, &vbo[vbo.size()-1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo.size()-1]);
    glBufferData(GL_ARRAY_BUFFER, RozmiarTablicy, WspolnaTablica, GL_STATIC_DRAW);


    //Ustawia atrybuty dla vertex shader
    //Punkty
    if(IloscWspolrzednychPunktu != 0)
    {
        if(IloscWspolrzednychPunktu >= 4)// || IloscWspolrzednychPunktu == 0)
        {
            IloscWspolrzednychPunktu = 4;
            glVertexAttribPointer(0, IloscWspolrzednychPunktu, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat), 0);

        }else
            glVertexAttribPointer(0, IloscWspolrzednychPunktu, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat), 0);

        glEnableVertexAttribArray(0);
    }


    //Kolor
    if(IloscWspolrzednychKoloru != 0)
    {
        if(IloscWspolrzednychKoloru >= 4)
        {
            IloscWspolrzednychKoloru = 4;
            glVertexAttribPointer(1, IloscWspolrzednychKoloru, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat)*sizeof(GLfloat), (GLvoid*)(IloscWspolrzednychPunktu * sizeof(GLfloat)));

        }else
            glVertexAttribPointer(1, IloscWspolrzednychKoloru, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat)*sizeof(GLfloat), (GLvoid*)(IloscWspolrzednychPunktu * sizeof(GLfloat)));

        glEnableVertexAttribArray(1);
    }


    //Tekstura
    if(IloscWspolrzednychTekstury != 0)
    {
        if(IloscWspolrzednychTekstury >= 3)// || IloscWspolrzednychTekstury == 0)
        {
            IloscWspolrzednychTekstury = 3;
            glVertexAttribPointer(2, IloscWspolrzednychTekstury, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat), (GLvoid*)((IloscWspolrzednychPunktu + IloscWspolrzednychKoloru) * sizeof(GLfloat)));

        }else
            glVertexAttribPointer(2, IloscWspolrzednychTekstury, GL_FLOAT, GL_FALSE, SumaWspolrzednych*sizeof(GLfloat), (GLvoid*)((IloscWspolrzednychPunktu + IloscWspolrzednychKoloru) * sizeof(GLfloat)));

        glEnableVertexAttribArray(2);
    }


    //Dezaktywuje voa
    glBindVertexArray(0);

    return vao[vao.size()-1];
}


//Metoda dodaje nowy obiekt do sceny, bedzie on teraz wyswietlany, jako argumet podajemy
//vao obiektu ktory chcemy dodac oraz liczbe punktow z ktorych sklada sie nasz obiekt
//(potrzebne w procesie rysowania obiektu), metoda zwraca identyfikator obiektu na scenie
GLuint Grafika3D::DodajObiektDoSceny(GLuint vaoObiektu, GLuint IloscPunktowWObiekcie)
{
    ObiektNaScenie NowyObiekt;
    glm::mat4 Transformacja = glm::mat4(1.0f);
    GLuint IDNowegoObiektu;

    //Jezeli istnieje jakis obiekt na scenie to nastepny obiekt dostanie numer ID o 1 wiekszy
    if(ObiektyNaScenie.empty())
        IDNowegoObiektu = 0;
    else
        IDNowegoObiektu = ObiektyNaScenie[ObiektyNaScenie.size()-1].IDObiektu + 1;

    NowyObiekt.IDObiektu = IDNowegoObiektu;
    NowyObiekt.IDvaoObiektu = vaoObiektu;
    NowyObiekt.MacierzTransformacji = Transformacja;
    NowyObiekt.IloscPunktow = IloscPunktowWObiekcie;
    NowyObiekt.Tekstury.clear();

    ObiektyNaScenie.push_back(NowyObiekt); //Dodaje nowy obiekt do sceny

    return IDNowegoObiektu; //Zwraca ID nowego obiektu
}

//Metoda usuwa obiekt ze sceny, argument jaki przyjmuje to identyfikator obiektu do usuniecia
void Grafika3D::UsunObiektZeSceny(GLuint IDObiektu)
{
    //Petla przeszukuje vektor aby znalezc wskaznik na obiekt do usuniecia, jezeli sie nie uda wyswietla komunikat
    for(vector<ObiektNaScenie>::iterator i = ObiektyNaScenie.begin(); i != ObiektyNaScenie.end(); i++)
    {
        if(i->IDObiektu == IDObiektu)
        {
            ObiektyNaScenie.erase(i);
            return;
        }
    }

    cerr<<"Na scenie nie istnieje obiekt o ID: "<<IDObiektu<<" . Nie mozna wiec go usunac"<<endl;
}


//Metoda kopiujaca obiekt na scenie, argumentem jest identyfikator obiektu, zwraca
//identyfikator nowego obiektu
GLuint Grafika3D::KopiujObiekt(GLuint IDObiektu)
{
    ObiektNaScenie NowyObiekt;

    for(size_t i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
        {
            NowyObiekt.IDObiektu = ObiektyNaScenie[ObiektyNaScenie.size()-1].IDObiektu + 1;
            NowyObiekt.IDvaoObiektu = ObiektyNaScenie[i].IDvaoObiektu;
            NowyObiekt.MacierzTransformacji = ObiektyNaScenie[i].MacierzTransformacji;
            NowyObiekt.IloscPunktow = ObiektyNaScenie[i].IloscPunktow;
            NowyObiekt.Tekstury.assign(ObiektyNaScenie[i].Tekstury.begin(), ObiektyNaScenie[i].Tekstury.end());

            ObiektyNaScenie.push_back(NowyObiekt);
            return NowyObiekt.IDObiektu;
        }
    }

    cerr<<"Nie istnieje obiekt o ID: "<<IDObiektu<<endl;
}

//Metoda pozwala dodac obiekt na scene bez koniecznosci wywolywania kolejnych metod,
//pierwszy argument to zbior puktow tego opiektu, drugi argument to ilosc wspolrzednych opisujacych punkt,
//trzeci liczbe punktow z ktorych sklada sie nasz obiekt (potrzebne w procesie rysowania obiektu),
//zwraca identyfikator obiektu. Aby dodawac kolejne takie same obiekty nalezy kopiowac pierwszy utworzony
GLuint Grafika3D::DodajObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu, GLuint IloscPunktowWObiekcie)
{
    GLuint vao = TworzObiekt(TablicaPunktow, RozmiarTablicyPunktow, IloscWspolrzednychPunktu);
    return DodajObiektDoSceny(vao, IloscPunktowWObiekcie);
}

//Metoda pozwala dodac obiekt na scene bez koniecznosci wywolywania kolejnych metod,
//pierwszy argument to zbior puktow tego opiektu, drugi argument to ilosc wspolrzednych opisujacych punkt,
//trzeci argument to tablica zawierajaca kolory odpowiednich punktu, czwart ilosc elementow w wektorze opisujacym kolor (np. RGB i Alpha),
//piaty liczbe punktow z ktorych sklada sie nasz obiekt (potrzebne w procesie rysowania obiektu), zwraca identyfikator obiektu.
//Aby dodawac kolejne takie same obiekty nalezy kopiowac pierwszy utworzony
GLuint Grafika3D::DodajObiekt(GLvoid* TablicaPunktow, size_t RozmiarTablicyPunktow, uint8_t IloscWspolrzednychPunktu, GLvoid* TablicaKolorow,
                                size_t RozmiarTablicyKolorow, uint8_t IloscWspolrzednychKoloru, GLuint IloscPunktowWObiekcie)
{
    GLuint vao = TworzObiekt(TablicaPunktow, RozmiarTablicyPunktow, IloscWspolrzednychPunktu, TablicaKolorow, RozmiarTablicyKolorow, IloscWspolrzednychKoloru);
    return DodajObiektDoSceny(vao, IloscPunktowWObiekcie);
}

//Metoda pozwala dodac obiekt na scene bez koniecznosci wywolywania kolejnych metod,
//Pierwszy argument to tablica zawierajaca wspolne dane punktow, koloru i tekstur, drugi to ilosc wspolrzednych opisujacych punkt,
//trzeci ilosc elementow w wektorze opisujacym kolor (np. RGB i Alpha), czwarty to ilosc wspolrzednych dla tektury
//piaty liczbe punktow z ktorych sklada sie nasz obiekt (potrzebne w procesie rysowania obiektu), zwraca identyfikator obiektu.
//Aby dodawac kolejne takie same obiekty nalezy kopiowac pierwszy utworzony
 GLuint Grafika3D::DodajObiekt(GLvoid* WspolnaTablica, size_t RozmiarTablicy, uint8_t IloscWspolrzednychPunktu, uint8_t IloscWspolrzednychKoloru,
                       uint8_t IloscWspolrzednychTekstury, GLuint IloscPunktowWObiekcie)
{
    GLuint vao = TworzObiekt(WspolnaTablica, RozmiarTablicy, IloscWspolrzednychPunktu, IloscWspolrzednychKoloru, IloscWspolrzednychTekstury);
    return DodajObiektDoSceny(vao, IloscPunktowWObiekcie);
}

//Metoda pozwalajaca przesunac obiekt o wektor, pierwszy argument to identyfikator obiektu na scenie,
//drugi argument to wektor przesuniecia
void Grafika3D::PrzesunObiekt(GLuint IDObiektu, glm::vec3 Przesuniecie)
{
    //Szukanie numeru obiektu o podanym ID
    size_t i;
    for(i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
            break;
    }

    //Jezeli nie znaleziono obiektu to wyswietlany jest odpowiedni komunikat
    if(i == ObiektyNaScenie.size())
    {
        cerr<<"Na scenie nie ma obiektu o ID: "<<IDObiektu<<endl;
        return;
    }


    //Do macierzy transformacji obiektu dodawany jest wektor przesuniecia
    ObiektyNaScenie[i].MacierzTransformacji = glm::translate(ObiektyNaScenie[i].MacierzTransformacji, Przesuniecie);

}

//Metoda pozwalajaca obrucic obiekt, pierwszy argument to identyfikator obiektu, drugi to kat obrotu,
//trzeci argument to os obrotu obiektu
void Grafika3D::ObrocObiekt(GLuint IDObiektu, GLfloat KatObrotu, glm::vec3 OsObrotu)
{
    //Szukanie numeru obiektu o podanym ID
    size_t i;
    for(i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
            break;
    }

    //Jezeli nie znaleziono obiektu to wyswietlany jest odpowiedni komunikat
    if(i == ObiektyNaScenie.size())
    {
        cerr<<"Na scenie nie ma obiektu o ID: "<<IDObiektu<<endl;
        return;
    }

    //Dodawanie obrotu do macierzy transformacji
    ObiektyNaScenie[i].MacierzTransformacji = glm::rotate(ObiektyNaScenie[i].MacierzTransformacji, KatObrotu, OsObrotu);
}

//Metoda pozwalajaca przeskalowac obiekt, pierwszy argument to identyfikator obiektu, drugi to wektor
//z kolejnymi wartoscimai skali wzdluz kolejnych osi
void Grafika3D::PrzeskalujObiekt(GLuint IDObiektu, glm::vec3 WektorSkali)
{
    //Szukanie numeru obiektu o podanym ID
    size_t i;
    for(i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
            break;
    }

    //Jezeli nie znaleziono obiektu to wyswietlany jest odpowiedni komunikat
    if(i == ObiektyNaScenie.size())
    {
        cerr<<"Na scenie nie ma obiektu o ID: "<<IDObiektu<<endl;
        return;
    }

    //Skaluje obiekt modyfikujac macierz transformacji
    ObiektyNaScenie[i].MacierzTransformacji = glm::scale(ObiektyNaScenie[i].MacierzTransformacji, WektorSkali);
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

//Ustawia kamere na scenie, pierwszy parametr to wspolrzedne globalne kamery na scenie,
//drugi to punkt, na ktory "patrzy" kamera, trzeci to kierunek osi Z kamery
void Grafika3D::UstawKamere(glm::vec3 Pozycja, glm::vec3 Cel, glm::vec3 OsZ)
{
    glm::mat4 widok;

    PozycjaKamery = Pozycja;
    CelKamery = Cel;
    OsZKamery = OsZ;

    widok = glm::lookAt(Pozycja, Cel, OsZ); //Tworzy macierz pozwalajaca przeksztalcic scene z przeszczeni globalnej do przestrzeni widoku

    shader.PrzekazMacierz4x4("widok", widok);
}

//Metoda pozwala wczytac obraz i stworzyc z niego teksture 2D, pierwszy argument to scierzka do obrazu,
//drugi to sposob "zawijania" tekstur na brzegach, trzeci to sposob filtracji tekstury by okreslic kolor piksela,
//zwraca identyfikator tekstury
GLuint Grafika3D::GenerujTeksture2D(const char* NazwaObrazka, GLint ZawijanieTekstury, GLint FiltracjaTekstury)
{
    GLuint NowaTekstura;
    int szerokosc, wysokosc;

    //generuje teksture
    glGenTextures(1, &NowaTekstura);
    glBindTexture(GL_TEXTURE_2D, NowaTekstura);

    //Ustawia parametry zawijania tekstury dla osi X(S) i Y(T)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ZawijanieTekstury);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ZawijanieTekstury);

    //Ustawienie parametrow filtru tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FiltracjaTekstury);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FiltracjaTekstury);

    //Wczytanie obrazka, stworzenie z niego tekstury 2D, stworzenie mipmaps i zwolnienie pamieci po obrazku
    unsigned char* Obrazek = SOIL_load_image(NazwaObrazka, &szerokosc, &wysokosc, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, Obrazek);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(Obrazek);

    glBindTexture(GL_TEXTURE_2D, 0);

    return NowaTekstura;

}

//Powduje nalozenie tekstury na obiekt
//Pierwszy argument to identyfikator tekstury, drugi identyfikator obiektu, na ktorego nakladamy teksture
void Grafika3D::DodajTekstureDoObiektu(GLuint IDTekstury, GLuint IDObiektu)
{
    //Szukanie numeru obiektu o podanym ID
    size_t i;
    for(i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
            break;
    }

    //Jezeli nie znaleziono obiektu to wyswietlany jest odpowiedni komunikat
    if(i == ObiektyNaScenie.size())
    {
        cerr<<"Na scenie nie ma obiektu o ID: "<<IDObiektu<<endl;
        return;
    }

    ObiektyNaScenie[i].Tekstury.push_back(IDTekstury);
}

//Metoda sluzaca do usuwania tekstury z obiektu,
//Pierwszy argument to identyfikator tekstury,drugi to identyfikator obiektu, z ktorego usuwamy teksture
void Grafika3D::UsunTekstureZObiektu(GLuint IDTekstury, GLuint IDObiektu)
{
    //Szukanie numeru obiektu o podanym ID
    size_t i;
    for(i = 0; i < ObiektyNaScenie.size(); i++)
    {
        if(IDObiektu == ObiektyNaScenie[i].IDObiektu)
            break;
    }

    //Jezeli nie znaleziono obiektu to wyswietlany jest odpowiedni komunikat
    if(i == ObiektyNaScenie.size())
    {
        cerr<<"Na scenie nie ma obiektu o ID: "<<IDObiektu<<endl;
        return;
    }

    //Petla przeszukuje vektor aby znalezc wskaznik na teksture do usuniecia, jezeli sie nie uda wyswietla komunikat
    for(vector<GLuint>::iterator j = ObiektyNaScenie[i].Tekstury.begin(); j != ObiektyNaScenie[i].Tekstury.end(); j++)
    {
        if(*j == IDTekstury)
        {
            ObiektyNaScenie[i].Tekstury.erase(j);
            return;
        }
    }

    cerr<<"Na scenie nie istnieje obiekt o ID: "<<IDObiektu<<" . Nie mozna wiec go usunac"<<endl;

}

void Grafika3D::Rysuj(SDL_Window* GlowneOkno)
{
    string TeksturyWShader = "Tekstura";
    string Tymczasowy = "";

    glClearColor(0.0, 0.0, 0.0, 1.0); //Ustawia kolor tla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Czysci tlo
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    for(int i = 0; i < ObiektyNaScenie.size(); i++)
    {
        glBindVertexArray(ObiektyNaScenie[i].IDvaoObiektu);
        shader.PrzekazMacierz4x4("transformacja", ObiektyNaScenie[i].MacierzTransformacji);

        //Aktywowanie tekstur
        if(ObiektyNaScenie[i].Tekstury.size() > 0)
        {
            for(int j = 0; j < ObiektyNaScenie[i].Tekstury.size(); j++)
            {
                if(j < GL_MAX_TEXTURE_UNITS - GL_TEXTURE0)
                {
                    glActiveTexture(GL_TEXTURE0 + j); // Aktywuje teksture o odpowiednim numerze

                    //Tworze nazwe zmiennej dla tekstury w shaderze
                    sprintf((char*)Tymczasowy.c_str(), "%d", j);
                    Tymczasowy = TeksturyWShader + Tymczasowy.c_str();;
                    //Przesyla teksture do shadera
                    glBindTexture(GL_TEXTURE_2D, ObiektyNaScenie[i].Tekstury[j]);
                    glUniform1i(glGetUniformLocation(shader.ZwrocProgramID(), Tymczasowy.c_str()), j);

                    Tymczasowy = ""; //Czysci napis tymczasowy

                }else
                {
                    cerr<<"Obiekt o ID: "<<ObiektyNaScenie[i].IDObiektu<<" posiada za duzo tekstur !"<<endl;
                    break;
                }
            }
        }

        //glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_BYTE, 0);
        glDrawArrays(GL_TRIANGLES, 0 ,ObiektyNaScenie[i].IloscPunktow);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }

    glFlush();

    SDL_GL_SwapWindow(GlowneOkno);
}
