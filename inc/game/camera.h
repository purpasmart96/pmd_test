// Copyright(c) 2019 Purpasmart
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


#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

typedef struct Camera_s
{
    mat4 *ortho_matrix;
    vec3 position; // eye
    vec3 direction; // target - position
    vec3 right;
    vec3 up; // rotation
} Camera_t;

Camera_t *Camera_New(vec3 position, vec3 target, vec3 up, float width, float height);

void Camera_Init(Camera_t *self, vec3 position, vec3 target, vec3 up, float width, float height);

void Camera_Move(Camera_t *self, vec3 movement);

void Camera_Update(Camera_t *self);

void Camera_ShutDown(Camera_t *self);

#endif
