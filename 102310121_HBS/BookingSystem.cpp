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

		while (getline(file, str, '\n'))		// �v��Ū��
		{
			vector<string> roomData;
			istringstream is(str);
			string partStr;
			while (is >> partStr)				// �Q�Τ�r��y�A�N�����r�̪Ů���}�A��push_back��roomData��		
			{
				roomData.push_back(partStr);
			}

			if (_hotels.size() == 0)			// �Y_hotels�̨S������Hotel�A�h�s�WHotel�ñN�ж���T�[�J��Hotel
			{
				_hotels.push_back(new Hotel(roomData[0]));
				_hotels[0]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
			}
			else
			{
				bool isFindSameHotel = false;
				for (int i = 0; i < _hotels.size(); i++)
				{
					if (_hotels[i]->GetName() == roomData[0])	// �Y_hotels�̤w���Ӷ����W�١A�h�N�ж���T�[�JHotel
					{
						_hotels[i]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
						isFindSameHotel = true;
					}
				}
				if (isFindSameHotel == false)					// �Y_hotels�̨S���Ӷ����W�١A�h�s�W�@��Hotel�ñN�ж���T�[�J��Hotel
				{
					_hotels.push_back(new Motel(roomData[0]));
					_hotels[_hotels.size() - 1]->AddRooms(roomData[1], roomData[2], stoi(roomData[3]));
				}
			}
		}
	}
}