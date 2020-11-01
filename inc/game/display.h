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

#ifndef _DISPLAY_MANAGER_H_
#define _DISPLAY_MANAGER_H_

#include <pthread.h>

typedef union ivec2 ivec2;

typedef struct Screen_s
{
    struct GLFWwindow *window;
    struct GLFWmonitor *monitor;
    int width;
    int height;
    bool widescreen;
    bool vsync;
    bool fullscreen;
    bool exit;

#ifdef USE_BATCH_RENDERER
    struct BatchRenderer2D_s *renderer;
#elif defined(USE_SLOW_RENDERER)
    struct Renderer2D_s *renderer;
#else   
    struct Renderer_s *renderer;
#endif
} Screen_t;

//Screen_t *GetScreenInstance();

Screen_t *Screen_New(bool init);
void Screen_Init(Screen_t *self);
void Screen_Update(Screen_t *self, ivec2 position);
void Screen_ShutDown(Screen_t *self);
//void Screen_Update();
//void Screen_ShutDown(Screen_t *self, pthread_t thread);


#endif
