#ifndef TExTUI_H
#define TEXTUI_H

#include "BookingSystem.h"

class TextUI
{
public:
	TextUI(BookingSystem System) : _bookingSystem(System) {}
	void Run();

private:
	BookingSystem _bookingSystem;
	void ShowMenu();
	void ShowHotelsAndRooms();
// ---------------------------------------------------
	void BookHotel();
	int ChooseHotel(int hotelSize);
	string InputOption(int min, int max);
	int ChooseRoom(int optionHotel, vector<Room*>& unbookedRooms);
	bool IsInputYes();
// ---------------------------------------------------
	void ShowPayments();
	void Exit();
	bool IsStringNumber(string str); // �ˬd��J�O�_���Ʀr
};

#endif