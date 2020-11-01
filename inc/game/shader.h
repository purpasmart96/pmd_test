// Copyright(c) 2016 Purpasmart
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

typedef struct Shader_s
{
    GLuint program;
    GLuint vertex_shader;
    GLuint frag_shader;
    char *vertex_path;
    char *frag_path;
} Shader_t;

Shader_t *Shader_New(char *vertex_path, char *frag_path);
void Shader_Load(Shader_t *self, char *vertex_path, char *frag_path);
void Shader_Init(Shader_t *self, char *vertex_path, char *frag_path);
void Shader_ShutDown(Shader_t *self);

void Shader_Use(Shader_t *self);

void Shader_SetFloat(Shader_t *self, const GLchar *name, GLfloat value);
void Shader_SetInteger(Shader_t *self, const GLchar *name, GLint value);
void Shader_SetVector2f(Shader_t *self, const GLchar *name, const vec2 *vector);
void Shader_SetVector3f(Shader_t *self, const GLchar *name, const vec3 *vector);
void Shader_SetVector4f(Shader_t *self, const GLchar *name, const vec4 *vector);
void Shader_SetMatrix3(Shader_t * self, const GLchar * name, const mat3 * matrix);
void Shader_SetMatrix4(Shader_t *self, const GLchar *name, const mat4 *matrix);


#endif
