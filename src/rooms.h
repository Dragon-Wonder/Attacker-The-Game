#ifndef _ROOMS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _ROOMS_H_INCLUDED__

#include "global.h"
#include "basic.h"
#include "battle.h"

#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>

class Dungeon
{
    int xmax;
    int ymax;
    int xsize;
    int ysize;
    int objects;
    int chanceRoom;
    int chanceCorridor;
    int* dungeon_map;
    long oldseed;
    enum
    {
        tileUnused = 0x0, //0
        tileDirtWall = 0x1, //1
        tileDirtFloor = 0x2, //2
        tileStoneWall = 0x3, //3
        tileCorridor = 0x4, //4
        tileDoor = 0x5, //5
        tileUpStairs = 0x6, //6
        tileDownStairs = 0x7, //7
        tileChest = 0x8, //8
		tilePlayer = 0x9, //9
		tileLockedDoor = 0xA //10
    };
    string msgXSize;
    string msgYSize;
    string msgMaxObjects;
    string msgNumObjects;
    string msgHelp;
    string msgDetailedHelp;
	public:
    Dungeon();
    void setCell(int, int, int);
    int getCell(int, int);
    int getRand(int, int);
    bool makeCorridor(int, int, int, int);
	bool makeRoom(int, int, int, int, int);
	void showDungeon();
	bool createDungeon(int, int, int);
    int* make_dungeon();
	void cmain();
	void playerfind();
	char PlayerMovement(char);
};

#endif
