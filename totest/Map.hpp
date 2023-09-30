#ifndef MAP_H
#define MAP_H

#include "Platform.cpp"

#ifdef LINUX
#include "Room.hpp"
#endif
#ifdef WINDOWS
#include "Room.hpp"
#endif

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




#endif