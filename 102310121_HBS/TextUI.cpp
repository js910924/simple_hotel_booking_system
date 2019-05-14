#include "TextUI.h"

void TextUI::Run()
{
	while (true)
	{
		ShowMenu();
		string function;
		while (cin >> function)		// 輸入欲執行功能之代碼
		{
			if (IsStringNumber(function)) // 檢查輸入是否正確
			{
				break;
			}
			cout << "錯誤輸入，請重新輸入 :";
		}
		cout << endl;

		switch (stoi(function))		// 將輸入轉為int
		{
		case 1:				// 若輸入為1，顯示所有房間
			ShowHotelsAndRooms();
			break;

		case 2:				// 若輸入為2，訂房間
			BookHotel();
			break;

		case 3:				// 若輸入為3，顯示所有訂單
			ShowPayments();
			break;
			
		case 4:				// 若輸入為4，離開
			Exit();
			break;

		default:			// 錯誤輸入則跳回主選單並重新輸入
			cout << "錯誤輸入，請重新輸入" << endl;
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

int TextUI::ChooseHotel(int hotelSize)		// 輸入號碼選擇要訂哪間飯店，並回傳號碼 - 1
{
	cout << "Please enter a number choose the hotel:" << endl;
	cout << endl;
	for (int i = 0; i < hotelSize; i++)		// 列出所有飯店
	{
		cout << i + 1 << ". " << _bookingSystem.GetHotels()->at(i)->GetName() << endl;
	}

	cout << endl;

	int option = stoi(InputOption(1, hotelSize)) - 1;	// 輸入號碼 (因option用於vector的index值，所以 - 1)

	return option;
}

string TextUI::InputOption(int min, int max)
{
	string input;
	while (cin >> input)
	{
		if (IsStringNumber(input))
		{
			if (stoi(input) >= min && stoi(input) <= max)	// 若input在min跟max之間，則回傳input
			{
				cout << endl;
				return input;
			}
		}
			
		cout << "錯誤輸入，請重新輸入 : ";
	}
}

int TextUI::ChooseRoom(int optionHotel, vector<Room*>& unbookedRooms)	// 輸入號碼選擇要訂該飯店的哪間房間，並回傳號碼 - 1
{
	cout << "Please enter a number to choose the room:" << endl;
	cout << endl;

	AbstractHotel* hotel = _bookingSystem.GetHotels()->at(optionHotel);		// hotel為使用者選擇的飯店
	Room* roomPtr;
	int countRoom = 0;

	for (int i = 0; i < hotel->GetRooms()->size(); i++)
	{
		roomPtr = hotel->GetRooms()->at(i);
		if (!roomPtr->IsBooked())		// 若房間沒有被預訂
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

		cout << "錯誤輸入，請重新輸入 : ";
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
	exit(0);			// 結束程式
}

bool TextUI::IsStringNumber(string str)		// 檢查輸入是否為整數
{
	for (int i = 0; i < str.size(); i++)
	{
		if ((str[i] - '0') > 9 || (str[i] - '0') < 0)	// 若不是0~9的數字，則回傳false
		{
			return false;
		}
	}

	return true;
}