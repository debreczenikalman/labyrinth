#ifndef TILE_H
#define TILE_H

#include "Point.cpp"
#include "DDelegate.hpp"

class Tile
{

public:

	DDelegate<void, Tile*>* OnEnter;
	DDelegate<void, Tile*>* OnLeave;
	DDelegate<void, Tile*>* OnStay;
	enum TileType { Other = 0, Wall = 1, Floor = 2, Passage = 3 };

	Tile();

	Tile(char icon, Point coords, bool passable);

	Tile(TileType t, Point coords);

	~Tile();



	Point Coords();

	bool Passable();

	TileType GetTileType();

	void SetTileType(TileType t);

	char GetIcon();
	int GetTargetRoom();


private:
	void InitDelegates();
	int destination;
	char icon;
	Point coords;
	bool passable;
	// bool interactable;
	// bool playerHere;
	TileType tileType;


};


#endif