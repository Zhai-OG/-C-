#pragma once
#include"ChessBoard.h"
#include"Chess.h"
#include"Player.h"
class Human:public Player  //Player是共性，Human是异化
{
public:
	//Position click_board(ChessBoard board);  //鼠标点击棋盘给出坐标
	Human();
	virtual Chess play_chess();
private:
};

