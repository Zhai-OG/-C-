#pragma once
#include"ChessBoard.h"
#include"Chess.h"
#include"Player.h"
class Human:public Player  //Player�ǹ��ԣ�Human���컯
{
public:
	//Position click_board(ChessBoard board);  //��������̸�������
	Human();
	virtual Chess play_chess();
private:
};

