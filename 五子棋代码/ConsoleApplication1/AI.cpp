#include "AI.h"
#include "ACMatcher.h"
#include <cmath>
#include <iostream>
#include <set>
#define MAX_SCORE (10000000)
#define MIN_SCORE (-10000000)
#define DEPTH (3)
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
AI::AI() {
    this->setName("ai");
};

//下棋
Chess AI::play_chess() {
	int color = getcolor();
	Position pos;
	if (posible_position.empty()) {
		pos.x = COL / 2;
		pos.y = ROW / 2;
		//Chess chess = Chess(color, pos);
	}
	else {
        pos.x = searchResult.x;
        pos.y = searchResult.y;
	}
	return Chess(color, pos);
}
//遍历可能的位置
void AI::find_posible_position(vector<vector<int> > boardstate) {
    posible_position.clear();  //清空位置容器
	Position pos; //临时存放检测到棋子的位置，用于最后压栈
	int dx[8]{ 1, 1, 0,-1,-1,-1, 0, 1};  //定义八个位置
	int dy[8]{ 0,-1,-1,-1, 0, 1, 1, 1};
	for (int i = 0; i < boardstate.size(); i++) {
		for (int j = 0; j < boardstate[0].size(); j++) {
			if (boardstate[i][j] == 1 || boardstate[i][j] == -1) {  //当前位置存在棋子
				int x = i;
				int y = j;
				for (int k = 0; k < 8; k++) {
					if ((x + dx[k]) < ROW && x + dx[k] >= 0 && (y + dy[k]) < COL && y + dy[k] >= 0) { // 棋子防止越界
						if (boardstate[x + dx[k]][y + dy[k]] == 0) {  //当前位置没有棋子
							boardstate[x + dx[k]][y + dy[k]] = -2;    //使用该位置后，赋垃圾值，防止二次压栈。 
							pos.x = x + dx[k];
							pos.y = y + dy[k];
							posible_position.insert(pos);
						}
					}
				}
			}
		}
	}
}
//根据位置评分，其中board是当前棋盘，pos是位置
int AI::evaluatePoint(vector<vector<int> > boardstate, Position pos) {
    int result;
    int i, j;
    int role = getcolor();
    result = 0;
    ACMatcher ac;
    vector<string> patternStrs;
    for (size_t i = 0; i < patterns.size(); i++) {
        patternStrs.push_back(patterns[i].pattern);
    }
    // 初始化ACS器
    ac.LoadKeywords(patternStrs);
    ac.ConstructGotoFunction();
    ac.ConstructFailureFunction();
    string myself_score_line[4];
    string other_score_line[4];
   
    int maxOffset = min(5, pos.x);
    int stCol = max(0, pos.x - 5);
    int endCol = min(COL, pos.x + 6);

    for (i = stCol; i < (int)endCol ; i++) {       //横的区间：当前棋子往前数5颗、往后数5颗  5+1+5 = 11
        if (i != pos.x) {
            myself_score_line[0].push_back(boardstate[i][pos.y] == role ? '1' : boardstate[i][pos.y] == 0 ? '0' : '2');
            other_score_line[0].push_back(boardstate[i][pos.y] == role ? '2' : boardstate[i][pos.y] == 0 ? '0' : '1');
        }
        else {
            myself_score_line[0].push_back('1');
            other_score_line[0].push_back('1');
        }
    }
    int stRow = max(0, pos.y - 5),stRCOL=0;
    int endRow = min(ROW, pos.y + 6),endCOL=0;

    for (i = stRow; i < (int)endRow; i++) {       //竖的区间：当前棋子往上数5颗、往下数5颗  5+1+5 = 11
        if (i != pos.y) {
            myself_score_line[1].push_back(boardstate[pos.x][i] == role ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
            other_score_line[1].push_back(boardstate[pos.x][i] == role ? '2' : boardstate[pos.x][i] == 0 ? '0' : '1');
        }
        else {
            myself_score_line[1].push_back('1');
            other_score_line[1].push_back('1');
        }
    }
    // 两层min是找到该斜列的起点，同样是 5+1+5;   "\"
    stRow = pos.x - min(min(pos.x, pos.y), 5), stRCOL = pos.y - min(min(pos.x, pos.y), 5);
    endRow = (int)min(COL, pos.x + 6), endCOL = ( int)min(ROW, pos.y + 6);

    for (i = stRow, j = stRCOL; i < endRow && j < endCOL; i++, j++) {
        if (i != pos.x) {
            myself_score_line[2].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
            other_score_line[2].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');
        }
        else {
            myself_score_line[2].push_back('1');
            other_score_line[2].push_back('1');
        }
    }
    //  研究："/"  同样是 5+1+5
    stRow = pos.x + min(min(pos.y, COL - 1 - pos.x), 5), stRCOL = pos.y - min(min(pos.y, COL - 1 - pos.x), 5);
    endRow = (int)max(0, pos.x - 5), endCOL = (int)min(ROW, pos.y + 6);

    for (i = stRow, j = stRCOL; i >= endRow && j < endCOL; i--, j++) {
        if (i != pos.x) {
            myself_score_line[3].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
            other_score_line[3].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');
        }
        else {
            myself_score_line[3].push_back('1');
            other_score_line[3].push_back('1');
        }
    }
  
 /*  for (int i = 0; i < 4; ++i) {
        cout << myself_score_line[i] << endl;
    }
    cout << "  " << endl;
    for (int i = 0; i < 4; ++i) {
        cout << other_score_line[i] << endl;
    }
    cout << "  " << endl;
    */
    /*
    // 测试
    string lines3[4];
    for (int i = 0; i < 4; ++i) {
        lines3[i] = myself_score_line[i];
        for (size_t j = 0; j < myself_score_line[i].size(); ++j) {
            if (myself_score_line[i][j] == '1') {
                lines3[i][j] = '2';
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        cout << lines3[i] << endl;
    }
    */

    for (i = 0; i < 4; i++) {
        vector<int> tmp = ac.Search(myself_score_line[i]);
        for (j = 0; j < tmp.size(); j++) {
            result += patterns[tmp[j]].score;
        }

        tmp = ac.Search(other_score_line[i]);
        for (j = 0; j < tmp.size(); j++) {
            result += patterns[tmp[j]].score;
        }
    }
    return result;
}
// 根据最新下棋位置，对棋盘分数进行更新
void AI::updateScore(vector<vector<int> > boardstate, Position pos) {
    string myself_score_line[4];
    string other_score_line[4];
    ACMatcher ac;
    vector<string> patternStrs;
    for (size_t i = 0; i < patterns.size(); i++) {
        patternStrs.push_back(patterns[i].pattern);
    }
    // 初始化ACS器
    ac.LoadKeywords(patternStrs);
    ac.ConstructGotoFunction();
    ac.ConstructFailureFunction();
    int i, j;
    int role = getcolor();   //得到机器自己的棋子信息（黑、或白）
    //竖
    // boardstate = board.getBoardState();
    int stROW = 0, stCOL = 0;
    int endROW = ROW, endCOL = COL;
    for (i = 0; i < COL; i++) {

        myself_score_line[0].push_back(boardstate[i][pos.y] == role ? '1' : boardstate[i][pos.y] == 0 ? '0' : '2');
        other_score_line[0].push_back(boardstate[i][pos.y] == role ? '2' : boardstate[i][pos.y] == 0 ? '0' : '1');
       
    }
    //横

    for (i = 0; i < ROW; i++) {

        myself_score_line[1].push_back(boardstate[pos.x][i] == role ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
        other_score_line[1].push_back(boardstate[pos.x][i] == role ? '2' : boardstate[pos.x][i] == 0 ? '0' : '1');

    }
    //反斜杠
    for (i = pos.x - min(pos.x, pos.y), j = pos.y - min(pos.x, pos.y); i < COL && j < COL; i++, j++) {

        myself_score_line[2].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
        other_score_line[2].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');
 

    }
    //斜杠
    for (i = pos.x + min(pos.y, COL - 1 - pos.x), j = pos.y - min(pos.y, COL - 1 - pos.x); i >= 0 && j < COL; i--, j++) {

        myself_score_line[3].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
        other_score_line[3].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');

    }
    //敌人的棋盘信息，与其数据相反       char 与 const char无法比较，舍弃该方法
  /* string lines3[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < myself_score_line[i].length(); j++) {
            if (myself_score_line[i][j] == char(1)){
                cout << myself_score_line[i][j] << endl;
                lines3[i][j] = char(2);
            }
        }
    }

    */

    int myself_secore[4];
    int other_secore[4];
    memset(myself_secore, 0, sizeof(myself_secore));  //生成两个全为0的数组，分别存储横、竖、撇、捺的棋盘分数。
    memset(other_secore, 0, sizeof(other_secore));  //myself_secore存放自己   other_secore存放对手
    //计算分数
    for (i = 0; i < 4; i++) {
        vector<int> result = ac.Search(myself_score_line[i]);
        for (j = 0; j < result.size(); j++) {
            myself_secore[i] += patterns[result[j]].score;
        }

        result = ac.Search(other_score_line[i]);
        for (j = 0; j < result.size(); j++) {
            other_secore[i] += patterns[result[j]].score;
        }
    }

    int a = pos.y;
    int b = COL + pos.x;
    int c = 2 * COL + (pos.y - pos.x + 10);
    int d = 2 * COL + 21 + (pos.x + pos.y - 4);
    //减去以前的记录
    for (i = 0; i < 2; i++) {
        allScore[i] -= scores[i][a];
        allScore[i] -= scores[i][b];
    }

    //scores顺序 竖、横、\、/
    scores[0][a] = myself_secore[0];  //下棋后，棋盘状态更新，因此需要更新该棋子所在的四个方向分数
    scores[1][a] = other_secore[0];
    scores[0][b] = myself_secore[1];
    scores[1][b] = other_secore[1];


    //加上新的记录
    for (i = 0; i < 2; i++) {
        allScore[i] += scores[i][a];
        allScore[i] += scores[i][b];
    }

    if (pos.y - pos.x >= -10 && pos.y - pos.x <= 10) {  // 当棋子数目>=5时，再更新数据；  这里用两个界限卡住范围  y-x+10 = 0  y-x-10=0

        for (i = 0; i < 2; i++)
            allScore[i] -= scores[i][c];

        scores[0][c] = myself_secore[2];
        scores[1][c] = other_secore[2];

        for (i = 0; i < 2; i++)
            allScore[i] += scores[i][c];
    }

    if (pos.x + pos.y >= 4 && pos.x + pos.y <= 24) {   // x+y-4 = 0  x+y-24=0

        for (i = 0; i < 2; i++)
            allScore[i] -= scores[i][d];

        scores[0][d] = myself_secore[3];
        scores[1][d] = other_secore[3];

        for (i = 0; i < 2; i++)
            allScore[i] += scores[i][d];
    }
}
//局面评估函数，给一个局面评分
int AI::evaluate(Role role) {

    if (role == COMPUTOR) {
        return allScore[0];
    }
    else if (role == HUMAN) {
        return allScore[1];
    }
    std::cout << "error" << endl;

    return 0;
}

int AI::abSearch(vector<vector<int> > boardstate, int depth, int alpha, int beta, Role currentSearchRole) {
    

    int score1 = evaluate(currentSearchRole);  //AI分数

    int score2 = evaluate(currentSearchRole == COMPUTOR ? HUMAN : COMPUTOR);  //人类分数

    if (score1 >= 50000) {
        return MAX_SCORE - 1000 - (DEPTH - depth);
    }
    if (score2 >= 50000) {
        return MIN_SCORE + 1000 + (DEPTH - depth);
    }


    if (depth == 0) {
        return score1 - score2;
    }

    

    int count = 0;
    set<Position_Score> possiblePositions;

    //对当前可能出现的位置进行粗略评分

    set<Position>::iterator iter;
    find_posible_position(boardstate);  //寻找可以下棋的位置

    for (iter = posible_position.begin(); iter != posible_position.end(); iter++) {
        possiblePositions.insert(Position_Score(iter->x, iter->y, evaluatePoint(boardstate, *iter)));  //按照棋子位置分数的大小进行排序（前10）
    }
    //获取角色的棋子颜色
    int color;
    if (currentSearchRole == COMPUTOR) {
        color = getcolor();
    }
    else{
        color = -getcolor();
    }

    while (!possiblePositions.empty()) {
        Position_Score pos = *possiblePositions.begin();

        possiblePositions.erase(possiblePositions.begin());  //删除最开始的元素
                                 
        //放置棋子
        boardstate[pos.x][pos.y] = color;

        // 更新棋盘分数
        updateScore(boardstate, pos);

        pos.score = 0;
        // 重新检索可能出现的位置
        find_posible_position(boardstate);  //后期有时间需要修改 

        int val = -abSearch(boardstate, depth - 1, -beta, -alpha, currentSearchRole == HUMAN ? COMPUTOR : HUMAN);
        /*if (depth == DEPTH)
            cout << "score(" << pos.x << "," << pos.y << "):" << val << endl;
        */
        
        //取消放置
        boardstate[pos.x][pos.y] = 0;

        //取消放置后，重新检索点位
        find_posible_position(boardstate);  //后期有时间需要修改

        updateScore(boardstate, pos);

        if (val >= beta) {
            return beta;
        }
        if (val > alpha) {
            alpha = val;
            if (depth == DEPTH) {
                searchResult = pos;
            }
        }

        count++;
        if (count >= 9) {
            break;
        }
    }

    return alpha;
 
};

void AI::getMove(ChessBoard board) {
    vector<vector<int> > boardstate = board.getBoardState();
    // 评估当前全局棋盘分数
    int score = abSearch(boardstate, DEPTH, MIN_SCORE, MAX_SCORE, COMPUTOR);
    return ;
}

