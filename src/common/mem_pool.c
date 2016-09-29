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


#include "common/mem_pool.h"
#include <assert.h>

MemPool *mempool_New(const size_t pool_size, const size_t mem_chunk_size, const size_t min_mem_size_alloc, bool set_mem_data)
{
    MemPool *mem_pool = calloc(1, sizeof(*mem_pool));
    mem_pool->first_chunk = NULL;
    mem_pool->last_chunk = NULL;
    mem_pool->cursor_chunk = NULL;

    mem_pool->total_mem_pool_size = 0;
    mem_pool->used_mem_pool_size = 0;
    mem_pool->free_mem_pool_size = 0;

    mem_pool->mem_chunk_size = mem_chunk_size;
    mem_pool->mem_chunk_count = 0;
    mem_pool->object_count = 0;

    mem_pool->set_mem_data = set_mem_data;
    mem_pool->min_mem_size_alloc = min_mem_size_alloc;

    AllocMem(mem_pool, pool_size);
    return mem_pool;
}

void DeallocateAllChunks(MemPool *self)
{
}

u32 CalculateNeededChunks(MemPool *self, const size_t size)
{
    float f = (float)((float)size / (float)self->mem_chunk_size);
    return ((u32)ceil(f));
}

size_t CalculateBestMemoryBlockSize(MemPool *self, const size_t size)
{
    u32 needed = CalculateNeededChunks(self, size);
    return (size_t)(needed * self->mem_chunk_size);
}

bool AllocMem(MemPool *self, const size_t mem_size)
{
    size_t best_mem_block_size = CalculateBestMemoryBlockSize(self, mem_size);
    // allocate from Operating System
    u8 *mem_block = malloc(best_mem_block_size);
    u32 needed_chunks = CalculateNeededChunks(self, mem_size);
    // allocate Chunk-Array to Manage the Memory
    MemChunk *new_chunks = malloc(sizeof(*new_chunks) * needed_chunks);
    assert(((mem_block) && (new_chunks)) && "Error : System ran out of Memory");

    return LinkChunksToData(self, new_chunks, needed_chunks, mem_block);
}

bool RecalcChunkMemorySize(MemPool *self, MemChunk *chunk, u32 chunk_count)
{
    u32 mem_offset = 0;
    for (u32 i = 0; i < chunk_count; i++)
    {
        if (chunk)
        {
            mem_offset = (i * ((u32)self->mem_chunk_size));
            chunk->capacity = (((u32)self->total_mem_pool_size) - mem_offset);
            chunk = chunk->next;
        }
        else
        {
            assert(false && "Error : chunk == NULL");
            return false;
        }
    }
    return true;
}

MemChunk *SetChunkDefaults(MemChunk *chunk)
{
    if (chunk != NULL)
    {
        chunk->data = NULL;
        chunk->capacity = 0;
        chunk->size = 0;
        chunk->is_alloc_chunk = false;
        chunk->next = NULL;
    }
    return chunk;
}

bool LinkChunksToData(MemPool *self, MemChunk *new_chunks, u32 chunk_count, u8 *new_mem_block)
{
    MemChunk *new_chunk = NULL;
    u32 mem_offset = 0;
    bool bAllocationChunkAssigned = false;
    for (u32 i = 0; i < chunk_count; i++)
    {
        if (!self->first_chunk)
        {
            self->first_chunk = SetChunkDefaults(&new_chunks[0]);
            self->last_chunk = self->first_chunk;
            self->cursor_chunk = self->first_chunk;
        }
        else
        {
            new_chunk = SetChunkDefaults(&new_chunks[i]);
            self->last_chunk->next = new_chunk;
            self->last_chunk = new_chunk;
        }

        mem_offset = (i * (u32)self->mem_chunk_size);
        self->last_chunk->data = &new_mem_block[mem_offset];

        // The first Chunk assigned to the new Memory-Block will be
        // a "AllocationChunk". This means, this Chunks stores the
        // "original" Pointer to the MemBlock and is responsible for
        // "free()"ing the Memory later....
        if (!bAllocationChunkAssigned)
        {
            self->last_chunk->is_alloc_chunk = true;
            bAllocationChunkAssigned = true;
        }
    }
    return RecalcChunkMemorySize(self, new_chunks, chunk_count);
}

MemChunk *SkipChunks(MemChunk *chunk, u32 chunk_to_skip)
{
    MemChunk* current_chunk = chunk;
    for (u32 i = 0; i < chunk_to_skip; i++)
    {
        if (current_chunk != NULL)
        {
            current_chunk = current_chunk->next;
        }
        else
        {
            break;
        }
    }
    return current_chunk;
}

MemChunk *FindChunkSuitableToHoldMemory(MemPool *self, const size_t size)
{
    u32 chunk_to_skip = 0;
    MemChunk *chunk = self->cursor_chunk;
    for (u32 i = 0; i < self->mem_chunk_count; i++)
    {
        if (chunk != NULL)
        {
            if (chunk == self->last_chunk)
            {
                chunk = self->first_chunk;
            }
            if (chunk->capacity >= size && chunk->size == 0)
            {
                self->cursor_chunk = chunk;
                return chunk;
            }
            chunk_to_skip = CalculateNeededChunks(self, chunk->size);
            if (chunk_to_skip == 0)
                chunk_to_skip = 1;
            chunk = SkipChunks(chunk, chunk_to_skip);
        }
    }
    return NULL;
}

void SetMemoryChunkValues(MemChunk *chunk, const size_t size)
{
    if (chunk != NULL)
    {
        chunk->size = size;
    }
}

size_t MaxValue(const size_t a, const size_t b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

void *GetMemory(MemPool *self, const size_t mem_size)
{
    size_t best_mem_block_size = CalculateBestMemoryBlockSize(self, mem_size);
    MemChunk *chunk = NULL;
    while (!chunk)
    {
        // Is a Chunks available to hold the requested amount of Memory ?
        chunk = FindChunkSuitableToHoldMemory(self, best_mem_block_size);
        if (chunk == NULL)
        {
            best_mem_block_size = MaxValue(best_mem_block_size, CalculateBestMemoryBlockSize(self, self->min_mem_size_alloc));
            AllocMem(self, best_mem_block_size);
        }
    }
    self->used_mem_pool_size += best_mem_block_size;
    self->free_mem_pool_size -= best_mem_block_size;

    SetMemoryChunkValues(chunk, best_mem_block_size);
    return (void*)chunk->data;
}
