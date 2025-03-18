#include <iostream>
#include "ChessBoard.h"
#include "Human.h"
#include"Chess.h"
Human::Human() {

};
Chess Human::play_chess() {
	int color = getcolor();
	Chess chess;
 	Position pos;
	pos.x = -1;
	pos.y = -1;  // 初始化棋子为非法位置
	string position = " ";
	while (position.size() != 2) {
		cin >> position;
		if (position.size() == 2) {     //落子是否合法
			pos.x = position[0] - 'a';
			pos.y = position[1] - 'a';
			chess = Chess(color, pos);
			return chess;
		}
		else {
			cout << "请重新落子" << endl;
		}
	}
	chess = Chess(color, pos);
	return chess;
}
