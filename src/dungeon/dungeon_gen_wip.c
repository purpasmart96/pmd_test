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

#include "dungeon/dungeon_gen.h"
#include "common/rand_num.h"
#include <assert.h>


void SetCell(Map *map, int x, int y, Tile celltype)
{
    assert(IsXInBounds(map, x));
    assert(IsYInBounds(map, y));

    map->data[x + map->size_x * y] = celltype;
}

int GetCell(Map *map, int x, int y)
{
    return map->data[x + map->size_x * y];
}

int GetRand(u64 rng, int min, int max)
{
    time_t seed;
    seed = time(NULL) + rng;
    rng = seed;

    srand(seed);

    int n = max - min + 1;
    int i = rand() % n;

    if (i < 0)
        i = -i;

    return min + i;
}

Direction GetRandomDirection(u64 rng)
{
    return (Direction)GetRand(rng, 0, 3);
}

Map *Generate(Dungeon dungeon)
{
    u64 rng = (dungeon.Seed);
    Map *map = malloc(sizeof(Map));
    map->size_x = dungeon.size_x;
    map->size_y = dungeon.size_y;
    map->data = calloc(0, sizeof(int) * (dungeon.size_x * dungeon.size_y));

    MakeDungeon(dungeon, map, rng);
    return map;
}

bool IsXInBounds(Map *map, int x)
{
    return x >= 0 && x < map->size_x;
}

bool IsYInBounds(Map *map, int y)
{
    return y >= 0 && y < map->size_y;
}

bool IsAreaUnused(Map *map, int xStart, int yStart, int xEnd, int yEnd)
{
    assert(IsXInBounds(map, xStart) && IsXInBounds(map, xEnd));
    assert(IsYInBounds(map, yStart) && IsYInBounds(map, yEnd));

    assert(xStart <= xEnd);
    assert(yStart <= yEnd);

    for (int y = yStart; y != yEnd + 1; ++y)
    {
        for (int x = xStart; x != xEnd + 1; ++x)
        {
            if (GetCell(map, x, y) != Unused)
            {
                return false;
            }
        }
    }
    return true;
}

bool IsAdjacent(Map *map, int x, int y, Tile tile)
{
    assert(IsXInBounds(map, x - 1) && IsXInBounds(map, x + 1));
    assert(IsYInBounds(map, y - 1) && IsYInBounds(map, y + 1));

    //bool value_x = GetCell(map, x - 1, y) == tile || GetCell(map, x + 1, y) == tile;

    return GetCell(map, x - 1, y) == tile || GetCell(map, x + 1, y) == tile || GetCell(map, x, y - 1) == tile || GetCell(map, x, y + 1) == tile;;
}


void SetCells(Map *map, int xStart, int yStart, int xEnd, int yEnd, Tile cellType)
{
    assert(IsXInBounds(map, xStart) && IsXInBounds(map, xEnd));
    assert(IsYInBounds(map, yStart) && IsYInBounds(map, yEnd));

    assert(xStart <= xEnd);
    assert(yStart <= yEnd);

    for (int y = yStart; y != yEnd + 1; ++y)
    {
        for (int x = xStart; x != xEnd + 1; ++x)
        {
            SetCell(map, x, y, cellType);
        }
    }
}

bool MakeCorridor(Map *map, u64 rng, int x, int y, int maxLength, Direction direction)
{
    assert(x >= 0 && x < size_x);
    assert(y >= 0 && y < size_y);

    assert(maxLength > 0 && maxLength <= MAX(size_x, size_y));

    int length = GetRand(rng, 2, maxLength);

    int xStart = x;
    int yStart = y;

    int xEnd = x;
    int yEnd = y;

    switch (direction)
    {
        case North:
        yStart = y - length;
        break;
	
        case East:
        xEnd = x + length;
        break;

        case South:
        yEnd = y + length;
        break;

        case West:
        xStart = x - length;
        break;

        default:
        break;
    }

/*
    if (direction == North)
    {
        yStart = y - length;
    }
    else if (direction == East)
    {
        xEnd = x + length;
    }
    else if (direction == South)
    {
        yEnd = y + length;
    }
    else if (direction == West)
    {
        xStart = x - length;
    }
*/
    
    if (!IsXInBounds(map, xStart) || !IsXInBounds(map, xEnd) || !IsYInBounds(map, yStart) || !IsYInBounds(map, yEnd))
    {
        return false;
    }
    if (!IsAreaUnused(map, xStart, yStart, xEnd, yEnd))
    {
        return false;
    }

    SetCells(map, xStart, yStart, xEnd, yEnd, Corridor);

    //std::cout << "Corridor: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

    return true;
}

static void RoomDirection(int *yStart, int *xStart)
{
    
}

bool MakeRoom(Map *map, u64 rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction)
{
    // Minimum room size of 6x6 tiles (3x3 for walking on, the rest is walls)
    int xLength = GetRand(rng, 4, xMaxLength);
    int yLength = GetRand(rng, 4, yMaxLength);

    int xStart = x;
    int yStart = y;

    int xEnd = x;
    int yEnd = y;

    switch (direction)
    {
        case North:
        {
            yStart = y - yLength;
            xStart = x - xLength / 2;
            xEnd = x + (xLength + 1) / 2;
            break;
        }
        case East:
        {
            yStart = y - yLength / 2;
            yEnd = y + (yLength + 1) / 2;
            xEnd = x + xLength;
            break;
        }
        case South:
        {
            yEnd = y + yLength;
            xStart = x - xLength / 2;
            xEnd = x + (xLength + 1) / 2;
            break;
        }
        case West:
        {
            yStart = y - yLength / 2;
            yEnd = y + (yLength + 1) / 2;
            xStart = x - xLength;
            break;
        }
        
        default:
        break;
    }

/*     if (direction == North)
    {
        yStart = y - yLength;
        xStart = x - xLength / 2;
        xEnd = x + (xLength + 1) / 2;
    }
    else if (direction == East)
    {
        yStart = y - yLength / 2;
        yEnd = y + (yLength + 1) / 2;
        xEnd = x + xLength;
    }
    else if (direction == South)
    {
        yEnd = y + yLength;
        xStart = x - xLength / 2;
        xEnd = x + (xLength + 1) / 2;
    }
    else if (direction == West)
    {
        yStart = y - yLength / 2;
        yEnd = y + (yLength + 1) / 2;
        xStart = x - xLength;
    } */

    if (!IsXInBounds(map, xStart) || !IsXInBounds(map, xEnd) || !IsYInBounds(map, yStart) || !IsYInBounds(map, yEnd))
        return false;

    if (!IsAreaUnused(map, xStart, yStart, xEnd, yEnd))
        return false;

    SetCells(map, xStart, yStart, xEnd, yEnd, DirtWall);
    SetCells(map, xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, DirtFloor);

    //std::cout << "Room: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

    return true;
}

bool MakeFeature(Dungeon dungeon, Map *map, u64 rng, int x, int y, int xmod, int ymod, Direction direction)
{
    // Choose what to build
    int chance = GetRand(rng, 0, 100);

    if (chance <= dungeon.ChanceRoom)
    {
        if (MakeRoom(map, rng, x + xmod, y + ymod, 8, 6, direction))
        {
            SetCell(map, x, y, Door);

            // Remove wall next to the door.
            SetCell(map, x + xmod, y + ymod, DirtFloor);

            return true;
        }

        return false;
    }
    else
    {
        if (MakeCorridor(map, rng, x + xmod, y + ymod, 6, direction))
        {
            SetCell(map, x, y, Door);

            return true;
        }

        return false;
    }
}

bool MakeFeatures(Dungeon dungeon, Map *map, u64 rng)
{
    int tries = 0;
    int maxTries = 1000;

    for (; tries != maxTries; ++tries)
    {
        // Pick a random wall or corridor tile.
        // Make sure it has no adjacent doors (looks weird to have doors next to each other).
        // Find a direction from which it's reachable.
        // Attempt to make a feature (room or corridor) starting at this point.

        int x = GetRand(rng, 1, dungeon.size_x - 2);
        int y = GetRand(rng, 1, dungeon.size_y - 2);

        if (GetCell(map, x, y) != DirtWall && GetCell(map, x, y) != Corridor)
            continue;

        if (IsAdjacent(map, x, y, Door))
            continue;

        if (GetCell(map, x, y + 1) == DirtFloor || GetCell(map, x, y + 1) == Corridor)
        {
            if (MakeFeature(dungeon, map, rng, x, y, 0, -1, North))
                return true;
        }
        else if (GetCell(map, x - 1, y) == DirtFloor || GetCell(map, x - 1, y) == Corridor)
        {
            if (MakeFeature(dungeon, map, rng, x, y, 1, 0, East))
                return true;
        }
        else if (GetCell(map, x, y - 1) == DirtFloor || GetCell(map, x, y - 1) == Corridor)
        {
            if (MakeFeature(dungeon, map, rng, x, y, 0, 1, South))
                return true;
        }
        else if (GetCell(map, x + 1, y) == DirtFloor || GetCell(map, x + 1, y) == Corridor)
        {
            if (MakeFeature(dungeon, map, rng, x, y, -1, 0, West))
                return true;
        }
    }

    return false;
}

bool MakeStairs(Dungeon dungeon, Map *map, u64 rng, Tile tile)
{
    int tries = 0;
    int maxTries = 10000;

    for (; tries != maxTries; ++tries)
    {
        int x = GetRand(rng, 1, dungeon.size_x - 2);
        int y = GetRand(rng, 1, dungeon.size_y - 2);

        if (!IsAdjacent(map, x, y, DirtFloor) && !IsAdjacent(map, x, y, Corridor))
            continue;

        if (IsAdjacent(map, x, y, Door))
            continue;

        SetCell(map, x, y, tile);

        return true;
    }

    return false;
}

bool MakeDungeon(Dungeon dungeon, Map *map, u64 rng)
{
    // Make one room in the middle to start things off.
    MakeRoom(map, rng, dungeon.size_x / 2, dungeon.size_y / 2, 8, 6, GetRandomDirection(rng));

    for (int features = 1; features != dungeon.MaxFeatures; ++features)
    {
        if (!MakeFeatures(dungeon, map, rng))
        {
            //std::cout << "Unable to place more features (placed " << features << ")." << std::endl;
            break;
        }
    }

    if (!MakeStairs(dungeon, map, rng, UpStairs))
    {
        //std::cout << "Unable to place up stairs." << std::endl;
        printf("Unable to place up stairs.\n");
    }

    if (!MakeStairs(dungeon, map, rng, DownStairs))
    {
        printf("Unable to place down stairs.\n");
        //std::cout << "Unable to place down stairs." << std::endl;
    }


    return true;
}


void Print(Map map)
{
    // TODO: proper ostream iterator.
    // TODO: proper lookup of character from enum.

    for (int y = 0; y != map->size_y; y++)
    {
        for (int x = 0; x != map->size_x; x++)
        {
            switch (GetCell(map, x, y))
            {
            case Unused:
                printf(" ");
                //std::cout << " ";
                break;
            case DirtWall:
                printf("#");
                //std::cout << "#";
                break;
            case DirtFloor:
                printf(".");
                //std::cout << ".";
                break;
            case Corridor:
                printf(".");
                //std::cout << ".";
                break;
            case Door:
                printf(".");
                //std::cout << "+";
                break;
            case UpStairs:
                printf("<");
                //std::cout << "<";
                break;
            case DownStairs:
                printf(".");
                //std::cout << ">";
                break;
            };
        }
        printf("\n");
    }
    printf("\n");
}

void dungeon_main()
{
    
    Dungeon dungeon;
    dungeon.Seed = 3905838349;
    dungeon.size_x = 80;
    dungeon.size_y = 25;
    dungeon.MaxFeatures = 100;
    dungeon.ChanceRoom = 75;
    dungeon.ChanceCorridor = 25;
    Map map = Generate(dungeon);
    Print(map);
    free(map->data);
}
