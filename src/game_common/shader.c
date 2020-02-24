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

#include "util.h"

#include <GL/glew.h>
#include <glfw3.h>

#include "common/vec.h"
#include "common/list_generic.h"

#include "game_common/game.h"
#include "game_common/dungeon.h"
#include "game_common/sprites.h"
#include "game_common/player.h"
#include "game_common/vertex_buffer.h"
#include "game_common/index_buffer.h"
#include "game_common/vertex_array.h"
#include "game_common/camera.h"
#include "game_common/shader.h"

static mat4 view_matrix;

Shader_t *Shader_New(char *vertex_path, char *frag_path)
{
    Shader_t *shader = malloc(sizeof(*shader));

    if (shader)
    {
        Shader_Init(shader, vertex_path, frag_path);
    }

    return shader;
}

static GLuint LoadShader(const char *filename, GLenum shader_type)
{
    GLuint shader_id = 0;
    FILE *file;
    size_t file_size = -1;
    char *glsl_source;

    if (NULL != (file = fopen(filename, "rb")) && 0 == fseek(file, 0, SEEK_END) && -1 != (file_size = ftell(file)))
    {
        rewind(file);

        glsl_source = malloc(file_size + 1);
        if (glsl_source != NULL)
        {
            if (file_size == fread(glsl_source, sizeof(char), file_size, file))
            {
                glsl_source[file_size] = '\0';

                shader_id = glCreateShader(shader_type);
                if (shader_id != 0)
                {
                    glShaderSource(shader_id, 1, (const GLchar**)&glsl_source, NULL);
                    glCompileShader(shader_id);
                }
                else
                {
                    ERROR("Could not create a shader.\n");
                }
            }
            else
            {
                ERROR("Could not read file %s\n", filename);
            }

            free(glsl_source);
        }
        else
        {
            ERROR("Could not allocate %ld bytes.\n", file_size);
        }

        fclose(file);
    }
    else
    {
        if (file != NULL)
            fclose(file);
        ERROR("Could not open file %s\n", filename);
    }

    return shader_id;
}

void Shader_Load(Shader_t *self, char *vertex_path, char *frag_path)
{
    //self->vertex_shader = LoadShader("data/shaders/sprite.vsh", GL_VERTEX_SHADER);
    //self->frag_shader = LoadShader("data/shaders/sprite.psh", GL_FRAGMENT_SHADER);

    self->vertex_shader = LoadShader(vertex_path, GL_VERTEX_SHADER);
    self->frag_shader = LoadShader(frag_path, GL_FRAGMENT_SHADER);
    self->program = glCreateProgram();
    glAttachShader(self->program, self->vertex_shader);
    glAttachShader(self->program, self->frag_shader);
    glLinkProgram(self->program);
}


void Shader_Init(Shader_t *self, char *vertex_path, char *frag_path)
{
    Shader_Load(self, vertex_path, frag_path);
    Shader_Use(self);
}

void Shader_Update(Shader_t *self)
{
    //vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    //vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    //vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    //view_matrix = mat4_lookAt(eye, center, up);
    //Shader_SetMatrix4(self, "ViewMatrix", &view_matrix);
}

void Shader_ShutDown(Shader_t *self)
{
    glDeleteProgram(self->program);
    free(self);
}

void Shader_Use(Shader_t *self)
{
    glUseProgram(self->program);
}

void Shader_SetFloat(Shader_t *self, const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(self->program, name), value);
}

void Shader_SetInteger(Shader_t *self, const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(self->program, name), value);
}

void Shader_SetVector2f(Shader_t *self, const GLchar *name, const vec2 *vector)
{
    glUniform2fv(glGetUniformLocation(self->program, name), 1, vector->v);
}

void Shader_SetVector3f(Shader_t *self, const GLchar *name, const vec3 *vector)
{
    glUniform3fv(glGetUniformLocation(self->program, name), 1, vector->v);
}

void Shader_SetVector4f(Shader_t *self, const GLchar *name, const vec4 *vector)
{
    glUniform4fv(glGetUniformLocation(self->program, name), 1, vector->v);
}

void Shader_SetMatrix3(Shader_t *self, const GLchar *name, const mat3 *matrix)
{
    glUniformMatrix3fv(glGetUniformLocation(self->program, name), 1, GL_FALSE, matrix->m);
}

void Shader_SetMatrix4(Shader_t *self, const GLchar *name, const mat4 *matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(self->program, name), 1, GL_FALSE, matrix->m);
}
