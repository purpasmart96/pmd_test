#version 330 core

//uniform mat4 ProjectionMatrix; 
//uniform mat4 ModelMatrix; 

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec4 vertex_color;
layout (location = 2) in vec2 texture_in;

out vec4 color;
out vec2 tex_coord;

void main()
{
    //gl_Position = vec4(vertex_position.xy, 0.0, 1.0);
    //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    //gl_Position = ProjectionMatrix * ModelMatrix * vec4(vertex_position.xy, 1.0); 
    gl_Position = vertex_position;
    color = vertex_color;
    tex_coord = texture_in;
}