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


#include "common/vec.h"

#include "game_common/camera.h"


Camera_t *Camera_New(vec3 position, vec3 target, vec3 up, float width, float height)
{
    Camera_t *camera = malloc(sizeof(*camera));
    if (camera)
    {
        Camera_Init(camera, position, target, up, width, height);
    }
    return camera;
}

void Camera_Init(Camera_t *self, vec3 position, vec3 target, vec3 up, float width, float height)
{
    self->ortho_matrix = mat4_identity();
    self->ortho_matrix = mat4_ortho(self->ortho_matrix, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
    //self->position = make_vec3(0.0f, 0.0f, 0.0f);
    //self->direction = make_vec3(0.0f, 0.0f, -1.0f);
    //self->up = make_vec3(0.0f, 1.0f, 0.0f);
    self->position = position;
    self->direction = vec3_normalize(vec3_sub(self->position, target));
    self->right = vec3_normalize(vec3_cross(up, self->direction));
    self->up = vec3_normalize(vec3_cross(self->direction, self->right));
}

void Camera_Move(Camera_t *self, vec3 movement)
{
    self->position = vec3_add(self->position, movement);
}

void Camera_Update(Camera_t *self)
{

}

void Camera_ShutDown(Camera_t *self)
{
    free(self);
}
