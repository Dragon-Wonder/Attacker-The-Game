#ifndef _ROOMS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _ROOMS_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold all the functions related to rooms, their generation and such.
Source: http://www.roguebasin.com/index.php?title=C%2B%2B_Example_of_Dungeon-Building_Algorithm
Current Revision: 2.1
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/20/15	1.0			Patrick Rye			-Original
=============================================================================================================================================================
2/23/15	1.1			Patrick Rye			-Added player tile
										-Changed the generated stairs up to generate a Player instead
											-Basically you can never goo back up and I don't have to worry about putting the stair back when they move.
										-Made getcell, setcell, showDungeon all public so I can access them from the main code.
=============================================================================================================================================================
2/26/15	1.2			Patrick Rye			-Moved player movement function here.
=============================================================================================================================================================
2/27/15	1.3			Patrick Rye			-Added option to save on map.
=============================================================================================================================================================
3/2/15	1.4			Patrick Rye			-Moved healing to happening between battles.
=============================================================================================================================================================
3/2/15	1.5			Patrick Rye			-General code improvement.
										-Fixed two player bug.
=============================================================================================================================================================
3/3/15	2.0			Patrick Rye			-Added debug mode.
=============================================================================================================================================================
3/4/15 	2.1			Patrick Rye			-Changed all system("pause") to getch.
										-Replaced all cout << string(X, '\n'); with refresh();
=============================================================================================================================================================	
*/
int intPlayerX; //Player position in X and Y.
int intPlayerY;
int intPlayerNewX; //Player position in X and Y.
int intPlayerNewY;
 
int intTempTile = 6; //Value to hold what the cell that the player is moving into is.
 
bool blRoomsDebugMode = false;
 
void SetRoomDebugMode(bool isDebug) {blRoomsDebugMode = isDebug;} 
 
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
        tileUnused = 0, //0
        tileDirtWall, //1
        tileDirtFloor, //2
        tileStoneWall, //3
        tileCorridor, //4
        tileDoor, //5
        tileUpStairs, //6
        tileDownStairs, //7
        tileChest, //8
		tilePlayer //9
    };
 
    std::string msgXSize;
    std::string msgYSize;
    std::string msgMaxObjects;
    std::string msgNumObjects;
    std::string msgHelp;
    std::string msgDetailedHelp;
	
	public:
    void setCell(int x, int y, int celltype)
    {
        dungeon_map[x + xsize * y] = celltype;
    }
	public:
    int getCell(int x, int y)
    {
        return dungeon_map[x + xsize * y];
    }
 
    int getRand(int min, int max)
    {
        time_t seed;
        seed = time(NULL) + oldseed;
        oldseed = seed;
 
        srand(seed);
 
        int n = max - min + 1;
        int i = rand() % n;
 
        if(i < 0)
            i = -i;
 
        return min + i;
    }
 
    bool makeCorridor(int x, int y, int lenght, int direction)
    {
        int len = getRand(2, lenght);
        int floor = tileCorridor;
        int dir = 0;
        if(direction > 0 && direction < 4) dir = direction;
 
        int xtemp = 0;
        int ytemp = 0;
 
        switch(dir)
        {
            case 0:
            {
                if(x < 0 || x > xsize) return false;
                else xtemp = x;
 
                for(ytemp = y; ytemp > (y-len); ytemp--)
                {
                    if(ytemp < 0 || ytemp > ysize) return false;
                    if(getCell(xtemp, ytemp) != tileUnused) return false;
                }
 
                for(ytemp = y; ytemp > (y - len); ytemp--)
                {
                    setCell(xtemp, ytemp, floor);
                }
                break;
 
            }
            case 1:
            {
                if(y < 0 || y > ysize) return false;
                else ytemp = y;
 
                for(xtemp = x; xtemp < (x + len); xtemp++)
                {
                    if(xtemp < 0 || xtemp > xsize) return false;
                    if(getCell(xtemp, ytemp) != tileUnused) return false;
                }
 
                for(xtemp = x; xtemp < (x + len); xtemp++)
                {
                    setCell(xtemp, ytemp, floor);
                }
                break;
            }
            case 2:
            {
                if(x < 0 || x > xsize) return false;
                else xtemp = x;
 
                for(ytemp = y; ytemp < (y + len); ytemp++)
                {
                    if(ytemp < 0 || ytemp > ysize) return false;
                    if(getCell(xtemp, ytemp) != tileUnused) return false;
                }
                for (ytemp = y; ytemp < (y+len); ytemp++){
                    setCell(xtemp, ytemp, floor);
                }
			break;
            }
            case 3:
            {
                if (ytemp < 0 || ytemp > ysize) return false;
                else ytemp = y;
 
                for (xtemp = x; xtemp > (x-len); xtemp--){
                    if (xtemp < 0 || xtemp > xsize) return false;
                    if (getCell(xtemp, ytemp) != tileUnused) return false;
                }
 
                for (xtemp = x; xtemp > (x-len); xtemp--){
                    setCell(xtemp, ytemp, floor);
                }
                break;
            }
		}
		//woot, we're still here! let's tell the other guys we're done!!
		return true;
	}
	bool makeRoom(int x, int y, int xlength, int ylength, int direction){
		//define the dimensions of the room, it should be at least 4x4 tiles (2x2 for walking on, the rest is walls)
		int xlen = getRand(4, xlength);
		int ylen = getRand(4, ylength);
		//the tile type it's going to be filled with
		int floor = tileDirtFloor; //jordgolv..
		int wall = tileDirtWall; //jordv????gg
		//choose the way it's pointing at
		int dir = 0;
		if (direction > 0 && direction < 4) dir = direction;
 
		switch(dir){
		case 0:
		//north
			//Check if there's enough space left for it
			for (int ytemp = y; ytemp > (y-ylen); ytemp--){
				if (ytemp < 0 || ytemp > ysize) return false;
				for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
					if (xtemp < 0 || xtemp > xsize) return false;
					if (getCell(xtemp, ytemp) != tileUnused) return false; //no space left...
				}
			}
 
			//we're still here, build
			for (int ytemp = y; ytemp > (y-ylen); ytemp--){
				for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
					//start with the walls
					if (xtemp == (x-xlen/2)) setCell(xtemp, ytemp, wall);
					else if (xtemp == (x+(xlen-1)/2)) setCell(xtemp, ytemp, wall);
					else if (ytemp == y) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y-ylen+1)) setCell(xtemp, ytemp, wall);
					//and then fill with the floor
					else setCell(xtemp, ytemp, floor);
				}
			}
			break;
		case 1:
		//east
			for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++){
				if (ytemp < 0 || ytemp > ysize) return false;
				for (int xtemp = x; xtemp < (x+xlen); xtemp++){
					if (xtemp < 0 || xtemp > xsize) return false;
					if (getCell(xtemp, ytemp) != tileUnused) return false;
				}
			}
 
			for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++){
				for (int xtemp = x; xtemp < (x+xlen); xtemp++){
 
					if (xtemp == x) setCell(xtemp, ytemp, wall);
					else if (xtemp == (x+xlen-1)) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y-ylen/2)) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y+(ylen-1)/2)) setCell(xtemp, ytemp, wall);
 
					else setCell(xtemp, ytemp, floor);
				}
			}
			break;
		case 2:
		//south
			for (int ytemp = y; ytemp < (y+ylen); ytemp++){
				if (ytemp < 0 || ytemp > ysize) return false;
				for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
					if (xtemp < 0 || xtemp > xsize) return false;
					if (getCell(xtemp, ytemp) != tileUnused) return false;
				}
			}
 
			for (int ytemp = y; ytemp < (y+ylen); ytemp++){
				for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
 
					if (xtemp == (x-xlen/2)) setCell(xtemp, ytemp, wall);
					else if (xtemp == (x+(xlen-1)/2)) setCell(xtemp, ytemp, wall);
					else if (ytemp == y) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y+ylen-1)) setCell(xtemp, ytemp, wall);
 
					else setCell(xtemp, ytemp, floor);
				}
			}
			break;
		case 3:
		//west
			for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++){
				if (ytemp < 0 || ytemp > ysize) return false;
				for (int xtemp = x; xtemp > (x-xlen); xtemp--){
					if (xtemp < 0 || xtemp > xsize) return false;
					if (getCell(xtemp, ytemp) != tileUnused) return false;
				}
			}
 
			for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++){
				for (int xtemp = x; xtemp > (x-xlen); xtemp--){
 
					if (xtemp == x) setCell(xtemp, ytemp, wall);
					else if (xtemp == (x-xlen+1)) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y-ylen/2)) setCell(xtemp, ytemp, wall);
					else if (ytemp == (y+(ylen-1)/2)) setCell(xtemp, ytemp, wall);
 
					else setCell(xtemp, ytemp, floor);
				}
			}
			break;
		}
 
		//yay, all done
		return true;
	}
	public:
	void showDungeon(){
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				//System.out.print(getCell(x, y));
				switch(getCell(x, y)){
				case tileUnused:
					printf("█");
					break;
				case tileDirtWall:
					printf("█");
					break;
				case tileDirtFloor:
					printf(" ");
					break;
				case tileStoneWall:
					printf("█");
					break;
				case tileCorridor:
					printf(" ");//░
					break;
				case tileDoor:
					printf("$");
					break;
				case tileUpStairs:
					printf("<");
					break;
				case tileDownStairs:
					printf(">");
					break;
				case tileChest:
					printf("@");
					break;
				case tilePlayer:
					printf("†");
					break;
				};
			}
			//if (xsize <= xmax) printf("\n");
		}
	}
	bool createDungeon(int inx, int iny, int inobj){
		if (inobj < 1) objects = 10;
		else objects = inobj;
 
		//justera kartans storlek, om den ????r st????rre eller mindre ????n "gr????nserna"
		//adjust the size of the map, if it's smaller or bigger than the limits
		if (inx < 3) xsize = 3;
		else if (inx > xmax) xsize = xmax;
		else xsize = inx;
 
		if (iny < 3) ysize = 3;
		else if (iny > ymax) ysize = ymax;
		else ysize = iny;
 
		//printf("%s %d\n", msgXSize.c_str(), xsize);
		//printf("%s %d\n", msgYSize.c_str(),  + ysize);
		//printf("%s %d\n", msgMaxObjects.c_str(), objects);
 
		//redefine the map var, so it's adjusted to our new map size
		dungeon_map = new int[xsize * ysize];
 
		//start with making the "standard stuff" on the map
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				//ie, making the borders of unwalkable walls
				if (y == 0) setCell(x, y, tileStoneWall);
				else if (y == ysize-1) setCell(x, y, tileStoneWall);
				else if (x == 0) setCell(x, y, tileStoneWall);
				else if (x == xsize-1) setCell(x, y, tileStoneWall);
 
				//and fill the rest with dirt
				else setCell(x, y, tileUnused);
			}
		}
 
		/*******************************************************************************
		And now the code of the random-map-generation-algorithm begins!
		*******************************************************************************/
 
		//start with making a room in the middle, which we can start building upon
		makeRoom(xsize/2, ysize/2, 8, 6, getRand(0,3)); //getrand saken f????r att slumpa fram riktning p?? rummet
 
		//keep count of the number of "objects" we've made
		int currentFeatures = 1; //+1 for the first room we just made
 
		//then we start the main loop
		for (int countingTries = 0; countingTries < 1000; countingTries++){
			//check if we've reached our quota
			if (currentFeatures == objects){
				break;
			}
 
			//start with a random wall
			int newx = 0;
			int xmod = 0;
			int newy = 0;
			int ymod = 0;
			int validTile = -1;
			//1000 chances to find a suitable object (room or corridor)..
			//(yea, i know it's kinda ugly with a for-loop... -_-')
			for (int testing = 0; testing < 1000; testing++){
				newx = getRand(1, xsize-1);
				newy = getRand(1, ysize-1);
				validTile = -1;
				//System.out.println("tempx: " + newx + "\ttempy: " + newy);
				if (getCell(newx, newy) == tileDirtWall || getCell(newx, newy) == tileCorridor){
					//check if we can reach the place
					if (getCell(newx, newy+1) == tileDirtFloor || getCell(newx, newy+1) == tileCorridor){
						validTile = 0; //
						xmod = 0;
						ymod = -1;
					}
					else if (getCell(newx-1, newy) == tileDirtFloor || getCell(newx-1, newy) == tileCorridor){
						validTile = 1; //
						xmod = +1;
						ymod = 0;
					}
					else if (getCell(newx, newy-1) == tileDirtFloor || getCell(newx, newy-1) == tileCorridor){
						validTile = 2; //
						xmod = 0;
						ymod = +1;
					}
					else if (getCell(newx+1, newy) == tileDirtFloor || getCell(newx+1, newy) == tileCorridor){
						validTile = 3; //
						xmod = -1;
						ymod = 0;
					}
 
					//check that we haven't got another door nearby, so we won't get alot of openings besides
					//each other
					if (validTile > -1){
						if (getCell(newx, newy+1) == tileDoor) //north
							validTile = -1;
						else if (getCell(newx-1, newy) == tileDoor)//east
							validTile = -1;
						else if (getCell(newx, newy-1) == tileDoor)//south
							validTile = -1;
						else if (getCell(newx+1, newy) == tileDoor)//west
							validTile = -1;
					}
 
					//if we can, jump out of the loop and continue with the rest
					if (validTile > -1) break;
				}
			}
			if (validTile > -1){
				//choose what to build now at our newly found place, and at what direction
				int feature = getRand(0, 100);
				if (feature <= chanceRoom){ //a new room
					if (makeRoom((newx+xmod), (newy+ymod), 8, 6, validTile)){
						currentFeatures++; //add to our quota
 
						//then we mark the wall opening with a door
						setCell(newx, newy, tileDoor);
 
						//clean up infront of the door so we can reach it
						setCell((newx+xmod), (newy+ymod), tileDirtFloor);
					}
				}
				else if (feature >= chanceRoom){ //new corridor
					if (makeCorridor((newx+xmod), (newy+ymod), 6, validTile)){
						//same thing here, add to the quota and a door
						currentFeatures++;
 
						setCell(newx, newy, tileDoor);
					}
				}
			}
		}
 
 
		/*******************************************************************************
		All done with the building, let's finish this one off
		*******************************************************************************/
 
		//sprinkle out the bonus stuff (stairs, chests etc.) over the map
		int newx = 0;
		int newy = 0;
		int ways = 0; //from how many directions we can reach the random spot from
		int state = 0; //the state the loop is in, start with the stairs
		while (state != 10){
			for (int testing = 0; testing < 1000; testing++){
				newx = getRand(1, xsize-1);
				newy = getRand(1, ysize-2); //cheap bugfix, pulls down newy to 0<y<24, from 0<y<25
 
				//System.out.println("x: " + newx + "\ty: " + newy);
				ways = 4; //the lower the better
 
				//check if we can reach the spot
				if (getCell(newx, newy+1) == tileDirtFloor || getCell(newx, newy+1) == tileCorridor){
				//north
					if (getCell(newx, newy+1) != tileDoor)
					ways--;
				}
				if (getCell(newx-1, newy) == tileDirtFloor || getCell(newx-1, newy) == tileCorridor){
				//east
					if (getCell(newx-1, newy) != tileDoor)
					ways--;
				}
				if (getCell(newx, newy-1) == tileDirtFloor || getCell(newx, newy-1) == tileCorridor){
				//south
					if (getCell(newx, newy-1) != tileDoor)
					ways--;
				}
				if (getCell(newx+1, newy) == tileDirtFloor || getCell(newx+1, newy) == tileCorridor){
				//west
					if (getCell(newx+1, newy) != tileDoor)
					ways--;
				}
 
				if (state == 0){
					if (ways == 0){
					//we're in state 0, let's place a Player from where they came down the stairs.
						setCell(newx, newy, tilePlayer);
						//intPlayerX = newx;
						//intPlayerY = newy;
						state = 1;
						break;
					}
				}
				else if (state == 1){
					if (ways == 0){
					//state 1, place a "downstairs"
						setCell(newx, newy, tileDownStairs);
						state = 10;
						break;
					}
				}
			}
		}
 
 
		//all done with the map generation, tell the user about it and finish
		//printf("%s %d\n",msgNumObjects.c_str(), currentFeatures);
 
		return true;
	}
 
	public:
    int* make_dungeon()
    {
        int x = 80;
        int y = 20;
        int dungeon_objects = 100;
        dungeon_map = new int[x * y];
        //for(;;)
        //{	
			intTempTile = tileUpStairs;
            if(createDungeon(x, y, dungeon_objects))
            showDungeon();
            //std::cin.get();
        //}
		return dungeon_map;
    }
	void cmain()
    {
        int x = 80;
        int y = 20;
        int dungeon_objects = 100;
        dungeon_map = new int[x * y];

        if(createDungeon(x, y, dungeon_objects)) {showDungeon();}
		playerfind();
	//PostPlayerFind:
    }
	public:
	void playerfind()
	{
		for (int y2 = 0; y2 < 80; y2++)
		{
			for (int x2 = 0; x2 < 20; x2++)
			{
				if (getCell(x2,y2)==9) //Finds where player is.
				{
					intPlayerX = x2;
					intPlayerY = y2;
					x2 = 80;
					y2 = 20;
					//Set x and y to max values so the for loops stop.
				}
			}
		}
	}
	public:
	char PlayerMovement(char chrPlayerDirection)
	{
		playerfind();
		intPlayerNewX = intPlayerX;
		intPlayerNewY = intPlayerY;
		switch (chrPlayerDirection)
		{
			case 'N' : //Player wants to go up.
				intPlayerNewY -= 1;
				break;
			case 'S' : //Player wants to go down.
				intPlayerNewY += 1;
				break;
			case 'E' : //Player wants to go right.
				intPlayerNewX += 1;
				break;
			case 'W' : //Player wants to go left.
				intPlayerNewX -= 1;
				break;
			case 'X' : //Player wants to exit game.
				refresh();
				cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All progress will be lost."<<endl<<"Y or N"<<endl<<"> ";
				cin>>chrPlayerDirection;
				chrPlayerDirection = CharConvertToUpper(chrPlayerDirection);
				switch (chrPlayerDirection)
				{
					case 'Y' :
						return 'E';
						break;
					default :
						return 'F';
						break;
				}
				break;
			case 'P' : //Player wants to save.
				return 'S'; //Player is asking to save, return S for save.
				break;
			case 'H' : //Player wants to heal.
				int intPlayerCurrHealth;
				intPlayerCurrHealth = getbattlevalue(5);
				int intPlayerMaxHealth;
				intPlayerMaxHealth = getbattlevalue(6);
				int intPlayerHealAmount;
				intPlayerHealAmount = floor(intPlayerMaxHealth/10);
				if (intPlayerCurrHealth + intPlayerHealAmount >= intPlayerMaxHealth) {intPlayerCurrHealth = intPlayerMaxHealth;}
				else {intPlayerCurrHealth += intPlayerHealAmount;}
				setbattlevalue(5,intPlayerCurrHealth); //Set player current health to the new amount.
				cout<<endl<<"Your health is now: "<<intPlayerCurrHealth<<" out of "<<intPlayerMaxHealth<<".";
				getch();
				return 'F'; //Return F that player did not find exit.
				break;
			case 'C' : //Player is checking themselves.
				int intPlayerStatsTemp[7];
				for (int i = 0; i < 7; i++) {intPlayerStatsTemp[i]=getbattlevalue(i);}
				cout<<endl<<"Your health is now: "<<intPlayerStatsTemp[5]<<" out of "<<intPlayerStatsTemp[6]<<".";
				cout<<endl<<"Your stats are as follows: "<<endl;
				cout<<"STR: "<<intPlayerStatsTemp[0]<<endl<<"CONS: "<<intPlayerStatsTemp[1]<<endl;
				cout<<"DEF: "<<intPlayerStatsTemp[2]<<endl<<"DEX: "<<intPlayerStatsTemp[3]<<endl;
				cout<<"LUK: "<<intPlayerStatsTemp[4]<<endl;
				getch();
				return 'F';
				break;
			case '&' : //Debug code to go straight to stairs.
				if (blRoomsDebugMode)
				{for (int y = 0; y < 20; y++){for (int x = 0; x < 80; x++){
					if (getCell(x,y)==tileDownStairs) //Finds where the down stairs are.
					{
						intPlayerNewX = x;
						intPlayerNewY = y;
						goto PostMovingCode;
					};
				}} break;}
			case 'M' :
				if (blRoomsDebugMode) {return 'M'; break;}
			default : 
				cout<<endl<<"Invalid choice, please try again."<<endl;
				return 'F';
				break;
		//End of case for direction picked.
		}
		PostMovingCode:
		switch (getCell(intPlayerNewX,intPlayerNewY))
		{
			case tileDownStairs :
				//Return a true saying that the player found the exit, aka the down stairs.
				return 'T';
				break;
			case tileStoneWall :
			case tileDirtWall :
			case tileUnused :
			case tilePlayer :
				//Player is trying to walk into something they can't.
				//Just return a false saying they did not find the exit.
				return'F';
				break;
			case tileCorridor :
			case tileChest :
			case tileDirtFloor :
			case tileDoor :
			case tileUpStairs :
				//Player is walking into a tile they are allowed to, move around the tiles.
				setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
				intTempTile = getCell(intPlayerNewX,intPlayerNewY); //Set the temp value to what the next cell is.
				intPlayerY = intPlayerNewY;
				intPlayerX = intPlayerNewX;
				setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
				return'F'; //Return a false, as they did not find the exit.
				break;
			default :
				//Player is stepping on a tile that should never exist, if I remember to add it.
				//Therefore just return a false.
				return 'F';
				break;
		//End of switch based on next cell.	
		}
	//End of PlayerMovement function.
	}
	
	
public:
    Dungeon()
    {
        xmax = 80;
        ymax = 20;
 
        xsize = 0;
        ysize = 0;
 
        objects = 10;
 
        chanceRoom = 80;
        chanceCorridor = 25;
 
        msgXSize = "X size of dungeon: \t";
        msgYSize = "Y size of dungeon: \t";
        msgMaxObjects = "max # of objects: \t";
        msgNumObjects = "# of objects made: \t";
        msgHelp = "";
        msgDetailedHelp = "";
 
        cmain();
    }
};

#endif
