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
#include <SOIL.h>

enum
{
    tileUnused = 0,
    tileDirtWall,
    tileDirtFloor,
    tileStoneWall,
    tileCorridor,
    tileDoor,
    tileUpStairs,
    tileDownStairs,
    tileChest
};

/*
typedef enum
{
    North,
    South,
    West,
    East,
    DirectionCount
} Direction;
*/

typedef enum
{
    North,
    East,
    South,
    West,
} Direction;


typedef struct
{
    int x;
    int y;
    int width;
    int height;
} Rect;

typedef struct
{

    int _width, _height;


} Dungeon;


char *DecodeImage(char *filename);

void setCell(int x, int y, int celltype);
int getCell(int x, int y);
int getRand(int min, int max);
bool makeCorridor(int x, int y, int lenght, Direction direction);
bool makeRoom(int x, int y, int xlength, int ylength, Direction direction);
void showDungeon();
bool createDungeon(int inx, int iny, int inobj);
void dungeon_main();
void dungeon_free();

void MapGenerate();

#endif
