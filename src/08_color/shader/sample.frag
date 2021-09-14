#version 330 core

in vec2 coord;
out vec4 frag_color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;
uniform vec3 light_color;

void main()
{
    frag_color = mix(texture(texture1, coord), texture(texture2, coord), mixer) * vec4(light_color, 1.0);
}