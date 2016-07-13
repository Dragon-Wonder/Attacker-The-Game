#ifndef _ROOMS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _ROOMS_H_INCLUDED__
/*****************************************************************************/
#include "global.h"
/*****************************************************************************/
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
/*****************************************************************************/
struct stcMapStats {
    struct stcXY max;
    struct stcXY size;
    int objects;
    int chanceRoom;
    int chanceCorridor;
};

typedef struct stcMapStats MapStc;
/*****************************************************************************/
class Dungeon {
    static MapStc mapstats;
    static int dungeon_map[DEFINED_MAP_WIDTH * DEFINED_MAP_HEIGHT];
    long oldseed;

	public:
        Dungeon();
        void setCell(int, int, int);
        void setCell(LOC, int);

        int getCell(int, int);
        int getCell(LOC);

        int getRand(int, int);
        bool makeCorridor(int, int, int, int);
        bool makeRoom(int, int, int, int, int);
        //void showDungeon();
        bool createDungeon(int, int, int);
        int* make_dungeon();
        void cmain();
        void playerfind();
        //char PlayerMovement(char);
};
/*****************************************************************************/
#endif
