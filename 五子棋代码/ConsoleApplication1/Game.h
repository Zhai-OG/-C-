#pragma once
#include<iostream>
#include<string>
#include"Chess.h"
#include"ChessBoard.h"
#include"Display.h"
#include"Player.h"
#include"Judge.h"
#include"Human.h"
#include"AI.h"
class Game
{
public:
	Game();
	void Mode();
	void initPlayer();    //初始化参赛对象
	void decideOrder();   //决定先后手  随机
	void initGame();      //初始化游戏：模式、对象、先后手
	void startGame();
private:
	Human human1, human2;
	AI ai;
	Player* player1, * player2;//玩家较多时，可以用指针数组指向参与玩家，方便玩家轮换
	Player* first_hand, * second_hand,*current_hand;

	Judge judge;
	ChessBoard board=ChessBoard(ROW,COL);
	Display display;
	int mode; //对弈模式 
};

