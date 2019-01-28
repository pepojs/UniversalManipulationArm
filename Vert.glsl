#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec4 in_Colour;

out Vertex
{
    vec4 Colour;

}Out;

uniform mat4 transformacja;
uniform mat4 rzutowanie;

void main(void)
{
    if(rzutowanie == mat4(0.0f))
    {
        if(transformacja == mat4(0.0f))
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        else
            gl_Position = transformacja * vec4(position.x, position.y, position.z, 1.0);

    }else
    {
        if(transformacja == mat4(0.0f))
            gl_Position = rzutowanie * vec4(position.x, position.y, position.z, 1.0);
        else
            gl_Position = rzutowanie * transformacja * vec4(position.x, position.y, position.z, 1.0);
    }


    Out.Colour = in_Colour;
}

