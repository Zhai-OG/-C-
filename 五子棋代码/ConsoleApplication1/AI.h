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
// ��λ�����������һ ���죬����AI ��
enum Role { HUMAN = 1, COMPUTOR = 2, EMPTY = 0 };  // ����AB��֦�㷨����ʶ״̬
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
    int evaluatePoint(vector<vector<int> > boardstate, Position pos); //�Կ�������λ�ý�������
//	void updateScore(ChessBoard board, Position pos);
    void updateScore(vector<vector<int> > boardstate, Position pos);
    int abSearch(vector<vector<int> > boardstate, int depth, int alpha, int beta, Role currentSearchRole); //ab��֦�㷨
    void getMove(ChessBoard board); // �õ���һ�������λ��
   // void init_firstboardscore(vector<vector<int> > boardstate);
private:
	set<Position> posible_position;  //�����һ����������ĵ��ʱ��ֻ��Ҫ�������������Աߵĵ�
	                                   //���������������һ����û�����ӵĵ㣨�˸�����
    int scores[2][ROW+COL+((COL-5)*2+1)*2];   //������ַ�����2����ɫ:��׼��֣�72�У�����������Ʋ�ࣩ
    int allScore[2];    //���������֣�2����ɫ�� allScore[0] ����  allScore[1] ����
    Position searchResult;  // ��һ�������λ��
    
};

