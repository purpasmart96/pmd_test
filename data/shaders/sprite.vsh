#version 330 core
#extension GL_ARB_shading_language_420pack: enable

//uniform mat4 ModelMatrix;
//uniform mat4 ProjectionMatrix;

layout (location = 0) in vec4 vertex_position; //vec2 position, vec2 texCoords
layout (location = 1) in vec4 vertex_color;

out vs_output
{
    vec4 color;
    vec2 texcoord;
} result;

void main()
{
    //gl_Position = ProjectionMatrix * ModelMatrix * vec4(vertex_position.xy, 0.0, 1.0);
    gl_Position = vec4(vertex_position.xy, 0.0, 1.0);
    result.color = vertex_color;
    result.texcoord = vertex_position.zw;
}