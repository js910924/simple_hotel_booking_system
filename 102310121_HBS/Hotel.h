#ifndef HOTEL_H
#define HOTEL_H

#include "AbstractHotel.h"

class Hotel : public AbstractHotel
{
public:
	Hotel() : AbstractHotel() {}
	Hotel(string name) : AbstractHotel(name) {}

	int GetBonusByPrice(int price) override;
	string GetDetail() override;
};

#endif