#version 330

in Vertex
{
    vec2 TexturCoord;
}In;

out vec4 out_Color;

uniform sampler2D Tekst;
uniform vec3 KolorTekstu;

void main(void)
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Tekst, In.TexturCoord).r);
    out_Color = vec4(KolorTekstu, 1.0) * sampled;


}

