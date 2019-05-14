#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

using namespace std;

class Room
{
public:
	Room(string number, string name, int price);
	Room();

	void SetNumber(string number);
	void SetName(string name);
	void SetPrice(int price);
	void Book(bool book);

	string GetDetail() const;
	string GetNumber() const;
	string GetName() const;
	int GetPrice() const;
	bool IsBooked() const;

private:
	string _number, _name; // �ж��s���A�W��
	int _price;	// �ж�����
	bool _isBooked = false;		// �ж��O�_�w�Q�w�q�A��l�ȳ]��false
};

#endif