#ifndef ROOM_H
#define ROOM_H

#include "Tile.hpp"
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