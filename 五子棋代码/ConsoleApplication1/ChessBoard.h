#pragma once
#include<vector>
#include<string>
#include"Chess.h"
#include<stack>
#define ROW 15
#define COL 15
using namespace std;
struct Scale {
	int row;
	int col;
};
class ChessBoard
{
public:
	ChessBoard();
	ChessBoard(int row,int col);
	void set_size(int row,int col);  //设置棋盘大小
	void addChess(Chess chess);       //添加棋子
	void takebackChess(int num); //悔棋N个
	Chess get_lastchess();       //获取最后一个棋子
	void board_Init(); //初始化棋盘
	vector<vector<string> > getBoardSymbol();  //给出棋盘摆放形式(可以用作输出棋盘结果)
	vector<vector<int> > getBoardState();
	stack<Chess> getRecords();
	Scale getChessScal();

	
private:
	Scale scal; //棋盘规格
	vector<vector<int> > board_state;  //存放棋盘上所有棋子
	const string chess_symbol[5] = { " ","●","○","▲","△" }; //空、白棋、黑棋、白棋最后一颗、黑棋最后一颗棋子
	vector<vector<string> > board_symbol; //棋盘样式
	Chess last_chess; 
	stack<Chess> records;  //记录棋谱
};

