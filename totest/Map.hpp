#ifndef MAP_H
#define MAP_H

#include "Room.hpp"

class Map
{
public:
	Room** rooms;

	~Map();

	static Map* GetInstance(int roomsCount);
	static Map* GetInstance();
	void ChangeRoom(int target);
	int GetActiveRoom();
private:
	Map();
	Map(int roomsCount);
	static Map* instPtr;
	int activeRoom;
	int roomsCount;
};

Map* Map::instPtr = nullptr;


#endif