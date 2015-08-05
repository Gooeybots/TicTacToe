#version 330 core

in vec3 colour;

smooth out vec4 color;

void main()
{
    color = vec4(colour, 1.0);
}
