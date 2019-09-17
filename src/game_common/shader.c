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
//#include <SOIL.h>

#include "common/vec.h"
#include "common/list_generic.h"

#include "game_common/sprites.h"
#include "game_common/shader.h"


static mat4 model_matrix;
static mat4 view_matrix;
static mat4 projection_matrix;
static mat4 model_view_matrix;
static mat4 model_view_projection_matrix;

static Texture_t *my_texture;

struct VertexData
{
    GLfloat quad[12];
    GLfloat quad_color[12];
    GLfloat tex_coord[8];
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


//static void Shader_StoreDataInAttributeList(Shader_t *self, int attribute_num, int coord_size, float *data, int data_size)
//{
//    int vbo_id;
//    int *vbo = LIST_TO_ARRAY(ListInt, self->vbo);
//    glGenBuffers(vbo_id, vbo);
//    LIST_PUSH(ListInt, self->vbo, vbo_id);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
//    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
//    glVertexAttribPointer(attribute_num, coord_size, GL_FLOAT, false, 0, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}


//static int Shader_MakeVAO(Shader_t *self)
//{
//    int vao_id;
//    int *vao = LIST_TO_ARRAY(ListInt, self->vao);
//    glGenVertexArrays(vao_id, vao);
//    free(vao);
//
//    LIST_PUSH(ListInt, self->vao, vao_id);
//    glBindVertexArray(vao_id);
//    return vao_id;
//}

static GLfloat quad_color[12];

GLfloat quad[] =
{
    -1, -1, 0, // bottom left corner
    -1,  1, 0, // top left corner
     1,  1, 0, // top right corner
     1, -1, 0 }; // bottom right corner

static GLfloat tex_coords[] =
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};

static GLfloat tex_coords2[] =
{
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

// OpenGL textures are loaded left to right, bottom to top.
static GLfloat tex_coords3[] =
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

//static GLfloat tex_coords[] =
//{
//    0.0f, 0.0f,
//    1.0f, 0.0f,
//    1.0f, 1.0f,
//    0.0f, 1.0f
//};

static GLubyte indices[] =
{
    0,1,2, // first triangle (bottom left - top left - top right)
    0,2,3 // second triangle (bottom left - top right - bottom right)
};

static GLubyte indices2[] =
{
    0,1,2, // first triangle (bottom left - top left - top right)
    2,3,0 // second triangle (bottom left - top right - bottom right)
};

//GLuint elements[] =
//{
//    0, 1, 2,
//    2, 3, 0
//};


void ShaderRenderer_DrawSprite(Shader_t *self, Texture_t *texture, vec2 position, vec2 size, GLfloat rotate, vec3 color)
{
    Shader_Use(self);

    mat4 model = mat4_translate(model, position.x, position.y, 0.0f, 0.0f);

    model = mat4_translate(model, 0.5f * size.x, 0.5f * size.y, 0.0f);
    model = mat4_rotate(model, rotate, 0.0f, 0.0f, 1.0f);
    model = mat4_translate(model, -0.5f * size.x, -0.5f * size.y, 0.0f);

    model = mat4_scale_xyz(model, size.x, size.y, 1.0f);

    Shader_SetMatrix4(self, "ModelMatrix", &model);
    Shader_SetVector3f(self, "vertex_color", &color);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glBindVertexArray(self->quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Shader_InitSprite(Shader_t *self)
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &self->quad_vao);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(self->quad_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    //int scale_x = 1920 / VIRTUAL_WIDTH;
    //int scale_y = 1080 / VIRTUAL_HEIGHT;
    //mat4 sprite_matrix = { 0 };
    //mat4 matrix = mat4_scale_xyz(sprite_matrix, scale_x, scale_y, 1.0f);

    //_spriteBatch.Begin(transformMatrix: matrix);
}


static void Renderer_Init(Shader_t *self)
{
}

void Shader_LoadShaders(Shader_t *self)
{
    self->vertex_shader = LoadShader("data/shaders/vertex.vsh", GL_VERTEX_SHADER);
    self->frag_shader = LoadShader("data/shaders/frag.psh", GL_FRAGMENT_SHADER);
    self->program = glCreateProgram();
    glAttachShader(self->program, self->vertex_shader);
    glAttachShader(self->program, self->frag_shader);
    glLinkProgram(self->program);
}

void Shader_Init(Shader_t *self)
{
    float fov = 90.0f;
    float width = 1280.0f;
    float height = 720.0f;
    float znear = 0.1f; 
    float zfar = 100.0f;

    float aspect_ratio = width / (float)height;

    Shader_SetProjectionMatrix(self, fov, aspect_ratio, znear, zfar);

    Shader_LoadShaders(self);
    // Setup quad colors
    quad_color[0] =  -0.6f; quad_color[1] =  1.0f; quad_color[2]  = 0.2f; quad_color[3] =  0.4f;
    quad_color[4]  = 0.7f; quad_color[5] =  0.4f; quad_color[6] =  0.5f; quad_color[7]  = 0.1f;
    quad_color[8]  = 0.1f; quad_color[9] =  0.3f; quad_color[10] = 0.1f; quad_color[11] = 0.2f; 

    GLint attrib_position  = glGetAttribLocation(self->program, "vertex_position");
    GLint attrib_color     = glGetAttribLocation(self->program, "vertex_color");
    GLint attrib_tex_coord = glGetAttribLocation(self->program, "vertex_texcoord");
    GLint uniform_sampler  = glGetUniformLocation(self->program, "tex_sampler");

    // setup and copy
    struct VertexData *vertex_data = malloc(sizeof(struct VertexData));

    memcpy(vertex_data->quad, quad, sizeof(GLfloat) * 12);
    memcpy(vertex_data->quad_color, quad_color, sizeof(GLfloat) * 12);
    memcpy(vertex_data->tex_coord, tex_coords2, sizeof(GLfloat) * 8);

    // Generate VBO handle for drawing
    glGenBuffers(1, &self->vbo_);

    // Generate VAO
    glGenVertexArrays(1, &self->vao_);
    glBindVertexArray(self->vao_);

    // Attach vertex data to VAO
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(struct VertexData), vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offsetof(struct VertexData, quad));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offsetof(struct VertexData, quad_color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offsetof(struct VertexData, tex_coord));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    my_texture = LoadTexture(my_texture, "test2.png");
    //glUniform1i(glGetUniformLocation(self->program, "tex_sampler"), 0);
    
    Shader_Use(self);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    free(vertex_data);
}

void Shader_Update(Shader_t *self)
{
    //Shader_Use(self);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //mat4 m1 = mat4_identity();
    //mat4 m2 = mat4_identity();

    //glm::ortho(0, width, height, 0, 0, 1000)
    //m1 = mat4_ortho2(m1, 1280, 720, 1.0f, 1.0f, 0.0f, 1000.0f);
    //m2 = mat4_ortho3(m2, 1280, 720, 1.0f, 1.0f, 0.0f, 1000.0f);


    //Shader_SetMatrix4(self, "ProjectionMatrix", Shader_GetProjectionMatrix(self));

    	// Texture binding - we set GL_ACTIVE_TEXTURE0, and then we tell fragment shader
     // that gSampler variable will fetch data from GL_ACTIVE_TEXTURE0

    //Shader_SetInteger(self, "tex_sampler", 0);
    //
    //glUniform1i(glGetUniformLocation(self->program, "tex_sampler"), 0);
    Sprites_BindTexture(my_texture, 0);
    //GLint uniform_sampler  = glGetUniformLocation(self->program, "tex_sampler");
    //glUniform1i(uniform_sampler, 0);

    //int iModelViewLoc = glGetUniformLocation(self->program, "ModelMatrix");
    //int iProjectionLoc = glGetUniformLocation(self->program, "ProjectionMatrix");

    //glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, Shader_GetProjectionMatrix(self).m);

    //mat4 ModelView = mat4_lookAt(make_vec3(0.0f, 15.0f, 40.0f), make_vec3(0.0f, 0.0f, 0.0f), make_vec3(0.0f, 1.0f, 0.0f));

    // Quad render

    glBindVertexArray(self->vao_);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);


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

void Shader_SetProjectionMatrix(Shader_t *self, float fov, float aspect_ratio, float znear, float zfar)
{
    self->projection_matrix = mat4_perspective(fov, aspect_ratio, znear, zfar);
    //mat4 matrix = mat4_perspective(fov, aspect_ratio, znear, zfar);
    //memcpy(&self->projection_matrix, &matrix, sizeof(mat4));
}

mat4 *Shader_GetProjectionMatrix(Shader_t *self)
{
    return self->projection_matrix;
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

