#include "TextUI.h"

void TextUI::Run()
{
	while (true)
	{
		ShowMenu();
		string function;
		while (cin >> function)		// ��J������\�ध�N�X
		{
			if (IsStringNumber(function)) // �ˬd��J�O�_���T
			{
				break;
			}
			cout << "���~��J�A�Э��s��J :";
		}
		cout << endl;

		switch (stoi(function))		// �N��J�ରint
		{
		case 1:				// �Y��J��1�A��ܩҦ��ж�
			ShowHotelsAndRooms();
			break;

		case 2:				// �Y��J��2�A�q�ж�
			BookHotel();
			break;

		case 3:				// �Y��J��3�A��ܩҦ��q��
			ShowPayments();
			break;
			
		case 4:				// �Y��J��4�A���}
			Exit();
			break;

		default:			// ���~��J�h���^�D���í��s��J
			cout << "���~��J�A�Э��s��J" << endl;
		}
	}
}

void TextUI::ShowMenu()
{
	cout << "Hotel Booking System [Main Menu]" << endl;
	cout << "Please enter a action to do:\n1. Show all rooms.\n2. Book rooms.\n3. Payment.\n4. Exit." << endl;
	cout << endl;
}

void TextUI::ShowHotelsAndRooms()
{
	cout << "[Room Lists]:" << endl;
	cout << endl;

	for (int hotelCounter = 0; hotelCounter < _bookingSystem.GetHotels()->size(); hotelCounter++)
	{
		cout << "[" << _bookingSystem.GetHotels()->at(hotelCounter)->GetDetail() << "]" << endl;
		for (int roomCounter = 0; roomCounter < _bookingSystem.GetHotels()->at(hotelCounter)->GetRooms()->size(); roomCounter++)
		{
			cout << _bookingSystem.GetHotels()->at(hotelCounter)->GetRooms()->at(roomCounter)->GetDetail() << endl;		// get room detail
		}

		cout << endl;
	}
}

void TextUI::BookHotel()
{
	int optionHotel, optionRoom;
	vector<Room*> unbookedRooms;

	optionHotel = ChooseHotel(_bookingSystem.GetHotels()->size());

	if (!_bookingSystem.GetHotels()->at(optionHotel)->GetUnbookedRoomNumber())
	{
		cout << "The rooms in this hotel have been booked." << endl;
	}
	else
	{
		cout << "You choose [" << _bookingSystem.GetHotels()->at(optionHotel)->GetName() << "]." << endl;
		optionRoom = ChooseRoom(optionHotel, unbookedRooms);

		cout << "This is the room detail:" << endl;
		cout << unbookedRooms[optionRoom]->GetDetail() << endl;
		cout << "Book this? (y/n)" << endl;
		cout << endl;

		if (IsInputYes())
		{
			cout << "Your current have " << _bookingSystem.GetBonus() << " bonus point(s)." << endl;
			cout << "Do you want to use bonus point(s) to pay for the room? (y/n)" << endl;
			cout << endl;

			bool isBonusPay = IsInputYes();
			if (isBonusPay)
			{
				if (_bookingSystem.GetBonus() >= unbookedRooms[optionRoom]->GetPrice())
				{
					cout << "You have enough bonus($" << _bookingSystem.GetBonus() << ") to pay the room." << endl;
					cout << "So we'll use your bonus to pay the room." << endl;
				}
				else
				{
					cout << "You need to pay $" << unbookedRooms[optionRoom]->GetPrice() << " (room price) - $"
						<< _bookingSystem.GetBonus() << " (bonus) = $"
						<< unbookedRooms[optionRoom]->GetPrice() - _bookingSystem.GetBonus() << "." << endl;
				}
			}
			else
			{
				cout << "You need to pay $" << unbookedRooms[optionRoom]->GetPrice() << " (room price)." << endl;
			}

			cout << "Are you sure? (y/n)" << endl;
			cout << endl;

			if (IsInputYes())
			{
				int newBonus;
				if (isBonusPay)
				{
					if (_bookingSystem.GetBonus() < unbookedRooms[optionRoom]->GetPrice())
					{
						newBonus = _bookingSystem.GetHotels()->at(optionHotel)->GetBonusByPrice(unbookedRooms[optionRoom]->GetPrice() - _bookingSystem.GetBonus());
					}
					else
					{
						newBonus = _bookingSystem.GetBonus() - unbookedRooms[optionRoom]->GetPrice();
					}
				}
				else
				{
					newBonus = _bookingSystem.GetBonus() + _bookingSystem.GetHotels()->at(optionHotel)->GetBonusByPrice(unbookedRooms[optionRoom]->GetPrice());
				}

				_bookingSystem.SetBonus(newBonus);
				_bookingSystem.BookHotel(_bookingSystem.GetHotels()->at(optionHotel), unbookedRooms[optionRoom]);

				cout << "Book successfully!" << endl;
				cout << "You now have " << _bookingSystem.GetBonus() << " bonus." << endl;
			}
			else
			{
				cout << "Bye" << endl;
			}
		}
		else
		{
			cout << "Bye" << endl;
		}
	}

	cout << endl;
}

int TextUI::ChooseHotel(int hotelSize)		// ��J���X��ܭn�q���������A�æ^�Ǹ��X - 1
{
	cout << "Please enter a number choose the hotel:" << endl;
	cout << endl;
	for (int i = 0; i < hotelSize; i++)		// �C�X�Ҧ�����
	{
		cout << i + 1 << ". " << _bookingSystem.GetHotels()->at(i)->GetName() << endl;
	}

	cout << endl;

	int option = stoi(InputOption(1, hotelSize)) - 1;	// ��J���X (�]option�Ω�vector��index�ȡA�ҥH - 1)

	return option;
}

string TextUI::InputOption(int min, int max)
{
	string input;
	while (cin >> input)
	{
		if (IsStringNumber(input))
		{
			if (stoi(input) >= min && stoi(input) <= max)	// �Yinput�bmin��max�����A�h�^��input
			{
				cout << endl;
				return input;
			}
		}
			
		cout << "���~��J�A�Э��s��J : ";
	}
}

int TextUI::ChooseRoom(int optionHotel, vector<Room*>& unbookedRooms)	// ��J���X��ܭn�q�Ӷ����������ж��A�æ^�Ǹ��X - 1
{
	cout << "Please enter a number to choose the room:" << endl;
	cout << endl;

	AbstractHotel* hotel = _bookingSystem.GetHotels()->at(optionHotel);		// hotel���ϥΪ̿�ܪ�����
	Room* roomPtr;
	int countRoom = 0;

	for (int i = 0; i < hotel->GetRooms()->size(); i++)
	{
		roomPtr = hotel->GetRooms()->at(i);
		if (!roomPtr->IsBooked())		// �Y�ж��S���Q�w�q
		{
			countRoom++;
			cout << countRoom << ". " << roomPtr->GetName() << endl;
			unbookedRooms.push_back(roomPtr);
		}
	}

	cout << endl;

	int option = stoi(InputOption(1, countRoom)) - 1;

	return option;
}

bool TextUI::IsInputYes()
{
	string input;
	while (cin >> input)
	{
		if (input == "y" | input == "Y")
		{
			cout << endl;
			return true;
		}
		else if (input == "N" | input == "n")
		{
			cout << endl;
			return false;
		}

		cout << "���~��J�A�Э��s��J : ";
	}
}

void TextUI::ShowPayments()
{
	bool isEmpty = true;
	for (int i = 0; i < _bookingSystem.GetPayments()->size(); i++)
	{
		cout << _bookingSystem.GetPayments()->at(i)->GetDetail() << endl;
		isEmpty = false;
	}
	if (isEmpty)
	{
		cout << "No payment." << endl;
	}
	cout << endl;
}

void TextUI::Exit()
{
	cout << "Goodbye~~~~" << endl;
	system("pause");
	exit(0);			// �����{��
}

bool TextUI::IsStringNumber(string str)		// �ˬd��J�O�_�����
{
	for (int i = 0; i < str.size(); i++)
	{
		if ((str[i] - '0') > 9 || (str[i] - '0') < 0)	// �Y���O0~9���Ʀr�A�h�^��false
		{
			return false;
		}
	}

	return true;
}