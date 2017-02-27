#version 330 core

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec4 vertex_color;

out vec4 color;

void main()
{
    gl_Position = vertex_position;
    color = vertex_color;
}