#ifndef PAYMENT_H
#define PAYMENT_H

#include "Hotel.h"
#include "Motel.h"

class Payment
{
public:
	Payment(AbstractHotel* hotel, Room* room);

	string GetDetail() const;

private:
	AbstractHotel* _hotel;
	Room* _room;
};

#endif