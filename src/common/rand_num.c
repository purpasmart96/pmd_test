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


#include "common/rand_num.h"

static pcg32_random_t pcg32_global = PCG32_INITIALIZER;

// pcg32_srandom(initstate, initseq)
// pcg32_srandom_r(rng, initstate, initseq):
//     Seed the rng.  Specified in two parts, state initializer and a
//     sequence selection constant (a.k.a. stream id)

void pcg32_srandom_r(pcg32_random_t *rng, u64 initstate, u64 initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

void srandom(u64 seed, u64 seq)
{
    pcg32_srandom_r(&pcg32_global, seed, seq);
}

// pcg32_random()
// pcg32_random_r(rng)
//     Generate a uniformly distributed 32-bit random number

u32 pcg32_random_r(pcg32_random_t *rng)
{
    u64 oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    u32 xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    u32 rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

u32 random()
{
    return pcg32_random_r(&pcg32_global);
}


// pcg32_boundedrand(bound):
// pcg32_boundedrand_r(rng, bound):
//     Generate a uniformly distributed number, r, where 0 <= r < bound

u32 pcg32_boundedrand_r(pcg32_random_t* rng, u32 bound)
{
    // To avoid bias, we need to make the range of the RNG a multiple of
    // bound, which we do by dropping output less than a threshold.
    // A naive scheme to calculate the threshold would be to do
    //
    //     uint32_t threshold = 0x100000000ull % bound;
    //
    // but 64-bit div/mod is slower than 32-bit div/mod (especially on
    // 32-bit platforms).  In essence, we do
    //
    //     uint32_t threshold = (0x100000000ull-bound) % bound;
    //
    // because this version will calculate the same modulus, but the LHS
    // value is less than 2^32.

    u32 threshold = -bound % bound;

    // Uniformity guarantees that this loop will terminate.  In practice, it
    // should usually terminate quickly; on average (assuming all bounds are
    // equally likely), 82.25% of the time, we can expect it to require just
    // one iteration.  In the worst case, someone passes a bound of 2^31 + 1
    // (i.e., 2147483649), which invalidates almost 50% of the range.  In 
    // practice, bounds are typically small and only a tiny amount of the range
    // is eliminated.
    for (;;)
    {
        u32 r = pcg32_random_r(rng);
        if (r >= threshold)
            return r % bound;
    }
}

u32 pcg32_boundedrand(u32 bound)
{
    return pcg32_boundedrand_r(&pcg32_global, bound);
}

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
