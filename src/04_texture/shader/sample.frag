#version 330 core

in vec4 vertex_color;
in vec2 coord;
out vec4 frag_color;

uniform sampler2D texture1;

void main()
{
    // frag_color = vertex_color;
    frag_color = texture(texture1, coord);
}