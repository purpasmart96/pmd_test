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

void setCell(int x, int y, int celltype);
int getCell(int x, int y);
int getRand(int min, int max);
bool makeCorridor(int x, int y, int lenght, int direction);
bool makeRoom(int x, int y, int xlength, int ylength, int direction);
void showDungeon();
bool createDungeon(int inx, int iny, int inobj);
void dungeon_main();


#endif