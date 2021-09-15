#version 330 core

in vec2 coord;
in vec3 world_normal;
in vec3 world_pos;
out vec4 frag_color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;
uniform vec3 light_color;
uniform vec3 ambient_light;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 camera_pos;
uniform float specular_strength;

void main()
{
    vec3 light_dir = normalize(light_pos - world_pos);
    float diffuse = max(dot(normalize(world_normal), light_dir), 0.0);
    //float diffuse = 0.3;
    vec4 ambient_color = vec4(ambient_light, 1.0);
    vec4 diffuse_color = vec4(light_color, 1.0) * diffuse;
    vec3 view_dir = normalize(camera_pos - world_pos);
    vec3 reflect_dir = normalize(reflect(-light_dir, world_normal));
    float specular = pow(max(0, dot(reflect_dir, view_dir)), 32);
    vec4 specular_color = vec4(light_color * specular, 1.0);
    frag_color = ambient_color + diffuse_color + specular_color;
}