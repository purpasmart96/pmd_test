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

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

typedef struct Game_s Game_t;

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

typedef struct Input_s
{
    bool keys[MAX_KEYS];
    bool buttons[MAX_BUTTONS];

    double mouse_x;
    double mouse_y;

    //int current_key;
    //int scan_code;
    //int action;
    //int mods;

    GLFWcursor *cursor;
} Input_t;

Input_t *Input_New(bool init);
void Input_Init(Input_t *self);
void Input_Update(Input_t *self);
void Input_ShutDown(Input_t *self);

bool Input_IsKeyPressed(Input_t *self, u32 key_code);
vec2 Input_GetMousePosition(Input_t *self);
bool Input_IsMouseButtonPressed(Input_t * self, u32 button);

#endif
