#include "Room.cpp"

class Map
{
private:
public:
    Room** rooms;
    Map()
    {

    }
	Map(int roomsCount)
    {
        rooms = new Room*[roomsCount];
    }
    ~Map()
    {
        delete rooms;
    }
};