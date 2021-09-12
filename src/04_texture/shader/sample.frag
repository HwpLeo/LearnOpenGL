#version 330 core

in vec4 vertex_color;
in vec2 coord;
out vec4 frag_color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // frag_color = vertex_color;
    frag_color = mix(texture(texture1, coord), texture(texture2, coord), 0.2);
}