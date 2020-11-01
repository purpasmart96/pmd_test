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
#include <glfw3.h>

#include "common/vec.h"

#include "game/input.h"

Input_t *Input_New(bool init)
{
    Input_t *input = malloc(sizeof(*input));

    if (!input)
    {
        return NULL;
    }
    else if (init)
    {
        Input_Init(input);
    }

    return input;
}

bool Input_IsKeyPressed(Input_t *self, u32 key_code)
{
    if (key_code >= MAX_KEYS)
    {
        ERROR("Out of range key_code input! %u\n", key_code);
        return false;
    }

    return self->keys[key_code];
}

vec2 Input_GetMousePosition(Input_t *self)
{
    return make_vec2(self->mouse_x, self->mouse_y);
}

bool Input_IsMouseButtonPressed(Input_t *self, u32 button)
{
    if (button >= MAX_BUTTONS)
    {
        ERROR("Out of range mouse button input! %u\n", button);
        return false;
    }

    return self->buttons[button];
}

void Input_Init(Input_t *self)
{
    //u8 pixels[16 * 16 * 4];
    //memset(pixels, 0xff, sizeof(pixels));
    //GLFWimage image;
    //image.width = 16;
    //image.height = 16;
    //image.pixels = pixels;
    //self->cursor = glfwCreateCursor(&image, 0, 0);

    // Initialize all the keys to being released and not pressed.
    for (int i = 0; i < MAX_KEYS; i++)
    {
        self->keys[i] = false;
    }

    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        self->buttons[i] = false;
    }

    //self->current_key = 0;
    //self->scan_code = 0;
    //self->action = 0;
    //self->mods = 0;
}

void Input_Update(Input_t *self)
{

}

void Input_ShutDown(Input_t *self)
{
    free(self);
}
