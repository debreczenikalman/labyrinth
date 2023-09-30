#ifndef ROOM_H
#define ROOM_H


#include "Platform.cpp"

#ifdef LINUX
#include "Tile.hpp"
#endif
#ifdef WINDOWS
#include "Tile.hpp"
#endif

#define MAX_NEIGHBOUR_COUNT 10

class Room
{
public:
	Room();
	Room(int height, int width);
	~Room();
	Tile*** GetTiles();

private:

	Tile*** tiles;
	// Room* neighbours[MAX_NEIGHBOUR_COUNT];
	int passagesCount = 0;
	// Passage* passages[MAX_NEIGHBOUR_COUNT];
	int width, height;
};

#endif