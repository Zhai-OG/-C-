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
	void initPlayer();    //��ʼ����������
	void decideOrder();   //�����Ⱥ���  ���
	void initGame();      //��ʼ����Ϸ��ģʽ�������Ⱥ���
	void startGame();
private:
	Human human1, human2;
	AI ai;
	Player* player1, * player2;//��ҽ϶�ʱ��������ָ������ָ�������ң���������ֻ�
	Player* first_hand, * second_hand,*current_hand;

	Judge judge;
	ChessBoard board=ChessBoard(ROW,COL);
	Display display;
	int mode; //����ģʽ 
};

