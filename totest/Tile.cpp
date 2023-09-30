#ifndef TILE
#define TILE

#include "Point.cpp"

#include "Platform.cpp"

#include "Tile.hpp"

#ifdef LINUX
#include "DDelegate.cpp"
#endif
#ifdef WINDOWS
#include "DDelegate.cpp"
#endif





Tile::Tile() : icon('\0'), passable(true)
{
	coords.x = 0;
	coords.y = 0;

}

Tile::Tile(char icon, Point coords, bool passable)
{
	this->icon = icon;
	this->coords = coords;
	this->passable = passable;
}

Tile::Tile(TileType t, Point coords)
{
	this->coords = coords;
	SetTileType(t);
}

Tile::~Tile()
{

}


Point Tile::Coords()
{
	return coords;
}

bool Tile::Passable()
{
	return passable;
}

Tile::TileType Tile::GetTileType()
{
	return tileType;
}

void Tile::SetTileType(TileType t)
{
	Tile::OnEnter->UnsubrscribeAll();
	switch (t)
	{
	case Wall:
		this->icon = '#';
		this->passable = false;
		break;

	case Floor:
		this->icon = ' ';
		this->passable = true;
		break;

	case Other:
		this->icon = '\0';
		this->passable = false;
		break;
	case Passage:
		this->icon = 'O';
		this->passable = true;
		// OnEnter->Subscribe(&Enter); // TODO
		break;

	default:
		break;
	}
}

char Tile::GetIcon()
{
	return icon;
}

int Tile::GetTargetRoom()
{
	return destination;
}

void Tile::InitDelegates()
{
	OnEnter = new DDelegate<void, Tile*>();
}


#endif