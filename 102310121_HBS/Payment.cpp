#include "Payment.h"

Payment::Payment(AbstractHotel* hotel, Room* room)
{
	_hotel = hotel;
	_room = room;
}

string Payment::GetDetail() const
{
	return _hotel->GetDetail() + ", Room Number: " + _room->GetNumber() + ", name: "
		+ _room->GetName() + ", price: " + to_string(_room->GetPrice()) + ".";
}