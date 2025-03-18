#include "Display.h"
#include "ChessBoard.h"
#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

Display::Display()
{
}
Display::~Display()
{
}

void Display::showBoard(ChessBoard board) {
	Scale size = board.getChessScal();
	vector<vector<string> > msg = board.getBoardSymbol();
	cout << "  " ;
	for (int i = 0; i < size.row; i++) {
		cout << char('a' + i);//横轴标识
		cout << " ";
	}
	cout << endl;
	for (int i = 0; i < size.row; i++) {
		cout << char('a' + i);//纵轴标识
		for (int j = 0; j < size.col; j++) {
			cout << msg[i][j];
		}
		cout << endl;
	}
}
void Display::showMessage(string msg) {
	cout << msg << endl;
}