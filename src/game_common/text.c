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
#include "common/stack.h"
#include "common/vec.h"

#include "game_common/text.h"

static float RI_TEXT_UV_BOX_WIDTH = 0.125f;
static float RI_TEXT_WIDTH = 32.0f;
static float RI_TEXT_SPACESIZE = 20.0f;

static int line_size[] =
{
    36, 29, 30, 34, 25, 25, 34, 33,
    11, 20, 31, 24, 48, 35, 39, 29,
    42, 31, 27, 31, 34, 35, 46, 35,
    31, 27, 30, 26, 28, 26, 31, 28,
    28, 28, 29, 29, 14, 24, 30, 18,
    26, 14, 14, 14, 25, 28, 31,  0,
    0,  38, 39, 12, 36, 34,  0,  0,
    0,  38,  0,  0,  0,  0,  0,  0,
};


TextObject_t *TextObject()
{
    TextObject_t *text_object = (TextObject_t*) malloc(sizeof(*text_object));
    text_object->text = "place_holder";
    text_object->x = 0.0f;
    text_object->y = 0.0f;
    text_object->color = make_vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

TextObject_t TextObject_(char *txt, float xcoord, float ycoord)
{
    TextObject_t *text_object = (TextObject_t*) malloc(sizeof(*text_object));
    text_object->text = txt;
    text_object->x = xcoord;
    text_object->y = ycoord;

    text_object->color = make_vec4(1.0f, 1.0f, 1.0f, 1.0f);
}


TextManager_t TextManager_New()
{
    TextManager_t *t = (TextManager_t*) malloc(sizeof(*t));

    // init as 0 as default
    t->texturenr = 0;
}

void AddText(TextManager_t *self, TextObject_t *obj)
{
    // Add text object to our collection
    stack_push(self->txt_collection, obj);
}

void SetTextureID(TextManager_t *self, int val)
{
    self->texturenr = val;
}

void AddCharRenderInformation(TextManager_t *self, float *vec, float *cs, float *uv, s16 *indi, int vec_size, int cs_size, int uv_size, int indi_size)
{
    // We need a base value because the object has indices related to 
    // that object and not to this collection so basicly we need to 
    // translate the indices to align with the vertexlocation in ou
    // vecs array of vectors.
    s16 base = (s16)(self->index_vecs / 3);

    // We should add the vec, translating the indices to our saved vector
    for (int i = 0; i < vec_size; i++)
    {
        self->vecs[self->index_vecs++] = vec[i];
    }

    // We should add the colors.
    for (int i = 0; i < cs_size; i++)
    {
        self->colors[self->index_colors++] = cs[i];
    }

    // We should add the uvs
    for (int i = 0; i < uv_size; i++)
    {
        self->uvs[self->index_uvs++] = uv[i];
    }

    // We handle the indices
    for (int j = 0; j < indi_size; j++)
    {
        self->indices[self->index_indices++] = (s16)(base + indi[j]);
    }
}

void PrepareDrawInfo(TextManager_t *self)
{
    // Reset the indices.
    self->index_vecs = 0;
    self->index_indices = 0;
    self->index_uvs = 0;
    self->index_colors = 0;

    // Get the total amount of characters
    int char_count = 0;
    for (size_t i = 0; i < self->txt_collection->size; i++)
    {
        TextObject_t* txt = (TextObject_t*) (self->txt_collection->data[i]);
        if (txt != NULL)
        {
            if (!(txt->text == NULL))
            {
                char_count += strlen(txt->text);
            }
        }
    }

    // Create the arrays we need with the correct size.

    // These can fail...
    self->vecs = (float*) realloc(self->vecs, sizeof(float) * char_count * 12);
    self->colors = (float*) realloc(self->colors, sizeof(float) * char_count * 16);
    self->uvs = (float*) realloc(self->uvs, sizeof(float) * char_count * 8);
    self->indices = (s16*) realloc(self->indices, sizeof(s16) * char_count * 6);

}

void PrepareDraw(TextManager_t *self)
{
    // Setup all the arrays
    PrepareDrawInfo(self);

    for (size_t i = 0; self->txt_collection->size; i++)
    {
        int index = i;
        TextObject_t *txt = (TextObject_t*) self->txt_collection->data[++index]; // Get the next slot
        if (txt != NULL)
        {
            if (!(txt->text == NULL))
            {
                //ConvertTextToTriangleInfo(txt);
            }
        }
    }
}
