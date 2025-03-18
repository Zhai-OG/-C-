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
	bool checkWin(ChessBoard chess_state); //判断是否取得胜利：获得胜利返回true；else false；
	bool isLegal(Chess chess, ChessBoard board);
	vector<Ban_Pattern> ban_patterns = {   //禁手规则
	// 三三禁手
	{ "01110",-100},
	{ "010110",-100},
	// 四四禁手
	{ "11101", -500},
	{ "11110" ,-500},
	{ "1011101",-500},
	// 长连禁手
	{"111111",-10000},
	};
};

