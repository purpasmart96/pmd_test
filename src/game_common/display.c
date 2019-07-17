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

#include "common/vec.h"
#include "game_common/shader.h"
#include "game_common/display.h"


static void error_callback(int error, const char *description)
{
    ERROR("%s\n", description);
}

Screen_t *Screen_New(bool init)
{
    Screen_t *screen = malloc(sizeof(*screen));
    if (init)
    {
        Screen_Init(screen);
    }
    return screen;
}

void Screen_Init(Screen_t *self)
{
    self->vsync = true;
    // Initialize GLFW
    if (!glfwInit())
    {
        // Just shut it down
        // Doesn't release evrything though...
        ERROR("GLFW could not initialize!\n");
        Screen_Shutdown(self);
        return;
    }
    else
    {
        glfwSetErrorCallback(error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create window
        //self->window = glfwCreateWindow(1920, 1080, "Pmd_wip", NULL, NULL);
        self->window = glfwCreateWindow(1280, 720, "Pmd_wip", NULL, NULL);
        glfwMakeContextCurrent(self->window);

        if (!self->window)
        {
            ERROR("Window could not be created!\n");
        }
        else if (glewInit() != GLEW_OK)
        {
            ERROR("GLEW could not initialize!\n");
        }
        else if (!GLEW_VERSION_3_3)
        {
            ERROR("OpenGL 3.3 required version support not present.\n");
            //exit(-1);
        }
        else
        {
            glfwSetWindowAspectRatio(self->window, 16, 9);
            glViewport(0, 0, 1280, 720);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            self->shader = Shader_New(true);
        }
    }

}

void Screen_Update(Screen_t *self)
{
    // Clear color and depth buffer  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader_Update(self->shader);
    // Swap the buffers  
    glfwSwapBuffers(self->window);
    glfwSwapInterval(self->vsync);
}

void Screen_Shutdown(Screen_t *self)
{
    Shader_ShutDown(self->shader);
    glfwDestroyWindow(self->window);
    glfwTerminate();
    free(self);
}
