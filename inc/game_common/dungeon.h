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

typedef enum
{
    tileUnused = 0,
    tileEnd,
    tileWall,
    tileFloor,
    tileHall,
    tileStairs,
    tileLava,
    tileItem,
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


typedef struct PokemonDungeonStatus
{
    bool leader;
    u8 attack_multiplier;
    u8 sp_attack_multiplier;
    u8 defense_multiplier;
    u8 sp_defense_multiplier;
    u8 speed_multiplier;

    u16 current_belly;
    u16 max_belly;

    bool confused;
    bool burned;
    bool paralysis;
    bool sleeping;
    bool posioned;
} PokemonDungeonStatus;

typedef struct {
    int item;
    Tile tile;
} TileState;

typedef struct 
{
    TileState **tiles;
    int width;
    int height;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    //SDL_Surface* surface;
} Floor;

typedef struct Dungeon
{
    int name;
    int seed;
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

Floor *GenerateFloor(int seed, int num_items);
void PrintFloor(Floor *floor);
int IsTilePassable(Floor * floor, int x, int y);
void Dungeon_Init(struct PokemonParty *party);

void Dungeon_ShutDown();

Dungeon *GetDungeonObject(void);

typedef enum Direction Direction;
TileState GetTileInFront(Dungeon * dungeon, const int x, const int y, Direction direction);

int GetItemFromTile(Dungeon *dungeon, int x, int y);
void RemoveItemFromTile(Dungeon *dungeon, int x, int y);
void SetItemToTile(Dungeon *dungeon, int x, int y, int item);

void Dungeon_SetUpDefualtStatus(struct PokemonParty *party);
void Dungeon_SetStatusAfterStairs(struct PokemonParty *party);

void Dungeon_NextFloorLevel(Dungeon *self, struct PokemonParty *party);

#endif
