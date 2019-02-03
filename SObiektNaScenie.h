#ifndef SOBIEKTNASCENIE_H
#define SOBIEKTNASCENIE_H

#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

struct ObiektNaScenie
{
    GLuint IDObiektu;
    GLuint IDvaoObiektu;
    glm::mat4 MacierzTransformacji;
    GLuint IloscPunktow;
    vector<GLuint> Tekstury;
};



#endif // SOBIEKTNASCENIE_H
