#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include "Payment.h"
#include <fstream>
#include <sstream>

class BookingSystem
{
public:
	BookingSystem();
	
	int GetBonus() const;
	const vector<AbstractHotel*>* GetHotels() const;
	const vector<Payment*>* GetPayments() const;

	void SetBonus(int bonus);

	void BookHotel(AbstractHotel* hotel, Room* room);
	
private:
	int _bonus = 0;
	vector<AbstractHotel*> _hotels;
	vector<Payment*> _payments;
	void LoadHotelAndRoomData(string fileName);
};

#endif