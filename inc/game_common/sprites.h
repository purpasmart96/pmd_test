// Copyright(c) 2017 Purpasmart
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

#ifndef _SPRITES_H_
#define _SPRITES_H_

typedef struct Shader_s Shader_t;
//typedef struct Texture_s Texture_t;

typedef struct Sprites_s
{
    struct Shader_s *shader;

} Sprites_t;

Texture_t *LoadTexture(Texture_t *texture, const char *name);
//void LoadTexture(const char *name);

void Sprites_BindTexture(Texture_t *texture, int texture_unit);

void Sprite_MakeTextureAtlas(void);
void SpriteRenderer_DrawSprite(Sprites_t *self, Texture_t *texture, vec2 position, vec2 size, GLfloat rotate, vec3 color);
void Sprites_Init(Sprites_t *self);

#endif
