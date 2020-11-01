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
#include "common/vec.h"

#include "game/item.h"
#include "game/hunger.h"
#include "game/pokemon.h"
#include "game/dungeon.h"

#define MIN_ROOM_BUFFER 7
#define MAX_PLACEMENT_FAILURES 100

static int difficulty;
static int floor_w;
static int floor_h;
static int min_room_dimension;
static int max_room_dimension;
static int total_corridor_length;
static int min_num_items;
static int max_num_items;
static int previous_pos_x;
static int previous_pos_y;


static Dungeon *dungeon;

void Dungeon_Init(PokemonParty *party, u32 seed)
{
    dungeon = calloc(1, sizeof(*dungeon));
    char *name = "TestDungeon";
    //strlcpy(dungeon->name, name, sizeof(name));
    dungeon->name = "TestDungeon";
    dungeon->seed = seed;
    srand(seed);

    // Calculate difficulty variables
    min_num_items = 5;
    max_num_items = 30;
    previous_pos_x = 0;
    previous_pos_y = 0;
    dungeon->difficulty = 5;
    floor_w = 80; // x
    floor_h = 60; // y
    min_room_dimension = 5;
    max_room_dimension = 16;
    total_corridor_length = floor_w * floor_h / 10;

    dungeon->total_floors = 10;
    dungeon->current_floor_level = 0;

    // Generate floor seeds in advance
    dungeon->floor_seeds = malloc(sizeof(int) * dungeon->total_floors);
    for (int i = 0; i < dungeon->total_floors; i++)
    {
        dungeon->floor_seeds[i] = rand();
    }

    int num_items = rand_interval_seed(&dungeon->seed, min_num_items, max_num_items);
    dungeon->floor = GenerateFloor(dungeon->floor_seeds[0], num_items);

    PrintFloorFixed(dungeon->floor);

}

void GenerateNewFloor(int min_num_items, int max_num_items)
{
    int num_items = rand_interval_seed(&dungeon->seed, min_num_items, max_num_items);
    dungeon->floor = GenerateFloor(dungeon->floor_seeds[dungeon->current_floor_level + 1], num_items);
}

void Dungeon_ShutDown()
{
    for (int x = 0; x < floor_w; x++)
    {
        free(dungeon->floor->tiles[x]);
    }

    free(dungeon->floor->tiles);
    free(dungeon->floor_seeds);
    free(dungeon->floor);
    free(dungeon);
}

Dungeon *GetDungeonObject(void)
{
    return dungeon;
}

TileState GetTileInFront(Dungeon *dungeon, const ivec2 coords, Direction direction)
{
    int temp_x = coords.x;
    int temp_y = coords.y;

    switch (direction)
    {
        case North:
            temp_y++;
            break;
        case East:
            temp_x++;
            break;
        case South:
            temp_y--;
            break;
        case West:
            temp_x--;
            break;

        default:
            break;
    }

    return dungeon->floor->tiles[temp_x][temp_y];
}

static int GetTile(Floor *floor, int x, int y)
{
    if (x < 0 || x >= floor->width || y < 0 || y >= floor->height)
    {
        return tileEnd;
    }
    return floor->tiles[x][y].tile;
}

/**
* Returns tile_wall if the tile is a boundary. Used to equate boundaries and walls
* for graphics purposes
*/
static int GetTileBoundaryAsWall(Floor *floor, int x, int y)
{
    if (x < 0 || x >= floor->width || y < 0 || y >= floor->height)
    {
        return tileWall;
    }
    if (floor->tiles[x][y].tile == tileEnd)
    {
        return tileWall;
    }
    return floor->tiles[x][y].tile;
}

static int SetTile(Floor *floor, int x, int y, int tile)
{
    if (x < 0 || x >= floor->width || y < 0 || y >= floor->height)
    {
        return 0;
    }
    floor->tiles[x][y].tile = tile;
    return 1;
}

int GetItemFromTile(Dungeon *dungeon, int x, int y)
{
    return dungeon->floor->tiles[x][y].item;
}

void RemoveItemFromTile(Dungeon *dungeon, int x, int y)
{
    SetItemToTile(dungeon, x, y, None);
    SetTile(floor, x, y, tileFloor);
}

void SetItemToTile(Dungeon *dungeon, int x, int y, int item)
{
    dungeon->floor->tiles[x][y].item = item;
}

static void RestoreOldPreviousTile(Floor *floor, int x, int y)
{
    SetTile(floor, x, y, floor->previous_tile_type_before_player);
}

static void SetNewPreviousTile(Floor *floor, ivec2 coords)
{
    floor->previous_tile_type_before_player = GetTile(floor, coords.x, coords.y);
}

void SetPlayerPreviousPos(ivec2 coords)
{
    previous_pos_x = coords.x;
    previous_pos_y = coords.y;
}

void SetPlayerTile(Dungeon *dungeon, ivec2 coords)
{
    if (previous_pos_x || previous_pos_y)
    {
        RestoreOldPreviousTile(dungeon->floor, previous_pos_x, previous_pos_y);
    }

    SetNewPreviousTile(dungeon->floor, coords);
    SetTile(dungeon->floor, coords.x, coords.y, tilePlayer);
    //PrintFloorFixed(dungeon->floor);
}

ivec2 GetPlayerSpawnPoint(Dungeon *dungeon)
{
    return dungeon->floor->player_spawn_point;
}

static void SetPlayerSpawnPoint(Floor *floor, ivec2 coords)
{
    floor->player_spawn_point.x = coords.x;
    floor->player_spawn_point.y = coords.y;
    SetNewPreviousTile(floor, coords);
    //SetTile(dungeon->floor, coords.x, coords.y, tilePlayer);
    floor->tiles[coords.x][coords.y].tile = tilePlayer;
}

bool IsAdjacent(Floor *floor, int x, int y, Tile tile)
{
    return GetTile(floor, x - 1, y) == tile || GetTile(floor, x + 1, y) == tile || GetTile(floor, x, y - 1) == tile || GetTile(floor, x, y + 1) == tile;
}


static Tile GetCorrectLavaTileType(Floor *floor, int x, int y)
{
    // TODO: Clean up this shit code

    Tile left = GetTile(floor, x - 1, y);
    Tile right = GetTile(floor, x + 1, y);

    Tile up = GetTile(floor, x, y + 1);
    Tile up_right = GetTile(floor, x + 1, y + 1);
    Tile up_left = GetTile(floor, x - 1, y + 1);

    Tile bottom = GetTile(floor, x, y - 1);
    Tile bottom_right = GetTile(floor, x + 1, y - 1);
    Tile bottom_left = GetTile(floor, x - 1, y - 1);
   
    if (left == tileFloor || left == tileHall)
        return tileLavaBorderMiddleLeft;

    if (right == tileFloor || right == tileHall)
        return tileLavaBorderMiddleRight;

    if (up_left == tileFloor && up != tileFloor || up_left == tileHall &&  up != tileHall)
        return tileLavaBorderLeftUp;

    if (up == tileFloor || up == tileHall)
        return tileLavaBorderUp;

    if (up_right == tileFloor && up != tileFloor || up_right == tileHall &&  up != tileHall)
        return tileLavaBorderRightUp;

    if (bottom_left == tileFloor && bottom != tileFloor || bottom_left == tileHall &&  bottom != tileHall)
        return tileLavaBorderBottomLeft;

    if (bottom == tileFloor || up == tileHall)
        return tileLavaBorderBottom;

    if (bottom_right == tileFloor && bottom != tileFloor || bottom_right == tileHall &&  bottom != tileHall)
        return tileLavaBorderBottomRight;


    return tileLava;
}


void PrintFloor(Floor *floor)
{
    char *strings[] =
    {
        " ",
        "=",
        "=",
        "=",
        "=",
        ".",
        ".",
        "X",
        "n",
        "*",
        "%"
    };

    for (int y = 0; y < floor->height; y++)
    {
        for (int x = 0; x < floor->width; x++)
        {
            int tile = GetTile(floor, x, y);
            char *tile_char = strings[tile];
            printf("%s", tile_char);
        }
        printf("\n");
    }
}

void PrintFloorFixed(Floor *floor)
{
    char *strings[] =
    {
        " ",
        "=",
        "=",
        "=",
        "=",
        ".",
        ".",
        "X",
        "n",
        "n",
        "n",
        "n",
        "n",
        "n",
        "n",
        "n",
        "n",
        "*",
        "%"
    };


    for (int y = floor->height; y > 0; y--)
    {
        for (int x = 0; x < floor->width; x++)
        {
            Tile tile = GetTile(floor, x, y);
            char *tile_char = strings[tile];
            printf("%s", tile_char);
        }
        printf("\n");
    }
}

int AddCorridor(Floor *floor, int ax, int ay, int bx, int by)
{
    if (ax == bx && ay == by)
    {
        return 0;
    }
    int x_diff = ax > bx ? ax - bx : bx - ax;
    int y_diff = ay > by ? ay - by : by - ay;
    int mid;
    if (x_diff > y_diff)
    {
        mid = ax < bx ? rand_interval(ax, bx) : rand_interval(bx, ax);
        while (ax != mid)
        {
            SetTile(floor, ax, ay, tileHall);
            ax += ax < mid ? +1 : -1;
        }
        while (bx != mid)
        {
            SetTile(floor, bx, by, tileHall);
            bx += bx < mid ? +1 : -1;
        }
        while (ay != by)
        {
            SetTile(floor, ax, ay, tileHall);
            ay += ay < by ? +1 : -1;
        }
        SetTile(floor, ax, ay, tileHall);
    }
    else
    {
        mid = ay < by ? rand_interval(ay, by) : rand_interval(by, ay);
        while (ay != mid)
        {
            SetTile(floor, ax, ay, tileHall);
            ay += ay < mid ? +1 : -1;
        }
        while (by != mid)
        {
            SetTile(floor, bx, by, tileHall);
            by += by < mid ? +1 : -1;
        }
        while (ax != bx)
        {
            SetTile(floor, ax, ay, tileHall);
            ax += ax < bx ? +1 : -1;
        }
        SetTile(floor, ax, ay, tileHall);
    }
    return 1;
}

int IsTilePassable(Floor *floor, int x, int y)
{
    if (x < 0 || x >= floor_w || y < 0 || y >= floor_h)
    {
        return 0;
    }

    switch (GetTile(floor, x, y))
    {
        case tileFloor:
            return 1;
        case tileHall:
            return 1;
        case tileStairs:
            return 1;
        case tileLava:
        case tileLavaBorderUp:
        case tileLavaBorderRightUp:
        case tileLavaBorderLeftUp:
        case tileLavaBorderBottom:
        case tileLavaBorderBottomRight:
        case tileLavaBorderBottomLeft:
        case tileLavaBorderMiddleLeft:
        case tileLavaBorderMiddleRight:
            return 0;
        case tileItem:
            return 1;
        case tilePlayer:
            return 1;
        default:
            return 0;
    }
}

int IsTilePassableByType(Floor *floor, Tile tile)
{
    switch (tile)
    {
        case tileFloor:
            return 1;
        case tileHall:
            return 1;
        case tileStairs:
            return 1;
        case tileLava:
        case tileLavaBorderUp:
        case tileLavaBorderRightUp:
        case tileLavaBorderLeftUp:
        case tileLavaBorderBottom:
        case tileLavaBorderBottomRight:
        case tileLavaBorderBottomLeft:
        case tileLavaBorderMiddleLeft:
        case tileLavaBorderMiddleRight:
            return 0;
        case tileItem:
            return 1;
        case tilePlayer:
            return 1;
        default:
            return 0;
    }
}


int CheckCorner(Floor *floor, int x, int y)
{
    int tile_n = IsTilePassable(floor, x, y - 1);
    int tile_s = IsTilePassable(floor, x, y + 1);
    int tile_e = IsTilePassable(floor, x + 1, y);
    int tile_w = IsTilePassable(floor, x - 1, y);
    int tile_ne = IsTilePassable(floor, x + 1, y - 1);
    int tile_nw = IsTilePassable(floor, x - 1, y - 1);
    int tile_se = IsTilePassable(floor, x + 1, y + 1);
    int tile_sw = IsTilePassable(floor, x - 1, y + 1);
    if (tile_n && tile_ne && tile_e && (!tile_s || !tile_w))
        return 1;
    if (tile_n && tile_nw && tile_w && (!tile_s || !tile_e))
        return 1;
    if (tile_s && tile_se && tile_e && (!tile_n || !tile_w))
        return 1;
    if (tile_s && tile_sw && tile_w && (!tile_n || !tile_e))
        return 1;
    return 0;
}

int RemoveWideCorridors(Floor *floor)
{
    for (int x = 0; x < floor_w; x++)
    {
        for (int y = 0; y < floor_h; y++)
        {
            if (GetTile(floor, x, y) == tileHall && CheckCorner(floor, x, y))
            {
                SetTile(floor, x, y, tileUnused);
            }
        }
    }
    return 1;
}

// Rooms

int CheckRoomPlacement(Floor *floor, int x, int y, int w, int h)
{
    if (x < 0 || y < 0 || x + w > floor_w || y + h > floor_h)
    {
        return 0;
    }

    // Check against the size of the room plus the minimum boundary
    int new_x = x - MIN_ROOM_BUFFER >= 0 ? x - MIN_ROOM_BUFFER : 0;
    int new_y = y - MIN_ROOM_BUFFER >= 0 ? y - MIN_ROOM_BUFFER : 0;
    int max_x = x + w + MIN_ROOM_BUFFER < floor_w ? x + w + MIN_ROOM_BUFFER : floor_w;
    int max_y = y + h + MIN_ROOM_BUFFER < floor_h ? y + h + MIN_ROOM_BUFFER : floor_h;

    // Make sure the new room won't intersect any room tiles and intersects at least one hall tile
    for (int px = new_x; px < max_x; px++)
    {
        for (int py = new_y; py < max_y; py++)
        {
            if (GetTile(floor, px, py) == tileFloor)
                return 0;
        }
    }
    int hall_tile_found = 0;
    for (int px = x; px < x + w; px++)
    {
        for (int py = y; py < y + h; py++)
        {
            if (GetTile(floor, px, py) == tileHall)
                hall_tile_found = 1;
        }
    }

    // Placement might be good!
    return hall_tile_found;
}

int AddRoom(Floor *floor, int x, int y, int w, int h)
{
    if (!CheckRoomPlacement(floor, x, y, w, h))
    {
        return 0;
    }

    // Fill room with passable tiles
    for (int px = x + 1; px < x + w - 1; px++)
    {
        for (int py = y + 1; py < y + h - 1; py++)
        {
            SetTile(floor, px, py, tileFloor);
        }
    }

    // Add extra elements

    return 1;
}

// Terrain

int AddTerrain(Floor *floor, int tile_terrain, int ax, int ay, int bx, int by)
{
    if (ax == bx && ay == by)
    {
        return 0;
    }
    int x_diff = ax > bx ? ax - bx : bx - ax;
    int y_diff = ay > by ? ay - by : by - ay;
    int mid;
    if (x_diff > y_diff)
    {
        mid = ax < bx ? rand_interval(ax, bx) : rand_interval(bx, ax);
        while (ax != mid)
        {
            if (GetTile(floor, ax, ay) == tileUnused)
            {
                SetTile(floor, ax, ay, tile_terrain);
            }
            ax += ax < mid ? + 1 : -1;
        }
        while (bx != mid)
        {
            if (GetTile(floor, bx, by) == tileUnused)
            {
                SetTile(floor, bx, by, tile_terrain);
            }
            bx += bx < mid ? + 1 : -1;
        }
        while (ay != by)
        {
            if (GetTile(floor, ax, ay) == tileUnused)
            {
                SetTile(floor, ax, ay, tile_terrain);
            }
            ay += ay < by ? + 1 : -1;
        }
        if (GetTile(floor, ax, ay) == tileUnused)
        {
            SetTile(floor, ax, ay, tile_terrain);
        }
    }
    else
    {
        mid = ay < by ? rand_interval(ay, by) : rand_interval(by, ay);
        while (ay != mid)
        {
            if (GetTile(floor, ax, ay) == tileUnused)
            {
                SetTile(floor, ax, ay, tile_terrain);
            }
            ay += ay < mid ? +1 : -1;
        }
        while (by != mid)
        {
            if (GetTile(floor, bx, by) == tileUnused)
            {
                SetTile(floor, bx, by, tile_terrain);
            }
            by += by < mid ? + 1 : -1;
        }
        while (ax != bx)
        {
            if (GetTile(floor, ax, ay) == tileUnused)
            {
                SetTile(floor, ax, ay, tile_terrain);
            }
            ax += ax < bx ? + 1 : -1;
        }
        if (GetTile(floor, ax, ay) == tileUnused)
        {
            SetTile(floor, ax, ay, tile_terrain);
        }
    }
    return 1;
}

static void FixLavaTiles(Floor *floor)
{
    for (int y = floor->height; y > 0; y--)
    {
        for (int x = 0; x < floor->width; x++)
        {
            if (GetTile(floor, x, y) == tileLava)
            {
                Tile tile_terrain = GetCorrectLavaTileType(floor, x, y);
                SetTile(floor, x, y, tile_terrain);
            }
        }
    }
}

static void MakeItems(Floor *floor, int num_items)
{
    int tries = 0;
    int maxTries = 1000;

    int current_num_items = 0;

    for (; tries != maxTries; ++tries)
    {
        // Exit when num_items is reached
        if (current_num_items > num_items - 1)
            return;

        int x = rand_interval(2, floor->width - 2);
        int y = rand_interval(2, floor->height - 2);

        if (GetTile(floor, x, y) == tileFloor)
        {
            // Random types of items from 60 to 70
            Items item = rand_interval(60, 70);

            floor->tiles[x][y].item = item;
            floor->tiles[x][y].tile = tileItem;

            current_num_items++;
        }
    }
}

static void MakeSpawnPointForPlayer(Floor *floor)
{
    int tries = 0;
    int max_tries = 1000;

    for (; tries != max_tries; ++tries)
    {
        int x = rand_interval(2, floor->width - 2);
        int y = rand_interval(2, floor->height - 2);

        if (GetTile(floor, x, y) == tileFloor)
        {
            SetPlayerSpawnPoint(floor, make_ivec2(x, y));
            return;
        }
    }
}

Floor *GenerateFloor(u32 seed, int num_items)
{
    Floor *floor = calloc(1, sizeof(*floor));
    floor->width = floor_w;
    floor->height = floor_h;
    srand(seed);

    // Fill floor with unused tiles
    floor->tiles = malloc(sizeof(TileState) * floor_w);
    for (int x = 0; x < floor_w; x++)
    {
        floor->tiles[x] = malloc(sizeof(TileState) * floor_h);
        for (int y = 0; y < floor_h; y++)
        {
            SetTile(floor, x, y, tileUnused);
        }
    }

    // Place floor boundaries
    for (int x = 0; x < floor->width; x++)
    {
        SetTile(floor, x, 0, tileEnd);
        SetTile(floor, x, floor->height - 1, tileEnd);
    }
    for (int y = 0; y < floor->height; y++)
    {
        SetTile(floor, 0, y, tileEnd);
        SetTile(floor, floor->width - 1, y, tileEnd);
    }

    // Fill with corridors
    int hall_start_x = rand_interval(3, floor_w - 3);
    int hall_start_y = rand_interval(3, floor_h - 3);
    int length = 0;
    while (length < total_corridor_length)
    {
        int dest_x = rand_interval(3, floor_w - 3);
        int dest_y = rand_interval(3, floor_h - 3);
        AddCorridor(floor, hall_start_x, hall_start_y, dest_x, dest_y);
        length += abs(dest_x - hall_start_x) + abs(dest_y - hall_start_y);
        hall_start_x = dest_x;
        hall_start_y = dest_y;
        RemoveWideCorridors(floor);
    }

    // Place rooms
    int failure_count = 0;
    int room_count = 0;
    while (failure_count < MAX_PLACEMENT_FAILURES || !room_count)
    {
        int w = rand_interval(min_room_dimension, floor_w / min_room_dimension);
        int h = rand_interval(min_room_dimension, floor_h / min_room_dimension);
        int max_x = MAX(floor_w - 3, floor_w - w);
        int max_y = MAX(floor_h - 3, floor_h - h);
        //int x = rand_interval(3, floor_w - w);
        //int y = rand_interval(3, floor_h - h);
        int x = rand_interval(3, max_x);
        int y = rand_interval(3, max_y);

        if (!AddRoom(floor, x, y, w, h))
        {
            failure_count++;
        }
        else
        {
            if (!room_count)
            {
                // Initial room added
                while (GetTile(floor, floor->start_x, floor->start_y) != tileFloor)
                {
                    floor->start_x = rand_interval(x, x + w);
                    floor->start_y = rand_interval(y, y + h);
                }
            }
            room_count++;
        }
    }

    // Place terrain
    for (int i = 0; i < floor->width / 10; i++)
    {
        int terrain_start_x = rand_interval(2, floor_w - 2);
        int terrain_start_y = rand_interval(2, floor_h - 2);
        int terrain_length = 0;
        while (terrain_length < total_corridor_length * 5)
        {
            int dest_x = rand_interval(MAX(1, terrain_start_x - 4), MIN(floor_w - 2, terrain_start_x + 4));
            int dest_y = rand_interval(MAX(1, terrain_start_y - 4), MIN(floor_w - 2, terrain_start_y + 4));
            
            AddTerrain(floor, tileLava, terrain_start_x, terrain_start_y, dest_x, dest_y);
            terrain_length += abs(dest_x - terrain_start_x) + abs(dest_y - terrain_start_y);
            terrain_start_x = dest_x;
            terrain_start_y = dest_y;
        }
    }

    // Place stairs
    int stairs_placed = 0;
    while (!stairs_placed)
    {
        int x = rand_interval(1, floor_w - 2);
        int y = rand_interval(1, floor_h - 2);
        if (GetTile(floor, x, y) == tileFloor
            && GetTile(floor, x + 1, y) != tileHall
            && GetTile(floor, x - 1, y) != tileHall
            && GetTile(floor, x, y + 1) != tileHall
            && GetTile(floor, x, y - 1) != tileHall)
        {
            SetTile(floor, x, y, tileStairs);
            stairs_placed = true;
        }
    }

    // Fill unused tiles
    for (int x = 0; x < floor->width; x++)
    {
        for (int y = 0; y < floor->height; y++)
        {
            if (GetTile(floor, x, y) == tileUnused)
            {
                SetTile(floor, x, y, tileWall);
            }
        }
    }

    FixLavaTiles(floor);
    MakeItems(floor, num_items);
    MakeSpawnPointForPlayer(floor);
    // Add graphics
    //AddFloorSurface(floor);

    return floor;
}


// Called when starting a new dungeon
void Dungeon_SetUpDefualtStatus(PokemonParty *party)
{
    for (int i = 0; i < party->size; i++)
    {
        Pokemon_StatusReset(party->members[i], true);
    }
}

// Called when then player gets past the stairs
void Dungeon_SetStatusAfterStairs(PokemonParty *party)
{
    for (int i = 0; i < party->size; i++)
    {
        Pokemon_StatusReset(party->members[i], false);
    }
}

void Dungeon_NextFloorLevel(Dungeon *self, PokemonParty *party)
{
    Dungeon_SetStatusAfterStairs(party);
    self->current_floor_level++;
    self->current_weather = WeatherClear;
}