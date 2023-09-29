#ifndef MAP
#define MAP

#include "Map.hpp"
#include "Room.cpp"


Map* Map::GetInstance(int roomsCount)
{
	if (instPtr == nullptr)
	{
		instPtr = new Map(roomsCount);

	}
	return instPtr;
}

Map::~Map()
{
	delete rooms;
}

Map* Map::GetInstance()
{
	if (instPtr == nullptr)
	{
		instPtr = new Map();
	}
	return instPtr;
}

void Map::ChangeRoom(int target)
{
	if (target < roomsCount)
	{
		activeRoom = target;
	}
}

int Map::GetActiveRoom()
{
	return activeRoom;
}


Map::Map()
{
	this->rooms = nullptr;
	this->roomsCount = 0;
	activeRoom = 0;
}

Map::Map(int roomsCount)
{
	this->roomsCount = roomsCount;
	rooms = new Room * [roomsCount];
	activeRoom = 0;
}


#endif