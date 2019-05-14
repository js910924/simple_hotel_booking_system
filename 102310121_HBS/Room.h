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
	string _number, _name; // 房間編號，名稱
	int _price;	// 房間價格
	bool _isBooked = false;		// 房間是否已被預訂，初始值設為false
};

#endif