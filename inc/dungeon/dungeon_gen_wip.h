// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#ifndef _DUNGEON_GEN_H_
#define _DUNGEON_GEN_H_

#include "util.h"
#include "common/stack.h"

typedef enum
{
    Unused,
    DirtWall,
    DirtFloor,
    Corridor,
    Door,
    UpStairs,
    DownStairs
} Tile;


typedef enum
{
    North,
    South,
    West,
    East,
    DirectionCount
} Direction;

typedef struct
{
    int size_x;
    int size_y;
    int *data;
} Map;

typedef struct
{
    u64 Seed;
    int size_x;
    int size_y;
    int MaxFeatures;
    int ChanceRoom;
    int ChanceCorridor;
} Dungeon;

void SetCell(Map *map, int x, int y, Tile celltype);
int  GetCell(Map *map, int x, int y);
int  GetRand(u64 rng, int min, int max);
Direction GetRandomDirection(u64 rng);
void SetCells(Map *map, int xStart, int yStart, int xEnd, int yEnd, Tile cellType);
bool MakeCorridor(Map *map, u64 rng, int x, int y, int maxLength, Direction direction);
bool MakeRoom(Map *map, u64 rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction);
bool MakeFeature(Dungeon dungeon, Map *map, u64 rng, int x, int y, int xmod, int ymod, Direction direction);
bool MakeFeatures(Dungeon dungeon, Map *map, u64 rng);
bool MakeStairs(Dungeon dungeon, Map *map, u64 rng, Tile tile);
bool MakeDungeon(Dungeon dungeon, Map *map, u64 rng);
void Print(Map *map);
void dungeon_main();
void dungeon_free();

#endif
