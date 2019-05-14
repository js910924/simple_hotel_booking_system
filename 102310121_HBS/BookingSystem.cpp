#include "BookingSystem.h"

BookingSystem::BookingSystem()
{
	LoadHotelAndRoomData("RoomData.txt");
}

int BookingSystem::GetBonus() const
{
	return _bonus;
}

const vector<AbstractHotel*>* BookingSystem::GetHotels() const
{
	return &_hotels;
}

const vector<Payment*>* BookingSystem::GetPayments() const
{
	return &_payments;
}

void BookingSystem::SetBonus(int bonus)
{
	_bonus = bonus;
}

void BookingSystem::BookHotel(AbstractHotel* hotel, Room* room)
{
	hotel->BookRoom(room);
	_payments.push_back(new Payment(hotel, room));
}

void BookingSystem::LoadHotelAndRoomData(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);

	if (file.fail())
	{
		cout << "Can't find file!" << endl;
	}
	else
	{
		string str;

		while (getline(file, str, '\n'))		// 逐行讀取
		{
			vector<string> roomData;
			istringstream is(str);
			string partStr;
			while (is >> partStr)				// 利用文字串流，將此行文字依空格分開，並push_back至roomData裡		
			{
				roomData.push_back(partStr);
			}

			if (_hotels.size() == 0)			// 若_hotels裡沒有任何Hotel，則新增Hotel並將房間資訊加入該Hotel
			{
				_hotels.push_back(new Hotel(roomData[0]));
				_hotels[0]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
			}
			else
			{
				bool isFindSameHotel = false;
				for (int i = 0; i < _hotels.size(); i++)
				{
					if (_hotels[i]->GetName() == roomData[0])	// 若_hotels裡已有該飯店名稱，則將房間資訊加入Hotel
					{
						_hotels[i]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
						isFindSameHotel = true;
					}
				}
				if (isFindSameHotel == false)					// 若_hotels裡沒有該飯店名稱，則新增一個Hotel並將房間資訊加入該Hotel
				{
					_hotels.push_back(new Motel(roomData[0]));
					_hotels[_hotels.size() - 1]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
				}
			}
		}
	}
}