// Copyright(c) 2015 Purpasmart
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

#include <stdlib.h>

#include "common/rand_num.h"

// Assumes 0 <= max <= RAND_MAX
// Returns in the half-open interval [0, max]
u32 random_at_most(u32 max)
{
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    u32 num_bins = (u32)max + 1;
    u32 num_rand = (u32)RAND_MAX + 1;
    u32 bin_size = num_rand / num_bins;
    u32 defect = num_rand % num_bins;

    int x = 0;
    // This is carefully written not to overflow
    do
    {
        x = rand();
    } while (num_rand - defect <= (u32)x);

    // Truncated division is intentional
    return x / bin_size;
}

u32 rand_interval(u32 min, u32 max)
{
    int r = 0;
    const u32 range = 1 + max - min;
    const u32 buckets = RAND_MAX / range;
    const u32 limit = buckets * range;

   /* Create equal size buckets all in a row, then fire randomly towards
    * the buckets until you land in one of them. All buckets are equally
    * likely. If you land off the end of the line of buckets, try again.
    */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

u32 rand_interval_seed(u32 min, u32 max)
{
    int r = 0;
    const u32 range = 1 + max - min;
    const u32 buckets = RAND_MAX / range;
    const u32 limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
    * the buckets until you land in one of them. All buckets are equally
    * likely. If you land off the end of the line of buckets, try again.
    */
    do
    {
        srand(time(NULL));
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
