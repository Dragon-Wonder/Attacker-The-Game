#include "rooms.h"
#include "player.h"
#include "global.h"
/*****************************************************************************/
unsigned char intTempTile = 0x6; //Value to hold what the cell that the player is moving into is.
/*****************************************************************************/
//Static members
int Dungeon::dungeon_map[DEFINED_MAP_WIDTH * DEFINED_MAP_HEIGHT];
MapStc Dungeon::mapstats;
/*****************************************************************************/
Dungeon::Dungeon() {
	mapstats.max.x = DEFINED_MAP_WIDTH;
	mapstats.max.y = DEFINED_MAP_HEIGHT;

	mapstats.size.x = DEFINED_MAP_WIDTH;
	mapstats.size.y = DEFINED_MAP_HEIGHT;

	mapstats.objects = 0;

	mapstats.chanceRoom = DEFINED_MAP_ROOM_CHANCE;
	mapstats.chanceCorridor = DEFINED_MAP_CORRIDOR_CHANCE;
	//cmain();
}
/*****************************************************************************/
void Dungeon::setCell(int x, int y, int celltype) {dungeon_map[x + mapstats.size.x * y] = celltype;}
/*****************************************************************************/
int Dungeon::getCell(int x, int y) {return dungeon_map[x + mapstats.size.x * y];}
/*****************************************************************************/
void Dungeon::setCell(LOC l, int celltype) {dungeon_map[l.x + mapstats.size.x * l.y] = celltype;}
/*****************************************************************************/
int Dungeon::getCell(LOC l) {return dungeon_map[l.x + mapstats.size.x * l.y];}
/*****************************************************************************/
int Dungeon::getRand(int min, int max) {
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
/*****************************************************************************/
bool Dungeon::makeCorridor(int x, int y, int lenght, int direction) {
	int len = getRand(2, lenght);
	int floor = tileCorridor;
	int dir = 0;
	if(direction > 0 && direction < 4) dir = direction;
	int xtemp = 0;
	int ytemp = 0;
	switch(dir) {
		case 0:
		{
			if(x < 0 || x > mapstats.size.x) return false;
			else xtemp = x;
			for(ytemp = y; ytemp > (y-len); ytemp--)
			{
				if(ytemp < 0 || ytemp > mapstats.size.y) return false;
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
			if(y < 0 || y > mapstats.size.y) return false;
			else ytemp = y;

			for(xtemp = x; xtemp < (x + len); xtemp++)
			{
				if(xtemp < 0 || xtemp > mapstats.size.x) return false;
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
			if(x < 0 || x > mapstats.size.x) return false;
			else xtemp = x;
			for(ytemp = y; ytemp < (y + len); ytemp++)
			{
				if(ytemp < 0 || ytemp > mapstats.size.y) return false;
				if(getCell(xtemp, ytemp) != tileUnused) return false;
			}
			for (ytemp = y; ytemp < (y+len); ytemp++){
				setCell(xtemp, ytemp, floor);
			}
		break;
		}
		case 3:
		{
			if (ytemp < 0 || ytemp > mapstats.size.y) return false;
			else ytemp = y;

			for (xtemp = x; xtemp > (x-len); xtemp--){
				if (xtemp < 0 || xtemp > mapstats.size.x) return false;
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
/*****************************************************************************/
bool Dungeon::makeRoom(int x, int y, int xlength, int ylength, int direction){
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
			if (ytemp < 0 || ytemp > mapstats.size.y) return false;
			for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
				if (xtemp < 0 || xtemp > mapstats.size.x) return false;
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
			if (ytemp < 0 || ytemp > mapstats.size.y) return false;
			for (int xtemp = x; xtemp < (x+xlen); xtemp++){
				if (xtemp < 0 || xtemp > mapstats.size.x) return false;
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
			if (ytemp < 0 || ytemp > mapstats.size.y) return false;
			for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++){
				if (xtemp < 0 || xtemp > mapstats.size.x) return false;
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
			if (ytemp < 0 || ytemp > mapstats.size.y) return false;
			for (int xtemp = x; xtemp > (x-xlen); xtemp--){
				if (xtemp < 0 || xtemp > mapstats.size.x) return false;
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
/*****************************************************************************/
/* void Dungeon::showDungeon(){
	int PlayerStatus = getbattlevalue(statStatus);
	for (int y = 0; y < mapstats.size.y; y++){
		for (int x = 0; x < mapstats.size.x; x++){
			//System.out.print(getCell(x, y));
			switch(getCell(x, y)){
			case tileUnused:
				if (PlayerStatus == effectBlinded) {printf(" ");}
				else {printf("¦");}
				break;
			case tileDirtWall:
				if (PlayerStatus == effectBlinded) {printf(" ");}
				else {printf("¦");}
				break;
			case tileDirtFloor:
				printf(" ");
				break;
			case tileStoneWall:
				printf("¦");
				break;
			case tileCorridor:
				printf(" ");//¦
				break;
			case tileDoor:
				if (PlayerStatus == effectBlinded) {printf(" ");}
				else {printf("$");}
				break;
			case tileUpStairs:
				printf("<");
				break;
			case tileDownStairs:
				printf(">");
				break;
			case tileChest:
				if (PlayerStatus == effectBlinded) {printf(" ");}
				else {printf("#");}
				break;
			case tilePlayer:
				printf("@");
				break;
			case tileLockedDoor:
				if (PlayerStatus == effectBlinded) {printf(" ");}
				else {printf("!");}
				break;
			};
		}
		//if (mapstats.size.x <= mapstats.max.x) printf("\n");
	}
} */
/*****************************************************************************/
bool Dungeon::createDungeon(int inx, int iny, int inobj){
	if (inobj < 1) mapstats.objects = 10;
	else mapstats.objects = inobj;
	if (inx < 3) mapstats.size.x = 3;
	else if (inx > mapstats.max.x) mapstats.size.x = mapstats.max.x;
	else mapstats.size.x = inx;
	if (iny < 3) mapstats.size.y = 3;
	else if (iny > mapstats.max.y) mapstats.size.y = mapstats.max.y;
	else mapstats.size.y = iny;
	//dungeon_map = new int[mapstats.size.x * mapstats.size.y];
	for (int y = 0; y < mapstats.size.y; y++){
		for (int x = 0; x < mapstats.size.x; x++){
			//ie, making the borders of unwalkable walls
			if (y == 0) setCell(x, y, tileStoneWall);
			else if (y == mapstats.size.y-1) setCell(x, y, tileStoneWall);
			else if (x == 0) setCell(x, y, tileStoneWall);
			else if (x == mapstats.size.x-1) setCell(x, y, tileStoneWall);
			//and fill the rest with dirt
			else setCell(x, y, tileUnused);
		}
	}

	/*******************************************************************************
	And now the code of the random-map-generation-algorithm begins!
	*******************************************************************************/
	//start with making a room in the middle, which we can start building upon
	makeRoom(mapstats.size.x/2, mapstats.size.y/2, 8, 6, getRand(0,3)); //getrand saken f????r att slumpa fram riktning p?? rummet
	//keep count of the number of "mapstats.objects" we've made
	int currentFeatures = 1; //+1 for the first room we just made
	//then we start the main loop
	for (int countingTries = 0; countingTries < 1000; countingTries++){
		//check if we've reached our quota
		if (currentFeatures == mapstats.objects){
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
			newx = getRand(1, mapstats.size.x-1);
			newy = getRand(1, mapstats.size.y-1);
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
			if (feature <= mapstats.chanceRoom){ //a new room
				if (makeRoom((newx+xmod), (newy+ymod), 8, 6, validTile)){
					currentFeatures++; //add to our quota

					//then we mark the wall opening with a door
					if(rand() % 101 <= 15) {setCell(newx, newy, tileLockedDoor);}
					else {setCell(newx, newy, tileDoor);}

					//clean up infront of the door so we can reach it
					setCell((newx+xmod), (newy+ymod), tileDirtFloor);
				}
			}
			else if (feature >= mapstats.chanceRoom){ //new corridor
				if (makeCorridor((newx+xmod), (newy+ymod), 6, validTile)){
					//same thing here, add to the quota and a door
					currentFeatures++;

					if(rand() % 101 <= 15) {setCell(newx, newy, tileLockedDoor);}
					else {setCell(newx, newy, tileDoor);}
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
			newx = getRand(1, mapstats.size.x-1);
			newy = getRand(1, mapstats.size.y-2); //cheap bugfix, pulls down newy to 0<y<24, from 0<y<25

			//System.out.println("x: " + newx + "\ty: " + newy);
			ways = 4; //the lower the better

			//check if we can reach the spot
			if (getCell(newx, newy+1) == tileDirtFloor || getCell(newx, newy+1) == tileCorridor){
			//north
				if (getCell(newx, newy+1) != tileDoor || getCell(newx, newy+1) != tileLockedDoor)
				ways--;
			}
			if (getCell(newx-1, newy) == tileDirtFloor || getCell(newx-1, newy) == tileCorridor){
			//east
				if (getCell(newx-1, newy) != tileDoor || getCell(newx-1, newy) != tileLockedDoor)
				ways--;
			}
			if (getCell(newx, newy-1) == tileDirtFloor || getCell(newx, newy-1) == tileCorridor){
			//south
				if (getCell(newx, newy-1) != tileDoor || getCell(newx, newy-1) != tileLockedDoor)
				ways--;
			}
			if (getCell(newx+1, newy) == tileDirtFloor || getCell(newx+1, newy) == tileCorridor){
			//west
				if (getCell(newx+1, newy) != tileDoor || getCell(newx+1, newy) != tileLockedDoor)
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
	return true;
}
/*****************************************************************************/
int* Dungeon::make_dungeon() {
    bool f;
	int x = DEFINED_MAP_WIDTH;
	int y = DEFINED_MAP_HEIGHT;
	int dungeon_objects = DEFINED_MAP_OBJECT_LIMIT;
	//dungeon_map = new int[x * y];
		intTempTile = tileUpStairs;
	if(createDungeon(x, y, dungeon_objects) && Global::blnDebugMode)
        {printf("Dungeon created.");}
	return dungeon_map;
}
/*****************************************************************************/
void Dungeon::cmain() {
	int x = DEFINED_MAP_WIDTH;
	int y = DEFINED_MAP_HEIGHT;
	int dungeon_objects = DEFINED_MAP_OBJECT_LIMIT;
	//dungeon_map = new int[x * y];
	if(createDungeon(x, y, dungeon_objects) && Global::blnDebugMode)
        {printf("Dungeon created.\n");}
	playerfind();
}
/*****************************************************************************/
void Dungeon::playerfind() {
    clsPlayer player;

	for (int y2 = 0; y2 < DEFINED_MAP_HEIGHT; y2++){
		for (int x2 = 0; x2 < DEFINED_MAP_WIDTH; x2++){
			if (getCell(x2,y2) == tilePlayer){ //Finds where player is.
                LOC newloc;
                newloc.x = x2;
                newloc.y = y2;
                player.setLocation(newloc);
				//Set x and y to max values so the for loops stop.
				x2 = DEFINED_MAP_WIDTH;
				y2 = DEFINED_MAP_HEIGHT;}}}
}
/*****************************************************************************/
/*
char Dungeon::PlayerMovement(char chrPlayerDirection) {
	unsigned char Status = getbattlevalue(statStatus);
	const char Dir[4] = {'N','S','E','W'};
	//If player is confused they move a random direction.

	if (Status != effectNone)
	{
		if (RemoveStatusEffect(getbattlevalue(statLuk),Status, getbattlevalue(statStatusCounter)))
		{
			printf("\n%s",EndOfEffectString("player",Status).c_str());
			setbattlevalue(statStatus,effectNone);
			setbattlevalue(statStatusCounter,0);
		}
		else {setbattlevalue(statStatusCounter,getbattlevalue(statStatusCounter)+1);}
	}
	if (Status == effectConfused && (chrPlayerDirection == 'N' || chrPlayerDirection == 'E' || chrPlayerDirection == 'W' ||chrPlayerDirection == 'S'))
	{
			chrPlayerDirection = Dir[rand() % 4];
			printf("\nYou are confused and don't know where to go.");
	}
	playerfind();
	intPlayerNewX = intPlayerX;
	intPlayerNewY = intPlayerY;
	string strStatus;
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
			for(int i = 0; i < 48; i++) {printf("\n");}
			printf("Are you sure you want to exit the game?\nAll progress will be lost.\nY or N\n> ");
			cin>>chrPlayerDirection;
			//scanf("%c",&chrPlayerDirection);
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
		case 'V' : //Player wants to save.
			return 'S'; //Player is asking to save, return S for save.
			break;
		case 'H' : //Player wants to heal.
			unsigned int intPlayerCurrHealth;
			intPlayerCurrHealth = getbattlevalue(statCurrHealth);
			unsigned int intPlayerMaxHealth;
			intPlayerMaxHealth = getbattlevalue(statMaxHealth);
			unsigned int intPlayerHealAmount;
			intPlayerHealAmount = floor(intPlayerMaxHealth/10.0);
			if (intPlayerCurrHealth + intPlayerHealAmount >= intPlayerMaxHealth) {intPlayerCurrHealth = intPlayerMaxHealth;}
			else {intPlayerCurrHealth += intPlayerHealAmount;}
			setbattlevalue(statCurrHealth,intPlayerCurrHealth); //Set player current health to the new amount.
			printf("\nYour health is now: %d out of %d.",intPlayerCurrHealth,intPlayerMaxHealth);
			return 'F'; //Return F that player did not find exit.
			break;
		case 'C' : //Player is checking themselves.
			int intPlayerStatsTemp[7];
			for (int i = 0; i < 7; i++) {intPlayerStatsTemp[i]=getbattlevalue(i);}
			printf("\nYour health is now: %d out of %d.\n",intPlayerStatsTemp[5],intPlayerStatsTemp[6]);
			printf("Your stats are as follows: \n");
			printf("STR: %d\nCONS: %d\nDEF: %d\nDEX: %d\nLUK: %d\n",intPlayerStatsTemp[0],intPlayerStatsTemp[1],intPlayerStatsTemp[2],intPlayerStatsTemp[3],intPlayerStatsTemp[4]);
			if (Status == effectNone) {strStatus = "NONE";}
			else if (Status == effectBlinded) {strStatus = "Blinded";}
			else if (Status == effectFrozen) {strStatus = "Frozen";}
			else if (Status == effectBurned) {strStatus = "Burned";}
			else if (Status == effectWet) {strStatus = "Wet";}
			else if (Status == effectPoison) {strStatus = "Poisoned";}
			else if (Status == effectBleeding) {strStatus = "Bleeding";}
			else if (Status == effectConfused) {strStatus = "Confused";}
			else {strStatus = "ERROR";}
			printf("Current status effect: %s\n",strStatus.c_str());
			getchar();
			return 'F';
			break;
		//Debug commands & invalid choice here
		case 'L' : //Debug code to go straight to stairs.
			if (Global::blnDebugMode)
			{for (int y = 0; y < DEFINED_MAP_HEIGHT; y++){for (int x = 0; x < DEFINED_MAP_WIDTH; x++){
				if (getCell(x,y)==tileDownStairs) //Finds where the down stairs are.
				{
					intPlayerNewX = x;
					intPlayerNewY = y;
					goto PostMovingCode;
				};
			}} break;}
		case 'M' :
			if (Global::blnDebugMode) {return 'M'; break;}
		default :
			printf("\nInvalid choice, please try again.\n");
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
		case tileLockedDoor:
			//Player Encounters a Locked Door
			LockedDoorStart:
			printf("\n\n\n\n\nThis door is locked!\nWhat do you want to do?");
			printf("\n[B]reak it\n");
			printf("[U]se Key\n");
			printf("[P]ick Lock\n");
			printf("[L]eave\n");

			cin>>chrPlayerDirection;
			//scanf("%c",&chrPlayerDirection);
			chrPlayerDirection = CharConvertToUpper(chrPlayerDirection);

			switch(chrPlayerDirection)
			{
				case 'L' :
					//Player does not attempt to unlocked door return F
					return 'F';
					break;
				case 'B' :
					//Player attempts to break the door.
					if(getbattlevalue(statStr) >= 60)
					{
						//Player breaks down the door
						printf("\nYou back up several paces from the door to get a running start. You run at the door, full speed, and ram the door. The wooden door breaks easily under your massive strength.\n\n");
						getchar();
						setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
						intTempTile = tileCorridor; //Set the temp value to a blank spot because the door was broken down.
						intPlayerY = intPlayerNewY;
						intPlayerX = intPlayerNewX;
						setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
						return 'F';
					}
					else
					{
						//Player fails to break down the door
						printf("\nYou slam into the door as hard as you can, but it does not budge.\n");
						goto LockedDoorStart;
					}
					break;
				case 'U' :
					//Player uses key if they have one
					if(getbattlevalue(statKeys) > 0)
					{
						//Player has at least one key.
						printf("You used a key to unlock the door. You now have %d keys\n\n",getbattlevalue(statKeys) - 1);
						getchar();
						setbattlevalue(statKeys,getbattlevalue(statKeys) - 1);
						setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
						intTempTile = tileDoor; //Set the temp value to a normal door since player unlocked it.
						intPlayerY = intPlayerNewY;
						intPlayerX = intPlayerNewX;
						setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
						return 'F';
					}
					else
					{
						//Player does not have any keys.
						printf("\nYou do not have any keys!\nFight monsters until you get one.\n");
						getchar();
						goto LockedDoorStart;
					}
					break;
				case 'P' :
					//Player attempts to pick the lock
					if(getbattlevalue(statLuk) >= 60)
					{
						//Player picks the lock.
						printf("\nYou move your lock-pick around a hear a *CLICK* you opened the door without any issue.\n");
						getchar();
						setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
						intTempTile = tileDoor; //Set the temp value to a normal door since player unlocked it.
						intPlayerY = intPlayerNewY;
						intPlayerX = intPlayerNewX;
						setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
						return 'F';
					}
					else
					{
						//Player fails to pick the lock.
						printf("\nYou fiddle with the lock, but you break your lock-pick before the lock gives.\n");
						goto LockedDoorStart;
					}
					break;
					break;
				default:
					printf("\nYou have selected an invalid option, please try again.\n\n\n");
					goto LockedDoorStart;
					break;
			}


		default :
			//Player is stepping on a tile that should never exist, if I remember to add it.
			//Therefore just return a false.
			return 'F';
			break;
	//End of switch based on next cell.
	}
//End of PlayerMovement function.
} */
/*****************************************************************************/

