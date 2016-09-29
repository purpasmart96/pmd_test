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


#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "util.h"

#define MAX_MOVES  4
#define NUMBER_OF_ENEMIES 20

// Team members, including the leader
#define NUMBER_OF_TEAMMATES 4
#define CURRENT_LEADER 0


typedef enum TileRangeModes
{
    Self,
    FrontEnemy,
    EntireRoom,
    EntireRoomExceptUser,
    OneTileInRange,
    TwoTilesInRange,
    FourTiles,
    TenTiles,
} TileRangeModes;

typedef enum MoveModes
{
    Physical = 1,
    Special,
    Status,
} MoveModes;

typedef enum _MoveEffectiveness
{
    LittleEffect,
    NotVeryEffective,
    NormalEffective,
    SuperEffective,
} MoveEffectiveness;

typedef enum _MovePower
{
    PowerNone,
    PowerAll,
    PowerTwo,
    PowerThree,
    PowerFour,
    PowerFive,
    PowerSix,
    PowerSeven,
    PowerEight,
} MovePower;

typedef enum _MoveHitRatio
{
    HitRatioOne = 1,
    HitRatioTwo,
    HitRatioThree,
    HitRatioFour,
    HitRatioFive,
    HitRatioSix,
    HitRatioSeven,
    HitRatioEight,
    HitRatioAlways,
} MoveHitRatio;

typedef enum _StatusEffects
{
    NoStatusEffects,
    HighCritRate,
    MayBurn,
    MayFlinch,
    MayFrozen,
    MayParalyze,

} StatusEffects;


#endif
