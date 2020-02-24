#version 330 core

uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

//layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 colors;
layout (location = 2) in vec2 texcoords;

out vec2 texcoord;

void main()
{
    //texcoord = vertex.zw;
    texcoord = texcoords;
    //color = colors;
    //gl_Position =  ProjectionMatrix * ModelMatrix * ViewMatrix * vec4(vertex.xy, 0.0, 1.0);
    gl_Position =  ProjectionMatrix * ModelMatrix * ViewMatrix * vec4(vertex.xyz, 1.0);
}
