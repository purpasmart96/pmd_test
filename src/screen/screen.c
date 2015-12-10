// Copyright(c) <2015> <Purpasmart>
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

#include "screen/screen.h"
#include "screen/load_png.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *bitmapTex = NULL;
SDL_Surface *bitmapSurface = NULL;
SDL_Rect src, dest;


void screen_Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Pmd_wip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    //GLFWwindow* window = glfwCreateWindow(640, 480, "Pmd_wip", NULL, NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    bitmapSurface = SDL_GetWindowSurface(window);
    if (window == NULL)
    {
        ERROR("Error creating SDL window\n");
        exit(1);
    } 

    /*get RGBA components*/
    char *file = GetPngFile("test2.png");
    FreePngFile(file);

}

void screen_Free()
{
    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}
