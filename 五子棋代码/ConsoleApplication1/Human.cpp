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
	pos.y = -1;  // ��ʼ������Ϊ�Ƿ�λ��
	string position = " ";
	while (position.size() != 2) {
		cin >> position;
		if (position.size() == 2) {     //�����Ƿ�Ϸ�
			pos.x = position[0] - 'a';
			pos.y = position[1] - 'a';
			chess = Chess(color, pos);
			return chess;
		}
		else {
			cout << "����������" << endl;
		}
	}
	chess = Chess(color, pos);
	return chess;
}
