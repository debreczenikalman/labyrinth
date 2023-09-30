#ifndef ROOM
#define ROOM

#include "Room.hpp"

#include "Platform.cpp"

#ifdef LINUX
#include "Tile.hpp"
#endif
#ifdef WINDOWS
#include "Tile.cpp"
#endif


Room::Room()
{
	this->height = 0;
	this->width = 0;
	tiles = nullptr;
}
Room::Room(int height, int width)
{
	this->height = height;
	this->width = width;
	tiles = new Tile * *[width];
	for (int i = 0; i < width; i++)
	{
		tiles[i] = new Tile * [height];
		for (int j = 0; j < height; j++)
		{
			tiles[i][j] = new Tile(Tile::TileType::Floor, Point{ i, j });
			if (i * j == 0 || i == width - 1 || j == height - 1)
			{
				tiles[i][j]->SetTileType(Tile::TileType::Wall);
			}
		}
	}
}
Room::~Room()
{
	for (int i = 0; i < width; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
	for (int i = 0; i < MAX_NEIGHBOUR_COUNT; i++)
	{
		// delete passages[i];
	}
}
Tile*** Room::GetTiles()
{
	return tiles;
}

#endif