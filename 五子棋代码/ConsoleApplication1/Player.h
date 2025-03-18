#pragma once
#include<string>
#include"Chess.h"
using namespace std;
class Player
{
public:
	Player();
	int getcolor();
	void setcolor(int color);
	Player(string name, int color);
	string getname();
	void setName(string name);
	virtual Chess play_chess();
private:
	string name;
	int color;
};

