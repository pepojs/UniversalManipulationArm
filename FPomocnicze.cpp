#include "FPomocnicze.h"


void GLVersia (void)
{
    std::cout<<"OpenGL "<<glGetString(GL_VERSION)<<", GLSL "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}

uint8_t SprawdzGLError()
{
    GLenum err;

    if((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr<<"Wystapil blad : "<<err<<" "<<gluErrorString(err)<<std::endl;
        return 1;
    }

    return 0;
}

//Macierz jednostkowa (po przekontnej 1, reszta 0)
void M4x4Jednof(GLfloat m[16])
{
    for(int i = 0; i < 16; i++)
        m[i] = 0;

    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void M4x4Translacjaf(GLfloat m[16], float x, float y, float z)
{
    M4x4Jednof(m);
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

void M4x4Skalujf(GLfloat m[16], float sx, float sy, float sz)
{
    M4x4Jednof(m);
    m[0] = sx;
    m[5] = sy;
    m[10] = sz;
}

void M4x4ObrotXf(GLfloat m[16], float alfa)
{
    M4x4Jednof(m);
    m[5] = m[10] = cos(alfa);
    m[6] = sin(alfa);
    m[9] = -m[6];
}

void M4x4ObrotYf(GLfloat m[16], float alfa)
{
    M4x4Jednof(m);
    m[0] = m[10] = cos(alfa);
    m[8] = sin(alfa);
    m[2] = -m[8];
}

void M4x4ObrotZf(GLfloat m[16], float alfa)
{
    M4x4Jednof(m);
    m[0] = m[5] = cos(alfa);
    m[1] = sin(alfa);
    m[4] = -m[1];
}

void M4x4ObrotVf(GLfloat m[16], float x, float y, float z, float alfa)
{
    float l,c1;

    M4x4Jednof(m);
    l = 1.0/sqrt(x*x+y*y+z*z);
    x *= l;
    y *= l;
    z *= l;

    c1 = 1.0 - cos(alfa);
    m[0] = x*x*c1 + cos(alfa);
    m[1] = m[4] = x*y*c1;
    m[5] = y*y*c1 + cos(alfa);
    m[2] = m[8] = x*z*c1;
    m[6] = m[9] = y*z*c1;
    m[10] = z*z*c1 + cos(alfa);
    m[6] += sin(alfa)*x;
    m[2] -= sin(alfa)*y;
    m[1] += sin(alfa)*z;
    m[9] -= sin(alfa)*x;
    m[8] += sin(alfa)*y;
    m[4] -= sin(alfa)*z;
}

void M4x4Mnozenief(GLfloat m12[16], const GLfloat m1[16], const GLfloat m2[16])
{
    for(int i = 0; i < 4;i++)
        for(int j = 0; j < 4; j++)
        {
            m12[INDEX(i,j)] = m1[INDEX(i,0)] * m2[INDEX(0,j)];
            for(int k = 1; k < 4; k++)
                m12[INDEX(i,j)] += m1[INDEX(i,k)] * m2[INDEX(k,j)];
        }
}

void M4x4MnozenieMV4f(GLfloat mv[4], const GLfloat m[16], const GLfloat v[4])
{
    for(int i = 0; i < 4;i++)
    {
        mv[i] = m[INDEX(i,0)]*v[0];
        for(int j = 1; j < 4; j++)
            mv[i] += m[INDEX(i,j)]*v[j];
    }

}

void M4x4MnozenieMTV4f(GLfloat mv[4], const GLfloat m[16], const GLfloat v[4])
{
    for(int i = 0; i < 4;i++)
    {
        mv[i] = m[INDEX(0,i)]*v[0];
        for(int j = 1; j < 4; j++)
            mv[i] += m[INDEX(j,i)]*v[j];
    }
}

void M4x4MnozenieMV3f(GLfloat mv[3], const GLfloat m[16], const GLfloat v[3])
{
    for(int i = 0; i < 3;i++)
    {
        mv[i] = m[INDEX(i,0)]*v[0];
        for(int j = 1; j < 3; j++)
            mv[i] += m[INDEX(i,j)]*v[j];
    }
}

void M4x4MnozenieMP4f(GLfloat mp[4], const GLfloat m[16], const GLfloat p[4])
{
    for(int i = 0; i < 4;i++)
    {
        mp[i] = m[INDEX(i,3)];
        for(int j = 0; j < 4; j++)
            mp[i] += m[INDEX(i,j)]*p[j];
    }
}

void M4x4MnozenieMP3f(GLfloat mp[3], const GLfloat m[16], const GLfloat p[3])
{
    for(int i = 0; i < 3;i++)
    {
        mp[i] = m[INDEX(i,3)];
        for(int j = 0; j < 3; j++)
            mp[i] += m[INDEX(i,j)]*p[j];
    }
}

GLfloat V3IloczynSka(const GLfloat v1[3], const GLfloat v2[3])
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void V3IloczynWek(GLfloat v12[3], const GLfloat v1[3], const GLfloat v2[3])
{
    v12[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v12[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v12[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void M4x4OstScietyf(GLfloat m[16], GLfloat modw[16], float lewa, float prawa,
                    float dol, float gora, float przod, float tyl)
{
    if(m)
    {
        for(int i = 0; i < 16; i++) m[i] = 0;
        m[0] = (przod + przod)/(prawa - lewa);
        m[5] = (przod + przod)/(gora - dol);
        m[8] = (prawa + lewa)/(prawa - lewa);
        m[9] = (gora + dol)/(gora - dol);
        m[10] = (przod + tyl)/(przod - tyl);
        m[14] = (tyl * (przod + przod))/(przod - tyl);
        m[11] = -1.0;
    }

    if(modw)
    {
        for(int i = 0; i < 16; i++) modw[i] = 0;
        modw[0] = (prawa - lewa)/(przod + przod);
        modw[5] = (gora - dol)/(przod + przod);
        modw[11] = (przod - tyl)/(tyl * (przod + przod));
        modw[12] = (prawa + lewa)/(przod + przod);
        modw[13] = (gora + dol)/(przod + przod);
        modw[14] = -1.0;
        modw[15] = (przod + tyl)/(tyl * (przod + przod));
    }

}

void M4x4Prostof(GLfloat m[16], GLfloat modw[16], float lewa, float prawa,
                 float dol, float gora, float przod, float tyl)
{
    if(m)
    {
        for(int i = 0; i < 16; i++) m[i] = 0;
        m[0] = 2.0/(prawa - lewa);
        m[5] = 2.0/(gora - dol);
        m[10] = 2.0/(przod - tyl);
        m[12] = (lewa + prawa)/(lewa - prawa);
        m[13] = (dol + gora)/(dol - gora);
        m[14] = (przod + tyl)/(przod - tyl);
        m[15] = 1.0;
    }

    if(modw)
    {
        for(int i = 0; i < 16; i++) modw[i] = 0;
        modw[0] = 0.5*(prawa - lewa);
        modw[5] = 0.5*(gora - dol);
        modw[10] = 0.5*(przod - tyl);
        modw[12] = 0.5*(prawa + lewa);
        modw[13] = 0.5*(gora + dol);
        modw[14] = 0.5*(tyl + przod);
        modw[15] = 1.0;
    }

}

void V3ZlozObrot(GLfloat v[3], GLfloat *alfa,
                  const GLfloat v1[3], GLfloat alfa1,
                  const GLfloat v2[3], GLfloat alfa2)
{
    float s, s1, s2, c1, c2, s2c1, s1c2, s2s1, v2v1, v2xv1[3];

    s1 = sin(0.5 * alfa1); c1 = cos(0.5 * alfa2);
    s2 = sin(0.5 * alfa2); c2 = cos(0.5 * alfa2);

    s2c1 = s2*c1; s1c2 = s1*c2; s2s1 = s2 * s1;
    v2v1 = V3IloczynSka(v2, v1);
    V3IloczynWek(v2xv1, v2, v1);

    v[0] = v2[0]*s2c1 + v1[0]*s1c2 + v2xv1[0]*s2s1;
    v[1] = v2[1]*s2c1 + v1[1]*s1c2 + v2xv1[1]*s2s1;
    v[2] = v2[2]*s2c1 + v1[2]*s1c2 + v2xv1[2]*s2s1;

    s = sqrt(V3IloczynSka(v, v));
    if(s > 0.0)
    {
        v[0] /= s;
        v[1] /= s;
        v[2] /= s;
        *alfa = 2.0*atan2(s, (c2*c1 - v2v1*s2s1));

    }else
    {
        v[0] = 1.0;
        v[1] = v[2] = *alfa = 0.0;
    }
}

uint8_t M4x4RozkCzynTrojkatne(GLfloat lu[16], int p[3], const GLfloat m[16])
{
    GLfloat d;
    int i, j, k;

    for(i = 0; i < 16; i++) lu[i] = m[i];
    for(i = 0; i < 3; i++) p[i] = 0;

    for(j = 0; j < 3; j++)
    {
        d = fabs( lu[INDEX(j,j)]);
        p[j] = j;

        for(i = j+1; i < 4; i++)
        {
            if(fabs(lu[INDEX(i,j)]) > d)
            {
                d = fabs(lu[INDEX(i,j)]);
                p[j] = i;
            }
        }

        if(d == 0.0) return 0;
        if(p[j] != j)
        {
            i = p[j];
            for(k = 0; k < 4; k++)
            {
                d = lu[INDEX(i,k)];
                lu[INDEX(i,k)] = lu[INDEX(j,k)];
                lu[INDEX(j,k)] = d;
            }
        }

        for(i = j+1; i < 4; i++)
        {
            d = lu[INDEX(i,j)] /= lu[INDEX(j,j)];
            for(k = j+1; k < 4; k++)
            {
                lu[INDEX(i,k)] -= d*lu[INDEX(j,k)];
            }
        }
    }

    return lu[15] != 0.0;
}

void M4x4RozUkladLin(GLfloat aiv[4], const GLfloat lu[16], const int p[3], const GLfloat v[4])
{
    GLfloat d;
    int i, j;

    for(i = 0; i < 4; i++)aiv[i] = v[i];

    for(i = 0; i < 3; i++)
    {
        if(p[i] != i)
        {
            d = aiv[i];
            aiv[i] = aiv[p[i]];
            aiv[p[i]] = d;
        }
    }


    for(i = 1; i < 4; i++)
        for(j = 0; j < i; j++)
            aiv[i] -= lu[INDEX(i,j)] * aiv[j];


    for(i = 3; i >= 0; i--)
    {
        for(j = i+1; j < 4; j++)
            aiv[i] -= lu[INDEX(i,j)]*aiv[j];

        aiv[i] /= lu[INDEX(i,i)];
    }
}

uint8_t M4x4Inwertf(GLfloat mi[16], const GLfloat m[16])
{
    int i, j, p[3];
    GLfloat lu[16], e[4];

    if(!M4x4RozkCzynTrojkatne(lu, p, m))
        return 0;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)e[j] = 0;
        e[i] = 1.0;
        M4x4RozUkladLin(&mi[4*i], lu, p, e);
    }

    return 1;
}
