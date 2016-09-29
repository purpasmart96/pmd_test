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

#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include "util.h"

typedef struct mem_chunk
{
    u8  *data;               // The actual Data
    size_t capacity;         // Size of the "Data"-Block
    size_t size;             // actual used Size
    bool is_alloc_chunk;     // true, when this MemoryChunks
                             // Points to a "Data"-Block
                             // which can be deallocated via "free()"
    struct mem_chunk *next;  // Pointer to the Next MemoryChunk
                             // in the List (may be NULL)
} MemChunk;

typedef struct
{
    MemChunk *first_chunk;
    MemChunk *last_chunk;
    MemChunk *cursor_chunk;

    size_t total_mem_pool_size;
    size_t used_mem_pool_size;
    size_t free_mem_pool_size;

    size_t mem_chunk_size;
    u32    mem_chunk_count;
    size_t object_count;

    bool set_mem_data;
    size_t min_mem_size_alloc;

} MemPool;

MemPool  *mempool_New(const size_t pool_size, const size_t mem_chunk_size, const size_t min_mem_size_alloc, bool set_mem_data);
void     DeallocateAllChunks(MemPool *self);
u32      CalculateNeededChunks(MemPool *self, const size_t size);
size_t   CalculateBestMemoryBlockSize(MemPool *self, const size_t size);
bool     AllocMem(MemPool *self, const size_t mem_size);
bool     RecalcChunkMemorySize(MemPool *self, MemChunk *chunk, u32 chunk_count);
MemChunk *SetChunkDefaults(MemChunk *chunk);
bool     LinkChunksToData(MemPool *self, MemChunk *new_chunks, u32 chunk_count, u8 *new_mem_block);
MemChunk *SkipChunks(MemChunk *chunk, u32 chunk_to_skip);
MemChunk *FindChunkSuitableToHoldMemory(MemPool *self, const size_t size);
void     SetMemoryChunkValues(MemChunk *chunk, const size_t size);
size_t   MaxValue(const size_t a, const size_t b);
void     *GetMemory(MemPool *self, const size_t mem_size);

#endif
