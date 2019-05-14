#ifndef ABSTRACTHOTEL_H
#define ABSTRACTHOTEL_H

#include "Room.h"
#include <vector>

class AbstractHotel
{
public:
	AbstractHotel();
	AbstractHotel(string name);

	void SetName(string name);
	
	string GetName() const;
	const vector<Room*>* GetRooms() const;
	int GetUnbookedRoomNumber() const;
	virtual string GetDetail() = 0;

	void AddRooms(string number, string name, int price);
	void BookRoom(Room* room);
	virtual int GetBonusByPrice(int price) = 0;

private:
	string _name;
	vector<Room*> _rooms;
	int _unbookedRoomNumber = 0;
};

#endif