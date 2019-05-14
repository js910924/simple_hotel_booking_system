#ifndef MOTEL_H
#define MOTEL_H

#include "AbstractHotel.h"

class Motel : public AbstractHotel
{
public:
	Motel() : AbstractHotel() {}
	Motel(string name) : AbstractHotel(name) {}

	int GetBonusByPrice(int price) override;
	string GetDetail() override;
};

#endif