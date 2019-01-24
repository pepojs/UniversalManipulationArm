#include "Klasa_lancuch.h"

void Lancuch::DodajCzlon(Czlon c)
{
    //Po dodaniu elementu do wektora zminiaja sie adresy co powoduje ze krawdzi wskazuja na pamiec gdzie nie ma wektora
   /* vector <string> L;
    vector <string> P;

    for(unsigned int i = 0; i < LanKine.ZwrocIleWierz(); i++)
    {
        for(unsigned int j = 0; j < LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->IloscKrawedzi(); j++)
        {
            L.push_back(LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->ZwrocKrawedz(j).ZwrocWartWierzL().Nazwa);
            P.push_back(LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->ZwrocKrawedz(j).ZwrocWartWierzP().Nazwa);
        }

    }*/

    LanKine.DodajWierzcholek(c);

   /* for(unsigned int i = 0; i < LanKine.ZwrocIleWierz()-1; i++)
    {
        for(unsigned int j = 0; j < LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->IloscKrawedzi(); j++)
        {
            LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->ZwrocKrawedz(j).ZmienWskWierzL(LanKine.ZwrocWskWierz(ZwrocZawCzlonu(L[j])));
            LanKine.ZwrocWskWierz(LanKine.ZwrocZawWierz(i))->ZwrocKrawedz(j).ZmienWskWierzP(LanKine.ZwrocWskWierz(ZwrocZawCzlonu(P[j])));
        }

    }*/

}

void Lancuch::DodajCzlon(string Nazwa, int IlePunktow,
                    GLvoid* Punkty, GLvoid* PrzePunkty, GLfloat A[16], GLfloat Skala[16])
{
     Czlon c;
     c.Nazwa = Nazwa;
     c.IleWspol = 3;
     c.IlePunktow = IlePunktow;
     c.PrzePunkty = PrzePunkty;
     c.Punkty = Punkty;


     for(int i = 0; i < 16; i++)
     {
         c.Skala[i] = Skala[i];
         c.A[i] = A[i];
     }

     LanKine.DodajWierzcholek(c);
}

 void Lancuch::DodajJoint(Joint j, string czlon1, string czlon2)
 {
     if(LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon1)) == NULL)
     {
         cout<<"Czlon o nazwaie : "<<czlon1<<" nie istnieje !"<<endl;
         return;
     }

     if(LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon2)) == NULL)
     {
         cout<<"Czlon o nazwaie : "<<czlon2<<" nie istnieje !"<<endl;
         return;
     }

     LanKine.DodajKrawedz(j, LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon1)), LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon2)));

     j.art = KA_ODWROTNY;
     LanKine.DodajKrawedz(j, LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon2)), LanKine.ZwrocWskWierz(ZwrocZawCzlonu(czlon1)));

 }

Czlon Lancuch::ZwrocZawCzlonu(string czlon)
{
    for(unsigned int i = 0; i < LanKine.ZwrocIleWierz(); i++)
    {
        if(LanKine.ZwrocZawWierz(i).Nazwa == czlon)
            return LanKine.ZwrocZawWierz(i);
    }

    cout<<"Nie ma czlonu o nazwie : "<<czlon<<endl;

    Czlon c;
    return c;
}

Joint Lancuch::ZwrocZawJoint(string joint)
{
    for(unsigned int i = 0; i < LanKine.ZwrocIleKraw(); i++)
    {
        if(LanKine.ZwrocZawKraw(i).Nazwa == joint)
            return LanKine.ZwrocZawKraw(i);
    }

    cout<<"Nie ma joint-a o nazwie : "<<joint<<endl;

    Joint j;
    return j;
}

void Lancuch::UstawMacierzF(string joint, GLfloat NF[16])
{
    unsigned int i;
    Joint j;

    for(i = 0; i < LanKine.ZwrocIleKraw(); i++)
    {
        if(LanKine.ZwrocZawKraw(i).Nazwa == joint)
            break;
    }

    j = LanKine.ZwrocZawKraw(i);

    for(int k = 0; k < 16; k++) j.F[k] = NF[k];
    M4x4Inwertf(j.B, j.F);

    LanKine.ZmienDaneKraw(i, j);
    LanKine.ZmienDaneKraw(i+1, j);

}

void Lancuch::UstawMacierzB(string joint, GLfloat NB[16])
{
    unsigned int i;
    Joint j;

    for(i = 0; i < LanKine.ZwrocIleKraw(); i++)
    {
        if(LanKine.ZwrocZawKraw(i).Nazwa == joint)
            break;
    }

    j = LanKine.ZwrocZawKraw(i);

    for(int k = 0; k < 16; k++) j.B[k] = NB[k];
    M4x4Inwertf(j.F, j.B);

    LanKine.ZmienDaneKraw(i, j);
    LanKine.ZmienDaneKraw(i+1, j);

}

void Lancuch::ObliczMacierzR(string joint, GLfloat* NowyParametr, int IleParametrow)
{
    unsigned int i;
    Joint j;

    for(i = 0; i < LanKine.ZwrocIleKraw(); i++)
    {
        if(LanKine.ZwrocZawKraw(i).Nazwa == joint)
            break;
    }

    j = LanKine.ZwrocZawKraw(i);

    switch(j.art)
    {
        case KA_OBROT_OS_X:
            if(IleParametrow == 1)
            {
                M4x4ObrotXf(j.R, NowyParametr[0]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4ObrotXf(j.R, -NowyParametr[0]);
                LanKine.ZmienDaneKraw(i+1, j);
            }
        break;

        case KA_OBROT_OS_Y:
            if(IleParametrow == 1)
            {
                M4x4ObrotYf(j.R, NowyParametr[0]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4ObrotYf(j.R, -NowyParametr[0]);
                LanKine.ZmienDaneKraw(i+1, j);
            }
        break;

        case KA_OBROT_OS_Z:
            if(IleParametrow == 1)
            {
                M4x4ObrotZf(j.R, NowyParametr[0]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4ObrotZf(j.R, -NowyParametr[0]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_OBROT_OS_V:
            if(IleParametrow == 4)
            {
                M4x4ObrotVf(j.R, NowyParametr[0], NowyParametr[1], NowyParametr[2], NowyParametr[3]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4ObrotVf(j.R, NowyParametr[0], NowyParametr[1], NowyParametr[2], -NowyParametr[3]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_PRZE_OS_X:
            if(IleParametrow == 1)
            {
                M4x4Translacjaf(j.R, NowyParametr[0], 0.0, 0.0);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Translacjaf(j.R, -NowyParametr[0], 0.0, 0.0);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_PRZE_OS_Y:
            if(IleParametrow == 1)
            {
                M4x4Translacjaf(j.R, 0.0, NowyParametr[0], 0.0);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Translacjaf(j.R, 0.0, -NowyParametr[0], 0.0);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_PRZE_OS_Z:
            if(IleParametrow == 1)
            {
                M4x4Translacjaf(j.R, 0.0, 0.0, NowyParametr[0]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Translacjaf(j.R, 0.0, 0.0, -NowyParametr[0]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_PRZE_OS_XYZ:
            if(IleParametrow == 3)
            {
                M4x4Translacjaf(j.R, NowyParametr[0], NowyParametr[1], NowyParametr[2]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Translacjaf(j.R, -NowyParametr[0], -NowyParametr[1], -NowyParametr[2]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_SCAL_OS_X:
            if(IleParametrow == 1)
            {
                M4x4Skalujf(j.R, NowyParametr[0], 1.0, 1.0);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Skalujf(j.R, -NowyParametr[0], 1.0, 1.0);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_SCAL_OS_Y:
            if(IleParametrow == 1)
            {
                M4x4Skalujf(j.R, 1.0, NowyParametr[0], 1.0);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Skalujf(j.R, 1.0, -NowyParametr[0], 1.0);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_SCAL_OS_Z:
            if(IleParametrow == 1)
            {
                M4x4Skalujf(j.R, 1.0, 1.0, NowyParametr[0]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Skalujf(j.R, 1.0, 1.0, -NowyParametr[0]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_SCAL_OS_XYZ:
            if(IleParametrow == 3)
            {
                M4x4Skalujf(j.R, NowyParametr[0], NowyParametr[1], NowyParametr[2]);
                LanKine.ZmienDaneKraw(i, j);
                M4x4Skalujf(j.R, -NowyParametr[0], -NowyParametr[1], -NowyParametr[2]);
                LanKine.ZmienDaneKraw(i+1, j);
            }

        break;

        case KA_ODWROTNY:
        break;

        default:
        M4x4Jednof(j.R);
        LanKine.ZmienDaneKraw(i, j);
        LanKine.ZmienDaneKraw(i+1, j);
        break;
    }
}

void Lancuch::ObliczMacierzA(string czlonPoczatkowy, string czlonKoncowy)
{
    Czlon cp, ck;
    Joint tempJ;
    vector <Czlon> ListaCzlonow;
    GLfloat m1[16];
    GLfloat m[16];
    GLfloat *mp;
    unsigned int i, j;
    int k, l;

    cp = ZwrocZawCzlonu(czlonPoczatkowy);
    ck = ZwrocZawCzlonu(czlonKoncowy);

    ListaCzlonow = LanKine.DFS(cp, ck);

    for(k = 0; k < 16; k++)m[k] = ListaCzlonow[0].A[k];

    for(i = 1; i < ListaCzlonow.size(); i++)
    {
        for(j = 0; j < LanKine.ZwrocIleKraw(); j++)
        {
            if(LanKine.ZwrocKraw(j).ZwrocWartWierzL() == ListaCzlonow[i-1]
               &&  LanKine.ZwrocKraw(j).ZwrocWartWierzP() == ListaCzlonow[i])
            {
                tempJ = LanKine.ZwrocZawKraw(j);

            }
        }

        M4x4Mnozenief(m1, m, tempJ.F);
        M4x4Mnozenief(m, m1, tempJ.R);
        M4x4Mnozenief(m1, m, tempJ.B);
        M4x4Mnozenief(m, m1, ListaCzlonow[i].Skala);


        for(k = 0; k < 16; k++)ListaCzlonow[i].A[k] = m[k];

        //Najprawdopodobniej to jest zle, ale nie mam jak na razie sprawdzic !!!!!!!!!!!
        if(ListaCzlonow[i].PrzePunkty != NULL)
        {
            if(ListaCzlonow[i].IleWspol == 3)
            {
                for(l = 0; l < ListaCzlonow[i].IlePunktow; l++)
                    M4x4MnozenieMP3f((GLfloat*)ListaCzlonow[i].PrzePunkty, ListaCzlonow[i].A, (GLfloat*)ListaCzlonow[i].Punkty);

            }else if(ListaCzlonow[i].IleWspol == 4)
            {
                for(l = 0; l < ListaCzlonow[i].IlePunktow; l++)
                    M4x4MnozenieMP4f((GLfloat*)ListaCzlonow[i].PrzePunkty, ListaCzlonow[i].A, (GLfloat*)ListaCzlonow[i].Punkty);
            }
        }
        //Do tego miejsca moze byc zle

        LanKine.ZmienDaneWierz(ZwrocZawCzlonu(ListaCzlonow[i].Nazwa), ListaCzlonow[i]);



    }


}
