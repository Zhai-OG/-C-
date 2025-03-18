#pragma once
#include"ChessBoard.h"
#include"ACMatcher.h"
struct Ban_Pattern {
    string pattern;
    int score;
};
class Judge
{
public:
	bool checkWin(ChessBoard chess_state); //�ж��Ƿ�ȡ��ʤ�������ʤ������true��else false��
	bool isLegal(Chess chess, ChessBoard board);
	vector<Ban_Pattern> ban_patterns = {   //���ֹ���
	// ��������
	{ "01110",-100},
	{ "010110",-100},
	// ���Ľ���
	{ "11101", -500},
	{ "11110" ,-500},
	{ "1011101",-500},
	// ��������
	{"111111",-10000},
	};
};

