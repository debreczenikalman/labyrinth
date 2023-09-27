


#include "Point.cpp"

class Tile
{

public:
	const enum TileType { Other = 0, Wall = 1, Floor = 2, Passage = 3 };



	Tile() : icon('\0'), passable(true)
	{
		coords.x = 0;
		coords.y = 0;
	}

	Tile(char icon, Point coords, bool passable)
	{
		this->icon = icon;
		this->coords = coords;
		this->passable = passable;
	}

	Tile(TileType t, Point coords)
	{
		this->coords = coords;
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
		case Passage:
			this->icon = 'O';
			this->passable = true;
			// TODO: Event: stepped on door
			break;

		case Other:
			this->icon = '\0';
			this->passable = false;
			break;

		default:
			break;
		}
	}

	~Tile()
	{

	}



	Point Coords()
	{
		return coords;
	}

	bool Passable()
	{
		return passable;
	}

	TileType GetTileType()
	{
		return tileType;
	}

	void SetTileType(TileType t)
	{
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

		default:
			break;
		}
	}

	char GetIcon()
	{
		return icon;
	}

private:
	char icon;
	Point coords;
	bool passable;
	// bool interactable;
	// bool playerHere;
	TileType tileType;


};


static class TileFactory
{
private:

public:

};


