#define MAX_NEIGHBOUR_COUNT 10

#include "Tile.cpp"
#include "Passage.cpp"



class Room
{
public:
	Room()
	{

	}
	Room(int height, int width)
	{
		tiles = new Tile**[width];
		for (int i = 0; i < width; i++)
		{
			tiles[i] = new Tile * [height];
			for (int j = 0; j < height; j++)
			{
				tiles[i][j] = new Tile(Tile::TileType::Floor, Point{ i,j });
				if (i * j == 0 || i == width - 1 || j == height - 1)
				{
					tiles[i][j]->SetTileType(Tile::TileType::Wall);
				}
			}
		}

	}
	~Room()
	{
		for (int i = 0; i < width; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;
		for (int i = 0; i < MAX_NEIGHBOUR_COUNT; i++)
		{
			delete passages[i];
		}
	}
	Tile*** GetTiles()
	{
		return tiles;
	}
	
	void AddPassage(Point loc, Room* destination)
	{
		passages[passagesCount++] = new Passage();
	}


private:

	Tile*** tiles;
	// Room* neighbours[MAX_NEIGHBOUR_COUNT];
	int passagesCount = 0;
	Passage* passages[MAX_NEIGHBOUR_COUNT];
	int width, height;
};