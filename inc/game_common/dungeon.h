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


#ifndef _DUNGEON_STATE_H_
#define _DUNGEON_STATE_H_

#include "util.h"

#include "common/vec.h"

typedef enum
{
    tileUnused = 0,
    tileEnd,
    tileWall,
    tileWallLeft,
    tileWallRight,
    tileFloor,
    tileHall,
    tileStairs,
    tileLava,
    tileLavaBorderUp,
    tileLavaBorderRightUp,
    tileLavaBorderLeftUp,
    tileLavaBorderBottom,
    tileLavaBorderBottomRight,
    tileLavaBorderBottomLeft,
    tileLavaBorderMiddleLeft,
    tileLavaBorderMiddleRight,
    tileItem,
    tilePlayer,
} Tile;

typedef enum WeatherState
{
    WeatherClear,
    WeatherClouds,
    WeatherFog,
    WeatherRain,
    WeatherSun,
    WeatherSnow,
    WeatherHail,
    WeatherSand,
} WeatherState;

typedef struct {
    int item;
    Tile tile;
} TileState;

typedef struct
{
    TileState **tiles;
    Tile previous_tile_type_before_player;
    int width;
    int height;
    ivec2 player_spawn_point;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} Floor;

typedef struct Dungeon
{
    int name;
    u64 seed;
    int difficulty;
    int *floor_seeds;
    int total_floors;
    int floor_counter;
    int num_items;
    int num_enemies;
    int num_traps;
    int current_floor_level;
    WeatherState current_weather;
    Floor *floor;
} Dungeon;

Floor *GenerateFloor(int num_items);
void PrintFloor(Floor *floor);
void PrintFloorFixed(Floor * floor);
int IsTilePassable(Floor * floor, int x, int y);
int IsTilePassableByType(Floor * floor, Tile tile);
void Dungeon_Init(struct PokemonParty *party);

void Dungeon_ShutDown();

Dungeon *GetDungeonObject(void);

typedef enum Direction Direction;
TileState GetTileInFront(Dungeon *dungeon, const ivec2 coords, Direction direction);

int GetItemFromTile(Dungeon *dungeon, int x, int y);
void RemoveItemFromTile(Dungeon *dungeon, int x, int y);
void SetItemToTile(Dungeon *dungeon, int x, int y, int item);

void SetPlayerPreviousPos(ivec2 coords);

void SetPlayerTile(Dungeon *dungeon, ivec2 coords);
//void SetPlayerTile(Dungeon * dungeon, int x, int y);

ivec2 GetPlayerSpawnPoint(Dungeon *dungeon);

void Dungeon_SetUpDefualtStatus(struct PokemonParty *party);
void Dungeon_SetStatusAfterStairs(struct PokemonParty *party);

void Dungeon_NextFloorLevel(Dungeon *self, struct PokemonParty *party);

#endif

