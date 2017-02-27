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


#include "common/string.h"

String_t *string_new(const char *string)
{
    String_t *str = malloc(sizeof(*str));
    str->length = strlen(string);
    str->data = malloc(sizeof(char*) * str->length);
    return str;
}

void string_resize(String_t *string, size_t capacity)
{
    string->length = capacity;
    char *temp = realloc(string->data, sizeof(char *) * string->length);

    if (!temp)
    {
        ERROR("Memory allocation failure\n");
    }
    string->data = temp;
}

void string_delete(String_t *string)
{
    free(string->data);
    free(string);
}

size_t string_format(String_t *self, char *dst, const char *format, va_list params)
{
    return sprintf(dst, format, params);
}
