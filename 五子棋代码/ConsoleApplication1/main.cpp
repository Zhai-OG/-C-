#include <iostream>
#include"ChessBoard.h"
#include<vector>
#include"Chess.h"
#include<stack>
#include"Game.h"
#include <string>
#include <set>
#include "ACMatcher.h"
using namespace std;

int main()
{
    vector<Pattern> patterns = {
    { "11111",  50000 },
    { "011110", 4320 },
    { "011100", 720 },
    { "001110", 720 },
    { "011010", 720 },
    { "010110", 720 },
    { "11110",  720 },
    { "01111",  720 },
    { "11011",  720 },
    { "10111",  720 },
    { "11101",  720 },
    { "001100", 120 },
    { "001010", 120 },
    { "010100", 120 },
    { "000100", 20 },
    { "001000", 20 },
    };        //分数评价表
    Game game;
    game.startGame();
}
