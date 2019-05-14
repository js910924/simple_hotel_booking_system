#include "Motel.h"

int Motel::GetBonusByPrice(int price)
{
	if (price > 2000)
	{
		return 500;
	}
	else if (price > 1500)
	{
		return 300;
	}
	
	return 100;
}

string Motel::GetDetail()
{
	return "Motel name: " + AbstractHotel::GetName();
}