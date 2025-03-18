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
	void set_size(int row,int col);  //�������̴�С
	void addChess(Chess chess);       //�������
	void takebackChess(int num); //����N��
	Chess get_lastchess();       //��ȡ���һ������
	void board_Init(); //��ʼ������
	vector<vector<string> > getBoardSymbol();  //�������̰ڷ���ʽ(��������������̽��)
	vector<vector<int> > getBoardState();
	stack<Chess> getRecords();
	Scale getChessScal();

	
private:
	Scale scal; //���̹��
	vector<vector<int> > board_state;  //�����������������
	const string chess_symbol[5] = { " ","��","��","��","��" }; //�ա����塢���塢�������һ�š��������һ������
	vector<vector<string> > board_symbol; //������ʽ
	Chess last_chess; 
	stack<Chess> records;  //��¼����
};

