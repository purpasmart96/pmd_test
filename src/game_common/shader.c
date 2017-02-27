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
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include "common/vec.h"
#include "common/list_generic.h"

#include "game_common/shader.h"


static mat4 model_matrix;
static mat4 view_matrix;
static mat4 projection_matrix;
static mat4 model_view_matrix;
static mat4 model_view_projection_matrix;


// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] =
{
    // Positions         // Colors
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // Bottom Right
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Left
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top 
};

Shader_t *Shader_New(bool init)
{
    Shader_t *shader = malloc(sizeof(*shader));

    if (!shader)
    {
        return NULL;
    }
    else if (init)
    {
        Shader_Init(shader);
    }

    return shader;
}

static const char *OpenFileFromPath(const char *path)
{
    // Load file
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        ERROR("Couldn't Read File!\n");
    }

    // Get Length
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Get source
    char *source = malloc(length + 1);
    if (source == NULL)
    {
        ERROR("Couldn't allocate enough space for the shader!\n");
    }

    // Read file
    fread(source, 1, length, file);

    // Close file
    fclose(file);
    source[length] = '\n';
    return source;
}

/*
void ExitOnGLError(const char* error_message)
{
    const GLenum ErrorValue = glGetError();

    if (ErrorValue != GL_NO_ERROR)
    {
        ERROR("%s: %s\n", error_message, glfwGe(ErrorValue));
        exit(EXIT_FAILURE);
    }
}
*/


static GLuint LoadShader(const char *filename, GLenum shader_type)
{
    GLuint shader_id = 0;
    FILE *file;
    size_t file_size = -1;
    char *glsl_source;

    if (NULL != (file = fopen(filename, "rb")) && 0 == fseek(file, 0, SEEK_END) && -1 != (file_size = ftell(file)))
    {
        rewind(file);

        if (NULL != (glsl_source = malloc(file_size + 1)))
        {
            if (file_size == fread(glsl_source, sizeof(char), file_size, file))
            {
                glsl_source[file_size] = '\0';

                if (0 != (shader_id = glCreateShader(shader_type)))
                {
                    glShaderSource(shader_id, 1, (const GLchar**)&glsl_source, NULL);
                    glCompileShader(shader_id);
                    //ExitOnGLError("Could not compile a shader");
                }
                else
                    ERROR("Could not create a shader.\n");
            }
            else
                ERROR("Could not read file %s\n", filename);

            free(glsl_source);
        }
        else
            ERROR("Could not allocate %ld bytes.\n", file_size);

        fclose(file);
    }
    else
    {
        if (NULL != file)
            fclose(file);
        fprintf(stderr, "ERROR: Could not open file %s\n", filename);
    }

    return shader_id;
}


static void VertexAttribsInit()
{
    //glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(GL_FLOAT) * 7, attributeOffset(offset, idDrawVert::xyzOffset));
    //glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(idDrawVert), attributeOffset(offset, idDrawVert::texcoordOffset));
    //glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(idDrawVert), attributeOffset(offset, idDrawVert::normalOffset));
    //glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, false, sizeof(idDrawVert), attributeOffset(offset, idDrawVert::colorOffset));
    //glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(idDrawVert), attributeOffset(offset, idDrawVert::binormalOffset));
    //glVertexAttribPointer(5, 3, GL_FLOAT, false, sizeof(idDrawVert), attributeOffset(offset, idDrawVert::tangentOffset));
}

static void Shader_StoreDataInAttributeList(Shader_t *self, int attribute_num, int coord_size, float *data, int data_size)
{
    int vbo_id;
    int *vbo = LIST_TO_ARRAY(ListInt, self->vbo);
    glGenBuffers(vbo_id, vbo);
    LIST_PUSH(ListInt, self->vbo, vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_num, coord_size, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


static int Shader_MakeVAO(Shader_t *self)
{
    int vao_id;
    int *vao = LIST_TO_ARRAY(ListInt, self->vao);
    glGenVertexArrays(vao_id, vao);
    free(vao);

    LIST_PUSH(ListInt, self->vao, vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void Shader_Init(Shader_t *self)
{
    self->vao = LIST_NEW(ListInt);
    self->vbo = LIST_NEW(ListInt);

    self->vertex_shader = LoadShader("data/shaders/vertex.vsh", GL_VERTEX_SHADER);
    self->frag_shader = LoadShader("data/shaders/frag.psh", GL_FRAGMENT_SHADER);
    self->program = glCreateProgram();
    glAttachShader(self->program, self->vertex_shader);
    glAttachShader(self->program, self->frag_shader);
    //Shader_BindAttributes(self);
    glLinkProgram(self->program);
    glValidateProgram(self->program);
    //Shader_GetAllUniformLocations();
}

void Shader_Update(Shader_t *self)
{
    Shader_Use(self);
    //DrawStuff();
    glBindVertexArray((GLint)self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    //DrawSprite(self, make_vec2(200.0f, 200.0f), make_vec2(64.0f, 64.0f), 45.0f, make_vec4(0.0f, 0.0f, 0.0f, 0.0f));
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

void Shader_SetVector2f(Shader_t *self, const GLchar *name, const vec2 vector)
{
    glUniform2fv(glGetUniformLocation(self->program, name), 1, vector.v);
}

void Shader_SetVector3f(Shader_t *self, const GLchar *name, const vec3 vector)
{
    glUniform3fv(glGetUniformLocation(self->program, name), 1, vector.v);
}

void Shader_SetVector4f(Shader_t *self, const GLchar *name, const vec4 vector)
{
    glUniform4fv(glGetUniformLocation(self->program, name), 1, vector.v);
}

void Shader_SetMatrix4(Shader_t *self, const GLchar *name, const mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(self->program, name), 1, GL_FALSE, matrix.m);
}

void DrawSprite(Shader_t *self, vec2 position, vec2 size, GLfloat rotate, vec4 color)
{
    int width = 0;
    int height = 0;
    u8 *image = SOIL_load_image("test.png", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    model_matrix = mat4_translate(model_matrix, position.x, position.y, 0.0f);  // First translate (transformations are: scale happens first, then rotation and then final translation happens; reversed order)
    model_matrix = mat4_translate(model_matrix, 0.5f * size.x, 0.5f * size.y, 0.0f); // Move origin of rotation to center of quad
    model_matrix = mat4_rotate(rotate, 0.0f, 0.0f, 1.0f); // Then rotate
    model_matrix = mat4_translate(model_matrix, -0.5f * size.x, -0.5f * size.y, 0.0f); // Move origin back

    //model_matrix = mat4_scale(model_matrix, size, 1.0f); // Last scale

    Shader_SetMatrix4(self, "ModelMatrix", model_matrix);

    // Render textured quad
    Shader_SetVector4f(self, "vertex_color", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, LIST_AT(ListInt, self->textures, 0));

    glBindVertexArray(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

