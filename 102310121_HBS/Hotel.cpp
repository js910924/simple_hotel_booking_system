#include "Hotel.h"

int Hotel::GetBonusByPrice(int price)
{
	if (price > 5000)
	{
		return price * 0.5;
	}
	else if (price > 3000)
	{
		return price * 0.4;
	}
	return price * 0.3;
}

string Hotel::GetDetail()
{
	return "Hotel name: " + AbstractHotel::GetName();
}