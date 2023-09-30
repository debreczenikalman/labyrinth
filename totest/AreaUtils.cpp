#ifndef AREAUTILS
#define AREAUTILS


#include "Tile.hpp"
#include "Map.hpp"


void ChangeRoom(Tile* caller)
{
	Map::GetInstance()->ChangeRoom(caller->GetTargetRoom());	
}

#endif