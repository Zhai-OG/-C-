#include "Judge.h"
#include "Chess.h"
#include"ChessBoard.h"
#include<iostream>
#include"ACMatcher.h"
#include<cmath>
using namespace std;

bool Judge::checkWin(ChessBoard chess_state) {
    Chess last_chess = chess_state.get_lastchess();
    Position loc = last_chess.getPosition();  //位置
    int color = last_chess.getColor();  //颜色
    int dx[4]{ 1,0,1,1 };  //定义四个方向
    int dy[4]{ 0,1,1,-1};   
    vector<vector<int> > state = chess_state.getBoardState();  //棋盘矩阵，存放对局信息
    int col = chess_state.getChessScal().col, row = chess_state.getChessScal().row;
    for(int i=0;i<4;i++){
        int count = 1;
        int x = loc.x, y = loc.y;
        while ((x + dx[i]) < col && (y + dy[i]) < row && (y + dy[i]) >=0 ) {  //向正方向检索：1）遇到边界，跳出循环  2）遇到不同颜色棋子跳出循环
            x += dx[i];
            y += dy[i];
            if (state[x][y] == color) count++;
            else
                break;        
        }
        x = loc.x;
        y = loc.y;
        while ((x - dx[i]) >= 0 && (y - dy[i]) < row && (y - dy[i]) >= 0) {  //向反方向检索：1）遇到边界，跳出循环
            x -= dx[i];
            y -= dy[i];
            if (state[x][y] == color) count++;
            else
                break;
        }
        if (count >= 5) {  //连成五子
            return true;
        }
    }
    return false;
}
bool Judge::isLegal(Chess chess, ChessBoard board) {

    int row = board.getChessScal().row, col = board.getChessScal().col;
    int x = chess.getPosition().x, y = chess.getPosition().y;
    if (x<0 || x>col || y<0 || y>row  ) { //越界
        cout << "落子越界" << endl;
        return false;
    }
    if (board.getBoardState()[x][y] != 0) {  //所下位置已经存在棋子
        cout << "所下位置存在棋子" << endl;
        return false;
    }
    //如果棋子为黑色则，进行禁手判断
    if (chess.getColor() == -1) { 
        ACMatcher ac;
        vector<string> patternStrs;
        for (size_t i = 0; i < ban_patterns.size(); i++) {
            patternStrs.push_back(ban_patterns[i].pattern);
        }
        // 初始化ACS器
        ac.LoadKeywords(patternStrs);
        ac.ConstructGotoFunction();
        ac.ConstructFailureFunction();
        vector<vector<int> > boardstate = board.getBoardState();
        string lines[4];
        Position pos = chess.getPosition(); //得到当前下棋棋子的位置
        int i,j;
        int stROW = 0, stCOL = 0;
        int endROW = 0, endCOL = 0;

        for (i = max(0, pos.x - 6); i < (int)min(COL, pos.x + 7); i++) {       //横的区间：当前棋子往前数6颗、往后数6颗  
            if (i != pos.x) {
               lines[0].push_back(boardstate[pos.x][i] == -1 ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
            }
            else {
                lines[0].push_back('1');
            }
        }
        for (i = max(0, pos.y - 6); i < (int)min(ROW, pos.y + 7); i++) {       //竖的区间：当前棋子往上数5颗、往下数5颗  
            if (i != pos.y) {
                lines[1].push_back(boardstate[pos.x][i] == -1 ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
            }
            else {
                lines[1].push_back('1');

            }
        }
        // 两层min是找到该斜列的起点，同样是 5+1+5;   "\"
        stROW = pos.x - min(min(pos.x, pos.y), 6),stCOL = pos.y - min(min(pos.x, pos.y), 6);
        endROW = min(COL, pos.x + 7), endCOL = min(ROW, pos.y + 7);
       
        for (i = stROW, j = stCOL ; i < (int)endROW && j < (int)endCOL; i++, j++) {
            if (i != pos.x) {
                lines[2].push_back(boardstate[i][j] == -1  ? '1' : boardstate[i][j] == 0 ? '0' : '2');
            }
            else {
                lines[2].push_back('1');
            }
        }
        stROW = pos.x + min(min(pos.y, COL - 1 - pos.x), 6), stCOL = pos.y - min(min(pos.y, COL - 1 - pos.x), 6);
        endROW = max(0, pos.x - 6), endCOL = min(ROW, pos.y + 7);
        //  研究："/"
        for (i = stROW, j = stCOL; i >= (int)endROW && j < (int)endCOL; i--, j++) {
            if (i != pos.x) {
                lines[3].push_back(boardstate[i][j] == -1 ? '1' : boardstate[i][j] == 0 ? '0' : '2');
            }
            else {
                lines[3].push_back('1');
            }
        }
        int result=0; 
        for (i = 0; i < 4; i++) {
            vector<int> tmp = ac.Search(lines[i]);
            for (j = 0; j < tmp.size(); j++) {
                result += ban_patterns[tmp[j]].score;
            }
        }
        if(result<0){
            if (result <= -200 && result >= -400) {
                cout << "三三禁手" << endl;
                return false;
            }
            if (result <= -1000 && result >= -2000) {
                cout << "四四禁手" << endl;
                return false;
            }
            if (result <= -10000) {
                cout << "长连禁手" << endl;
                return false;
            }
        }
    }
    return true;
}