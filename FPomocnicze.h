#ifndef FPOMOCNICZE_H
#define FPOMOCNICZE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>

#define GLEW_STATIC
#include <glew.h>


#define INDEX(i,j) ((i)+4*(j))

void GLVersia (void);

uint8_t SprawdzGLError();

//Macierz jednostkowa (po przekontnej 1, reszta 0)
void M4x4Jednof(GLfloat m[16]);

void M4x4Translacjaf(GLfloat m[16], float x, float y, float z);

void M4x4Skalujf(GLfloat m[16], float sx, float sy, float sz);

void M4x4ObrotXf(GLfloat m[16], float alfa);

void M4x4ObrotYf(GLfloat m[16], float alfa);

void M4x4ObrotZf(GLfloat m[16], float alfa);

void M4x4ObrotVf(GLfloat m[16], float x, float y, float z, float alfa);

void M4x4Mnozenief(GLfloat m12[16], const GLfloat m1[16], const GLfloat m2[16]);

void M4x4MnozenieMV4f(GLfloat mv[4], const GLfloat m[16], const GLfloat v[4]);

void M4x4MnozenieMTV4f(GLfloat mv[4], const GLfloat m[16], const GLfloat v[4]);

void M4x4MnozenieMV3f(GLfloat mv[3], const GLfloat m[16], const GLfloat v[3]);

void M4x4MnozenieMP4f(GLfloat mp[4], const GLfloat m[16], const GLfloat p[4]);

void M4x4MnozenieMP3f(GLfloat mp[3], const GLfloat m[16], const GLfloat p[3]);

GLfloat V3IloczynSka(const GLfloat v1[3], const GLfloat v2[3]);

void V3IloczynWek(GLfloat v12[3], const GLfloat v1[3], const GLfloat v2[3]);

void M4x4OstScietyf(GLfloat m[16], GLfloat modw[16], float lewa, float prawa,
                    float dol, float gora, float przod, float tyl);

void M4x4Prostof(GLfloat m[16], GLfloat modw[16], float lewa, float prawa,
                 float dol, float gora, float przod, float tyl);

void V3ZlozObrot(GLfloat v[3], GLfloat *alfa,
                  const GLfloat v1[3], GLfloat alfa1,
                  const GLfloat v2[3], GLfloat alfa2);

uint8_t M4x4RozkCzynTrojkatne(GLfloat lu[16], int p[3], const GLfloat m[16]);

void M4x4RozUkladLin(GLfloat aiv[4], const GLfloat lu[16], const int p[3], const GLfloat v[4]);

uint8_t M4x4Inwertf(GLfloat mi[16], const GLfloat m[16]);

#endif
