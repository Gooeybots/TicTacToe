#version 330 core

layout(location = 0) in vec4 position;

uniform vec2 offset;
uniform vec3 colourIn;
uniform mat4 view;

out vec3 colour;

void main()
{
    colour = colourIn;
    gl_Position = view * (position + vec4(offset, 0.0, 0.0));
}
