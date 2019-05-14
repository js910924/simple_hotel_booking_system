#include "Room.h"

Room::Room(string number, string name, int price)	// constructor
{
	_number = number;
	_name = name;
	_price = price;
}

Room::Room()	// default constructor
{
	_number = "0000";
	_name = "Unnamed Room";
	_price = 0;
}

void Room::SetNumber(string number)
{
	_number = number;
}

void Room::SetName(string name)
{
	_name = name;
}

void Room::SetPrice(int price)
{
	_price = price;
}

void Room::Book(bool book)
{
	_isBooked = book;
}

string Room::GetDetail() const
{
	if (!_isBooked)
	{
		return "[-] Room number: " + _number + ", name: " + _name + ", price: " + to_string(_price) + ".";
	}

	return "[X] Room number: " + _number + ", name: " + _name + ", price: " + to_string(_price) + ".";
}

string Room::GetNumber() const
{
	return _number;
}

string Room::GetName() const
{
	return _name;
}

int Room::GetPrice() const
{
	return _price;
}

bool Room::IsBooked() const
{
	return _isBooked;
}