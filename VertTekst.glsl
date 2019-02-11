#version 330

layout(location=0) in vec4 in_Vertex;

out Vertex
{
    vec2 TexturCoord;

}Out;

uniform mat4 rzutowanie;


void main(void)
{
    if(rzutowanie == mat4(0.0f))
        gl_Position = vec4(in_Vertex.xy, 0.0, 1.0);
    else
        gl_Position = rzutowanie * vec4(in_Vertex.xy, 0.0, 1.0);


    Out.TexturCoord = in_Vertex.zw;
}


