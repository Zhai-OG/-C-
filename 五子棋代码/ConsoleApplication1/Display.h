#pragma once
#include "ChessBoard.h"
class Display
{
public:
	Display();
	~Display();
	void showBoard(ChessBoard board); //��ʾ����
	void showMessage(string msg);     
};


