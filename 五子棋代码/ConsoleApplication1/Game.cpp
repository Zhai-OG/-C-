#include "Game.h"
#include"AI.h"
#define MAX_SCORE (10000000)
#define MIN_SCORE (-10000000)
#define DEPTH (3)  // 搜索算法层数
void Game::initPlayer() {
	string name;
	if (mode == 2) {
		player1 = &human1;
		player2 = &human2;
		display.showMessage("玩家一的姓名：");
		cin >> name;
		player1->setName(name);
		display.showMessage("玩家二的姓名：");
		cin >> name;
		player2->setName(name);
	}
	else if (mode == 1) {
		player1 = &human1;
		display.showMessage("玩家一的姓名：");
		cin >> name;
		player1->setName(name);
		player2 = &ai;
		player2->setName("ai");
		system("cls");
		display.showMessage("Hi " + player1->getname() + "我是AI");
		system("pause");
	}
}
Game::Game()
{
	this->mode = 0;
}
void Game::Mode() {
	while(1){
		system("cls");
		display.showMessage("选择对弈模式 (人机对弈输入\"1\"，人人对弈输入\"2\")：");
		cin >> mode; 
		if (mode == 1 || mode == 2) {
			break;
		}
		else {
			display.showMessage("输入有误，请输入数字1 or 2：");
		}
	}
}
void Game::decideOrder() {
	int j=0,flag=0,i=0;
	string name1 = " ", name2 = player2->getname();
	display.showMessage("石头、剪刀、布判断下棋先后顺序:");
	display.showMessage("该程序会不断运行，直到分出先后手为止。赢家为先手，输家为后手");
	int num = 0;
	srand(time(0));  //随机数种子
	while (true) {    //人机模式下：如果三局决定不出胜负，直接让人类玩家先手；
		if (mode == 1) {  //人机
			j = rand() % 3;
		}
		num += 1;
		name1 = player1->getname();
		display.showMessage("玩家：" + name1);
		display.showMessage("请输入数字（0、1、2），其表示含义：0-石头、1-剪刀、2-布");
		cin >> i;
		system("cls");  //在同一电脑下棋，所以需要清空屏幕内容
		if (mode == 2) {  //人人
		
			string message = "玩家：" + name2;
			display.showMessage(message);
			display.showMessage("请输入数字（0、1、2），其表示含义：0-石头、1-剪刀、2-布");
			cin >> j;
			system("cls");  //在同一电脑下棋，所以需要清空屏幕内容
		}
		if (i == 0) {
			if (j == 0) continue; //平局
			if (j == 2) {  // 输
				flag = 0;
				break;
			}
			else flag = 1; // 赢
		}
		if (i == 1) {
			if (j == 1) continue; //平局
			if (j == 0) {  // 输
				flag = 0;
				break;
			}
			else flag = 1; //赢
		}
		if (i == 2) {
			if (j == 2) continue; //平局
			if (j == 1) {  // 输
				flag = 0;
				break;
			}
			else flag = 1; //赢
		}
		if (num >= 2) {   //人机模式下满足该条件，人类直接获胜
			flag = 1; 
			break;
		}
	}
	flag = 1;
	if (flag == 1) 
	{
		string message = "玩家：" + name1 + "先手";
		display.showMessage(message);
		system("pause");
		if (mode == 1) {   //人机
			first_hand = &human1;
			first_hand->setcolor(-1);  //黑棋
			second_hand = &ai;
			second_hand->setcolor(1);   //白棋
		}
		if (mode == 2) {  //人人
			first_hand = &human1;
			first_hand->setcolor(-1);  //黑棋
			second_hand = &human2;
			second_hand->setcolor(1);   //白棋
		}
	}
	else
	{
		string message = "玩家：" + name2 + "先手";
		display.showMessage(message);
		system("pause");
		if (mode == 1) {   //人机
			first_hand = &ai;
			first_hand->setcolor(-1);  //黑棋
			second_hand = &human1;
			second_hand->setcolor(1);   //白棋
		}
		if (mode == 2) {  //人人
			first_hand = &human2;
			first_hand->setcolor(-1);  //黑棋
			second_hand = &human1;
			second_hand->setcolor(1);   //白棋
		}
	}
	
}
void Game::initGame() {
	Mode();
	initPlayer();
	decideOrder();   //决定先后手
}
void Game::startGame() {
	string input_msg = "";
	Chess chess;
	Judge equity;
	bool win = false;
	while (1)
	{
		int flag = 0;  //对局结束标志 0：重新开始  1：有人获胜  2：平局   3：和棋
		initGame();
		board.board_Init();  //清空棋盘；
		system("cls");
		display.showBoard(board);
		string name1 = first_hand->getname(), name2 = second_hand->getname();
		string message = " ";
		while (1) {
			// 先手下棋
			display.showMessage("玩家：" + name1 + "  下棋");
			while (1) {
				if (first_hand->getname() == "ai") { 					
					ai.getMove(board);
				}
				chess = first_hand->play_chess();
				current_hand = first_hand;
				if (equity.isLegal(chess, board)) {	
					board.addChess(chess);
					vector<vector<int> > boardstate = board.getBoardState();
					ai.updateScore(boardstate, chess.getPosition());
					system("cls");
					display.showBoard(board);			
					break;
				}
		}
			// 获胜
			if (board.getRecords().size() >= 9) {
				if (judge.checkWin(board)) {
					cout << current_hand->getname() << "赢得比赛" << endl;
					system("pause");
					break;
				}
			}
			// 后手下棋
			display.showMessage("玩家：" + name2 + "  下棋");
			while (1) {
				if (second_hand->getname() == "ai") {
				ai.getMove(board);
				}		
				chess = second_hand->play_chess();
				current_hand = second_hand;
				if (equity.isLegal(chess, board)) {		
					board.addChess(chess);
					vector<vector<int> > boardstate = board.getBoardState();
					ai.updateScore(boardstate, chess.getPosition());
					system("cls");
					display.showBoard(board);
					break;
				}
			}
		
		
			// 获胜
			if (board.getRecords().size() >= 9) {
				if (judge.checkWin(board)) {
					cout << current_hand->getname() << "赢得比赛" << endl;
					system("pause");
					break;
				}
			}
			// 下满
			if (board.getRecords().size() == COL * ROW) {
				cout << "平局" << endl;
			}
		}
	}
}