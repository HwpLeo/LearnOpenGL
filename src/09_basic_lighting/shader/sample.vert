#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 world_normal;
out vec3 world_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    world_pos = vec3(model * vec4(pos, 1.0));
    world_normal = mat3(transpose(inverse(model))) * normal;
}