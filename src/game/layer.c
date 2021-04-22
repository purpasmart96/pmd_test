// Copyright(c) 2020 Purpasmart
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

#include "common/vec.h"
#include "common/list_generic.h"
#include "common/list_queue.h"

#include "game/vertex_buffer.h"
#include "game/index_buffer.h"
#include "game/vertex_array.h"
#include "game/camera.h"
#include "game/shader.h"
#include "game/renderer2d_info.h"
#include "game/renderer2d.h"
#include "game/single_sprite.h"
#include "game/layer.h"

Layer_t *Layer_New(Renderer2D_t *renderer, Shader_t *shader, mat4 *mtx)
{
    Layer_t *layer = malloc(sizeof(*layer));

    if (layer)
    {
        Layer_Init(layer,renderer, shader, mtx);
    }
    return layer;
}

void Layer_Init(Layer_t *self, Renderer2D_t *renderer, Shader_t *shader, mat4 *mtx)
{
    self->renderer = renderer;
    self->renderables = Queue_New();
    self->mtx = mtx;
    self->shader = shader;

    Shader_SetMatrix4(self->shader, "ProjectionMatrix", self->mtx);
    Shader_NotUse(self->shader);
}

void Layer_Add(Layer_t *self, SingleSprite_t *renderable)
{
    Queue_PushBack(self->renderables, renderable);
}

void Layer_Draw(Layer_t *self)
{
    Shader_Use(self->shader);
    LIST_FOREACH(self->renderables, front, next, cur)
    {
        Renderer2D_Submit(self->renderer, cur->data);
    }

    Renderer2D_Flush(self->renderer);
    //for (int i = 0; i < self->renderables->size; i++)
    //{
    //    Renderer2DInfo_t *tmp = Queue_At(self->renderables, i);
    //    Renderer2D_Submit(self->renderer, tmp);
    //}

}

void Layer_Update(Layer_t *self)
{



}

void Layer_ShutDown(Layer_t *self)
{
    Shader_ShutDown(self->shader);
    Renderer2D_ShutDown(self->renderer);
    Queue_ShutDown(self->renderables);

    free(self);
}
