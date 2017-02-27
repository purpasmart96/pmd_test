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

#include "common/rand_num.h"

#include "game_common/health.h"
#include "game_common/item.h"
#include "game_common/dungeon.h"
#include "game_common/pokemon.h"
#include "game_common/move.h"

typedef struct Pokemon_s Pokemon_t;

static const Move move_table[] =
{
    { "",             "", NoMove,       0,          0,                   0,        0,        0,  0,  0,         0,             0               },
    { "Pound",        "", Pound,        FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical, 27, 27, PowerFour, HitRatioSeven, NoStatusEffects },
    { "KarateChop",   "", KarateChop,   FrontEnemy, CAN_NOT_CUT_CORNERS, Fighting, Physical, 18, 18, PowerFive, HitRatioSeven, HighCritRate    },
    { "DoubleSlap",   "", DoubleSlap,   FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical, 10, 10, PowerTwo,  HitRatioTwo, 0 },
    { "CometPunch",   "", CometPunch,   FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical,  0,  0,  0,  0 },
    { "MegaPunch",    "", MegaPunch,    FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical,  0,  0,  0,  0 },
    { "PayDay",       "", PayDay,       FrontEnemy, CAN_NOT_CUT_CORNERS, Dark,     Physical,  0,  0,  0,  0 },
    { "FirePunch",    "", FirePunch,    FrontEnemy, CAN_NOT_CUT_CORNERS, Fire,     Physical, 13, 13, PowerSix,  HitRatioFour,  MayBurn         },
    { "IcePunch",     "", IcePunch,     FrontEnemy, CAN_NOT_CUT_CORNERS, Ice,      Physical, 12, 12, PowerSix,  HitRatioSix,   MayFrozen       },
    { "ThunderPunch", "", ThunderPunch, FrontEnemy, CAN_NOT_CUT_CORNERS, Electric, Physical, 17, 17, PowerFour, HitRatioSix,   MayParalyze     },
    { "Scratch",      "", Scratch,      FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical, 28, 28, PowerFour, HitRatioSeven, NoStatusEffects },
    { "ViceGrip",     "", ViceGrip,     FrontEnemy, CAN_NOT_CUT_CORNERS, Normal,   Physical, 22, 22, PowerFour, HitRatioSeven, NoStatusEffects },
    { "Guillotine",   "", Guillotine, 0, 0, 0, 0, 0, 0, 0 },
    { "RazorWind",    "", RazorWind, 0, 0, 0, 0, 0, 0, 0 },
    { "SwordsDance",  "", SwordsDance, 0, 0, Status, 0, 0, 0, 0 },
    { "Cut",          "", Cut, 0, 0, 0, 0, 0, 0, 0 },
    { "Gust",         "", Gust, 0, 0, 0, 0, 0, 0, 0 },
    { "WingAttack",   "", WingAttack, 0, 0, 0, 0, 0, 0, 0 },
    { "Whirlwind",    "", Whirlwind, 0, 0, 0, 0, 0, 0, 0 },
    { "Fly",          "", Fly, 0, 0, 0, 0, 0, 0, 0 },
    { "Bind",         "", Bind, 0, 0, 0, 0, 0, 0, 0 },
    { "Slam",         "", Slam, 0, 0, 0, 0, 0, 0, 0 },
    { "VineWhip",     "", VineWhip, 0, 0, 0, 0, 0, 0, 0 },
    { "Stomp",        "", Stomp, 0, 0, 0, 0, 0, 0, 0 },
    { "DoubleKick",   "", DoubleKick, 0, 0, 0, 0, 0, 0, 0 },
    { "MegaKick",     "", MegaKick, 0, 0, 0, 0, 0, 0, 0 },
    { "JumpKick",     "", JumpKick, 0, 0, 0, 0, 0, 0, 0 },
    { "RollingKick",  "", RollingKick, 0, 0, 0, 0, 0, 0, 0 },
    { "SandAttack",   "", SandAttack, 0, 0, 0, 0, 0, 0, 0 },
    { "Headbutt",     "", Headbutt, 0, 0, 0, 0, 0, 0, 0 },
    { "HornAttack",   "", HornAttack, 0, 0, 0, 0, 0, 0, 0 },
    { "FuryAttack",   "", FuryAttack, 0, 0, 0, 0, 0, 0, 0 },
    { "HornDrill",    "", HornDrill, 0, 0, 0, 0, 0, 0, 0 },
    { "Tackle",       "", Tackle, 0, 0, 0, 0, 0, 0, 0 },
    { "BodySlam",     "", BodySlam, 0, 0, 0, 0, 0, 0, 0 },
    { "Wrap",         "", Wrap, 0, 0, 0, 0, 0, 0, 0 },
    { "TakeDown",     "", TakeDown, 0, 0, 0, 0, 0, 0, 0 },
    { "DoubleEdge",   "", DoubleEdge, 0, 0, 0, 0, 0, 0, 0 },
    { "TailWhip",     "", TailWhip, 0, 0, 0, 0, 0, 0, 0 },
    { "PoisonSting",  "", PoisonSting, 0, 0, 0, 0, 0, 0, 0 },
    { "Twineedle",    "", Twineedle, 0, 0, 0, 0, 0, 0, 0 },
    { "PinMissile",   "", PinMissile, 0, 0, 0, 0, 0, 0, 0 },
    { "Leer",         "", Leer, 0, 0, 0, 0, 0, 0, 0 },
    { "Bite",         "", Bite, 0, 0, 0, 0, 0, 0, 0 },
    { "Growl",        "", Growl, 0, 0, 0, 0, 0, 0, 0 },
    { "Roar",         "", Roar, 0, 0, 0, 0, 0, 0, 0 },
    { "Sing",         "", Sing, 0, 0, 0, 0, 0, 0, 0 },
    { "Supersonic",   "", Supersonic, 0, 0, 0, 0, 0, 0, 0 },
    { "SonicBoom",    "", SonicBoom, 0, 0, 0, 0, 0, 0, 0 },
    { "Disable",      "", Disable, 0, 0, 0, 0, 0, 0, 0 },
    { "Acid",         "", Acid, 0, 0, 0, 0, 0, 0, 0 },
    { "Ember",        "", Ember, 0, 0, 0, 0, 0, 0, 0 },
    { "Flamethrower", "", Flamethrower, TenTiles, CAN_CUT_CORNERS, Fire, Special, 0, 0, 0 },
    { "Mist",         "", Mist, 0, 0, 0, 0, 0, 0, 0 },
    { "WaterGun",     "", WaterGun, 0, 0, 0, 0, 0, 0, 0 },
    { "HydroPump",    "", HydroPump, 0, 0, 0, 0, 0, 0, 0 },
    { "Surf",         "", Surf, 0, 0, 0, 0, 0, 0, 0 },
    { "IceBeam",      "", IceBeam, 0, 0, 0, 0, 0, 0, 0 },
    { "Blizzard",     "", Blizzard, 0, 0, 0, 0, 0, 0, 0 },
    { "Psybeam",      "", Psybeam, 0, 0, 0, 0, 0, 0, 0 },
    { "BubbleBeam",   "", BubbleBeam, 0, 0, 0, 0, 0, 0, 0 },
    { "AuroraBeam",   "", AuroraBeam, 0, 0, 0, 0, 0, 0, 0 },
    { "HyperBeam",    "", HyperBeam, 0, 0, 0, 0, 0, 0, 0 },
    { "Peck",         "", Peck, 0, 0, 0, 0, 0, 0, 0 },
    { "DrillPeck",    "", DrillPeck, 0, 0, 0, 0, 0, 0, 0 },
    { "Submission",   "", Submission, 0, 0, 0, 0, 0, 0, 0 },
    { "LowKick",      "", LowKick, 0, 0, 0, 0, 0, 0, 0 },
    { "Counter",      "", Counter, 0, 0, 0, 0, 0, 0, 0 },
    { "SeismicToss",  "", SeismicToss, 0, 0, 0, 0, 0, 0, 0 },
    { "Strength",     "", Strength, 0, 0, 0, 0, 0, 0, 0 },
    { "Absorb",       "", Absorb, 0, 0, 0, 0, 0, 0, 0 },
    { "MegaDrain",    "", MegaDrain, 0, 0, 0, 0, 0, 0, 0 },
    { "LeechSeed",    "", LeechSeed, 0, 0, 0, 0, 0, 0, 0 },
    { "Growth",       "", Growth, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0, 0, 0, 0, 0 },
    { "", "", NoMove, 0, 0, 0,   0, 0, 0, 0, 0, 0 },
};

static const MoveEffectiveness move_effectiveness_combos[4][4] =
{
    { LittleEffect,     LittleEffect,     LittleEffect,     NotVeryEffective },
    { LittleEffect,     NotVeryEffective, NotVeryEffective, NormalEffective  },
    { LittleEffect,     NotVeryEffective, NormalEffective,  SuperEffective   },
    { NotVeryEffective, NormalEffective,  SuperEffective,   SuperEffective   },
};


bool IsMovesEmpty(MoveSet *moves)
{
	return moves->size == 0;
}

bool IsMovesFull(MoveSet *moves)
{
	return moves->size == MAX_MOVES;
}

Move GetMoveFromTable(MoveNames the_move)
{
    return move_table[the_move];
}

void SetMoveToPokemon(Pokemon_t *pokemon, MoveNames the_move)
{
    Move move = GetMoveFromTable(the_move);

    if (!IsMovesFull(pokemon->moves))
    {
        pokemon->moves->move[pokemon->moves->size++] = move;
    }
    else
    {
    }

}

void UseMove(MoveNames the_move)
{
    Move move = GetMoveFromTable(the_move);

    switch (move.status_effects)
    {
    }

}

void CalculateAccuracy()
{
}


void CalculateDamage(MoveNames the_move, Pokemon_t *attacker, Pokemon_t *defender)
{
    Move move = GetMoveFromTable(the_move);

    double N = 0;
    double A = 0;
    double D = 0;
    double E = 0;
    int damage = 0;

    if (move.mode == Physical)
    {
        N = 340 / 256;
        A = 75; //attacker->sp_attack;
        D = defender->defense;
        E = (log((((A - D) / 8) + attacker->level + 50) * 10) * 50) - 311;

        if (move.type == attacker->primary_type || attacker->sub_type)
        {
            E *= 1.5;
        }

        damage = (((A + move.power) * 39168 / 65536) - (D / 2) + E) / N;
        printf("E = %d\n", E);
    }
    else
    {
        N = 340 / 256;
        A = 75; //attacker->attack;
        D = defender->sp_defense;
        E = (log((((A - D) / 8) + attacker->level + 50) * 10) * 50) - 311;

        if (move.type == attacker->primary_type || attacker->sub_type)
        {
            E *= 1.5;
        }

        damage = (((A + move.power) * 39168 / 65536) - (D / 2) + E) / N;
    }

    damage *= E;
    u32 n = rand_interval(0, 16383);
    printf("n = %d\n", n);
    int rng_multiplier = (57344 + n) / 65536;
    printf("rng_multiplier = %d\n", rng_multiplier);
    int final_multiplier = round(rng_multiplier);
    damage *= final_multiplier;

    DecreaseHealth(defender, damage);
}


int GetMoveEffectiveness(Move move, Type type, bool isGhostRevealed, bool isGravity)
{
    if (isGhostRevealed && type == Ghost && (move.type == Normal || move.type == Fighting))
    {
        return 1;
    }
    else if (isGravity && type == Flying && move.type == Ground)
    {
        return 1;
    }
    else if (move.name == "FreezeDry" && type == Water)
    {
        return 2;
    }
    else if (move.name == "Flying Press")
    {
        //return typeChart["Fighting"][type] * typeChart["Flying"][type];
    }
    else
    {
        //return typeChart[move.type][type];
    }
}
