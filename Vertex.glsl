#version 330

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Colour;

out Vertex
{
    vec4 Colour;

}Out;

uniform TransBlock
{
    mat4 mm;
    mat4 vm;
    mat4 pm;

}trb;

void main(void)
{
    gl_Position = trb.pm * (trb.vm * (trb.mm * in_Position));
    Out.Colour = in_Colour;
}
