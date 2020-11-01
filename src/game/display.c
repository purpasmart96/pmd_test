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

#include <pthread.h>
#include "common/vec.h"
#include "game/game.h"

#include <dictionary.h>
#include <iniparser.h>

#if defined(USE_BATCH_RENDERER) || defined(USE_SLOW_RENDERER)
#include "game/renderer2d.h"
#else
#include "game/renderer.h"
#endif

#include "game/display.h"

//static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//static struct Screen_s *screen_instance = NULL;

static void error_callback(int error, const char *description)
{
    ERROR("%s\n", description);
}

//Screen_t *GetScreenInstance()
//{
//    // putting a pre condition to avoid locks on multiple calls
//    // if we don't put this condition,_lock.acquire()and _lock.release() will always be executed on 
//    // multiple GetInstance() call and will affect performance.
//    if (screen_instance == NULL)
//    {
//        pthread_mutex_lock(&lock);
//
//        if (screen_instance == NULL)
//        {
//            screen_instance = Screen_New(true);
//        }
//        pthread_mutex_unlock(&lock);
//    }
//    return screen_instance;
//}

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
    dictionary *ini;
    const char *ini_name = "game.ini";
    ini = iniparser_load(ini_name);

    if (ini == NULL)
    {
        ERROR("Cannot parse file: %s\n", ini_name);
        self->width = 1280;
        self->height = 720;
        self->vsync = true;
        self->fullscreen = false;
    }
    else 
    {
        self->width = iniparser_getint(ini, "Video:resolution_width", -1);
        self->height = iniparser_getint(ini, "Video:resolution_height", -1);
        self->vsync = iniparser_getboolean(ini, "Video:enable_vsync", -1);
        self->fullscreen = iniparser_getboolean(ini, "Video:enable_fullscreen", -1);
    }

    iniparser_freedict(ini);

    // Initialize GLFW
    if (!glfwInit())
    {
        // Just shut it down
        // Doesn't release evrything though...
        ERROR("GLFW could not initialize!\n");
        //Screen_ShutDown(self);
        return;
    }
    else
    {
        glfwSetErrorCallback(error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        self->monitor = NULL;
        if (self->fullscreen)
        {
            self->monitor = glfwGetPrimaryMonitor();
        }

        self->window = glfwCreateWindow(self->width, self->height, "Pmd_wip", self->monitor, NULL);
        glfwMakeContextCurrent(self->window);

        if (!self->window)
        {
            ERROR("Window could not be created!\n");
            glfwTerminate();
        }
        else if (glewInit() != GLEW_OK)
        {
            ERROR("GLEW could not initialize!\n");
            glfwTerminate();

        }
        else if (!GLEW_VERSION_3_3)
        {
            ERROR("OpenGL 3.3 required version support not present.\n");
            glfwTerminate();
            //exit(-1);
        }
        else
        {
            glfwSetWindowAspectRatio(self->window, 16, 9);
            glViewport(0, 0, self->width, self->height);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        #ifdef USE_BATCH_RENDERER
            self->renderer = BatchRenderer2D_New();
        #elif defined(USE_SLOW_RENDERER)
            self->renderer = Renderer2D_New();
        #else   
            self->renderer = Renderer_New(true);
        #endif

        }
    }
}

//void Screen_Update()
//{
//    Screen_t *screen = GetScreenInstance();
//    screen->exit = false;
//    while (!screen->exit)
//    {
//        //pthread_mutex_lock(&lock);
//        // Clear color and depth buffer  
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//#ifdef USE_BATCH_RENDERER
//        BatchRenderer2D_Update(self->renderer);
//#elif defined(USE_SLOW_RENDERER)
//        Renderer2D_Update(self->renderer);
//#else
//        //pthread_join(self->renderer->thread_id, NULL);
//        Renderer_Update(screen->renderer);
//#endif
//        // Swap the buffers  
//        glfwSwapBuffers(screen->window);
//        glfwSwapInterval(screen->vsync);
//        //pthread_mutex_unlock(&lock);
//    }
//    pthread_exit(NULL);
//}


void Screen_Update(Screen_t *self, ivec2 position)
{
    // Clear color and depth buffer  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef USE_BATCH_RENDERER
    BatchRenderer2D_Update(self->renderer, position);
#elif defined(USE_SLOW_RENDERER)
    Renderer2D_Update(self->renderer, position);
#else
    //pthread_join(self->renderer->thread_id, NULL);
    Renderer_Update(self->renderer, position);
#endif
    // Swap the buffers  
    glfwSwapBuffers(self->window);
    glfwSwapInterval(self->vsync);
}

void Screen_ShutDown(Screen_t *self)
{
    //self->exit = true;
    //pthread_join(thread, NULL);
#ifdef USE_BATCH_RENDERER
    BatchRenderer2D_ShutDown(self->renderer);
#elif defined(USE_SLOW_RENDERER)
    Renderer2D_ShutDown(self->renderer);
#else   
    Renderer_ShutDown(self->renderer);
#endif
    glfwDestroyWindow(self->window);
    glfwTerminate();
    free(self);
}
