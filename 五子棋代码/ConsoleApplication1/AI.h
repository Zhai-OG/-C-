#pragma once
#include"Player.h"
#include"Chess.h"
#include"ChessBoard.h"
#include<stack>
#include<set>
struct Pattern {
    string pattern;
    int score;
};
// 将位置引入分数这一 差异，用在AI 中
enum Role { HUMAN = 1, COMPUTOR = 2, EMPTY = 0 };  // 用于AB剪枝算法，标识状态
struct Position_Score:public Position {
    int score;
    Position_Score() {}
    Position_Score(int x, int y) {
        this->x = x;
        this->y = y;
        score = 0;
    }
    Position_Score(int x, int y, int score) {
        this->x = x;
        this->y = y;
        this->score = score;
    }
    bool operator <(const Position_Score& pos) const {
        if (score != pos.score) {
            return score > pos.score;
        }
        if (x != pos.x) {
            return x < pos.x;
        }
        else {
            return y < pos.y;
        }
    }
};

class AI:public Player{
public:
	AI();
	Chess play_chess();
    int evaluate(Role role);
	void find_posible_position(vector<vector<int> > boardstate);
    int evaluatePoint(vector<vector<int> > boardstate, Position pos); //对可能下棋位置进行评分
//	void updateScore(ChessBoard board, Position pos);
    void updateScore(vector<vector<int> > boardstate, Position pos);
    int abSearch(vector<vector<int> > boardstate, int depth, int alpha, int beta, Role currentSearchRole); //ab剪枝算法
    void getMove(ChessBoard board); // 得到下一步下棋的位置
   // void init_firstboardscore(vector<vector<int> > boardstate);
private:
	set<Position> posible_position;  //存放下一步可能下棋的点的时候只需要考虑现有棋子旁边的点
	                                   //即与现有棋子相差一格且没有棋子的点（八个方向）
    int scores[2][ROW+COL+((COL-5)*2+1)*2];   //保存棋局分数（2个角色:标准棋局（72行），包括横竖撇捺）
    int allScore[2];    //局面总评分（2个角色） allScore[0] 电脑  allScore[1] 敌人
    Position searchResult;  // 下一步下棋的位置
    
};

