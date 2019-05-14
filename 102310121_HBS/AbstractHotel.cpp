#include "AbstractHotel.h"

AbstractHotel::AbstractHotel()
{
	_name = "Unnamed hotel";
}

AbstractHotel::AbstractHotel(string name)
{
	_name = name;
}

void AbstractHotel::SetName(string name)
{
	_name = name;
}

void AbstractHotel::AddRooms(string number, string name, int price)
{
	_rooms.push_back(new Room(number, name, price));
	_unbookedRoomNumber++;
}

string AbstractHotel::GetName() const
{
	return _name;
}

const vector<Room*>* AbstractHotel::GetRooms() const
{
	return &_rooms;
}

int AbstractHotel::GetUnbookedRoomNumber() const
{
	return _unbookedRoomNumber;
}

void AbstractHotel::BookRoom(Room* room)
{
	room->Book(true);
	_unbookedRoomNumber--;
}