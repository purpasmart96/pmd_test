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

#include "game_common/move_manager.h"

char *GetMoveNameFromEnum(Move move)
{
    char *move_name = NULL;
    switch (move.move_name)
    {
    case NoMove:
    {
        move_name = "NoMove";
        break;
    }
    case Pound:
    {
        move_name = "Pound";
        break;
    }
    case KarateChop:
    {
        move_name = "KarateChop";
        break;
    }
    case DoubleSlap:
    {
        move_name = "DoubleSlap";
        break;
    }
    case CometPunch:
    {
        move_name = "CometPunch";
        break;
    }
    case MegaPunch:
    {
        move_name = "MegaPunch";
        break;
    }
    case PayDay:
    {
        move_name = "PayDay";
        break;
    }
    case FirePunch:
    {
        move_name = "FirePunch";
        break;
    }
    case IcePunch:
    {
        move_name = "IcePunch";
        break;
    }
    case ThunderPunch:
    {
        move_name = "ThunderPunch";
        break;
    }
    case Scratch:
    {
        move_name = "Scratch";
        break;
    }
    case ViceGrip:
    {
        move_name = "ViceGrip";
        break;
    }
    case Guillotine:
    {
        move_name = "Guillotine";
        break;
    }
    case RazorWind:
    {
        move_name = "RazorWind";
        break;
    }
    case SwordsDance:
    {
        move_name = "SwordsDance";
        break;
    }
    case Cut:
    {
        move_name = "Cut";
        break;
    }
    case Gust:
    {
        move_name = "";
        break;
    }
    case WingAttack:
    {
        move_name = "";
        break;
    }
    case Whirlwind:
    {
        move_name = "";
        break;
    }
    case Fly:
    {
        move_name = "";
        break;
    }
    case Bind:
    {
        move_name = "";
        break;
    }
    case Slam:
    {
        move_name = "Slam";
        break;
    }
    case VineWhip:
    {
        move_name = "VineWhip";
        break;
    }
    case Stomp:
    {
        move_name = "Stomp";
        break;
    }
    case DoubleKick:
    {
        move_name = "DoubleKick";
        break;
    }
    case MegaKick:
    {
        move_name = "MegaKick";
        break;
    }
    case JumpKick:
    {
        move_name = "JumpKick";
        break;
    }
    case RollingKick:
    {
        move_name = "RollingKick";
        break;
    }
    case SandAttack:
    {
        move_name = "SandAttack";
        break;
    }
    case Headbutt:
    {
        move_name = "Headbutt";
        break;
    }

    default:
        printf("Haven't added Move %d\n", move.move_name);
        break;
    }

    return move_name;
}
