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
#include "game_common/display_manager.h"


Screen *Screen_New(bool init)
{
    Screen *screen = malloc(sizeof(*screen));
    if (init)
    {
        Screen_Init(screen);
    }
    return screen;
}

void Screen_Init(Screen *self)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO ) < 0)
    {
        ERROR("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        //self->window = SDL_CreateWindow("Pmd_wip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL | (SDL_WINDOW_FULLSCREEN_DESKTOP * fullscreen));
        self->window = SDL_CreateWindow("Pmd_wip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
        if (self->window == NULL)
        {
            ERROR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            //self->texture = SDL_CreateTexture(self->renderer, 4, 0, 1280, 720);
            // Get window surface
            self->surface = SDL_GetWindowSurface(self->window);
            // Fill the surface white
            SDL_FillRect(self->surface, NULL, SDL_MapRGBA(self->surface->format, 0xFF, 0xFF, 0xFF, 0xFF));
            // Wait two seconds
            //SDL_Delay(2000);
        }
    }

}

void Screen_Update(Screen *self)
{
    //SDL_UnlockTexture(self->texture);
    //SDL_RenderCopy(self->renderer, self->texture, 0, 0);
    //SDL_RenderPresent(self->renderer);
    //SDL_LockTexture(self->texture, NULL, NULL, NULL); //(void**)&r->d.outputBuffer, &r->d.outputBufferStride);

    // Update the surface
    SDL_UpdateWindowSurface(self->window);
}

void Screen_Shutdown(Screen *self)
{
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    free(self);
}
