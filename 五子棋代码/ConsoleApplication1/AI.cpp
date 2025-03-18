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
};        //�������۱�
AI::AI() {
    this->setName("ai");
};

//����
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
//�������ܵ�λ��
void AI::find_posible_position(vector<vector<int> > boardstate) {
    posible_position.clear();  //���λ������
	Position pos; //��ʱ��ż�⵽���ӵ�λ�ã��������ѹջ
	int dx[8]{ 1, 1, 0,-1,-1,-1, 0, 1};  //����˸�λ��
	int dy[8]{ 0,-1,-1,-1, 0, 1, 1, 1};
	for (int i = 0; i < boardstate.size(); i++) {
		for (int j = 0; j < boardstate[0].size(); j++) {
			if (boardstate[i][j] == 1 || boardstate[i][j] == -1) {  //��ǰλ�ô�������
				int x = i;
				int y = j;
				for (int k = 0; k < 8; k++) {
					if ((x + dx[k]) < ROW && x + dx[k] >= 0 && (y + dy[k]) < COL && y + dy[k] >= 0) { // ���ӷ�ֹԽ��
						if (boardstate[x + dx[k]][y + dy[k]] == 0) {  //��ǰλ��û������
							boardstate[x + dx[k]][y + dy[k]] = -2;    //ʹ�ø�λ�ú󣬸�����ֵ����ֹ����ѹջ�� 
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
//����λ�����֣�����board�ǵ�ǰ���̣�pos��λ��
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
    // ��ʼ��ACS��
    ac.LoadKeywords(patternStrs);
    ac.ConstructGotoFunction();
    ac.ConstructFailureFunction();
    string myself_score_line[4];
    string other_score_line[4];
   
    int maxOffset = min(5, pos.x);
    int stCol = max(0, pos.x - 5);
    int endCol = min(COL, pos.x + 6);

    for (i = stCol; i < (int)endCol ; i++) {       //������䣺��ǰ������ǰ��5�š�������5��  5+1+5 = 11
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

    for (i = stRow; i < (int)endRow; i++) {       //�������䣺��ǰ����������5�š�������5��  5+1+5 = 11
        if (i != pos.y) {
            myself_score_line[1].push_back(boardstate[pos.x][i] == role ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
            other_score_line[1].push_back(boardstate[pos.x][i] == role ? '2' : boardstate[pos.x][i] == 0 ? '0' : '1');
        }
        else {
            myself_score_line[1].push_back('1');
            other_score_line[1].push_back('1');
        }
    }
    // ����min���ҵ���б�е���㣬ͬ���� 5+1+5;   "\"
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
    //  �о���"/"  ͬ���� 5+1+5
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
    // ����
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
// ������������λ�ã������̷������и���
void AI::updateScore(vector<vector<int> > boardstate, Position pos) {
    string myself_score_line[4];
    string other_score_line[4];
    ACMatcher ac;
    vector<string> patternStrs;
    for (size_t i = 0; i < patterns.size(); i++) {
        patternStrs.push_back(patterns[i].pattern);
    }
    // ��ʼ��ACS��
    ac.LoadKeywords(patternStrs);
    ac.ConstructGotoFunction();
    ac.ConstructFailureFunction();
    int i, j;
    int role = getcolor();   //�õ������Լ���������Ϣ���ڡ���ף�
    //��
    // boardstate = board.getBoardState();
    int stROW = 0, stCOL = 0;
    int endROW = ROW, endCOL = COL;
    for (i = 0; i < COL; i++) {

        myself_score_line[0].push_back(boardstate[i][pos.y] == role ? '1' : boardstate[i][pos.y] == 0 ? '0' : '2');
        other_score_line[0].push_back(boardstate[i][pos.y] == role ? '2' : boardstate[i][pos.y] == 0 ? '0' : '1');
       
    }
    //��

    for (i = 0; i < ROW; i++) {

        myself_score_line[1].push_back(boardstate[pos.x][i] == role ? '1' : boardstate[pos.x][i] == 0 ? '0' : '2');
        other_score_line[1].push_back(boardstate[pos.x][i] == role ? '2' : boardstate[pos.x][i] == 0 ? '0' : '1');

    }
    //��б��
    for (i = pos.x - min(pos.x, pos.y), j = pos.y - min(pos.x, pos.y); i < COL && j < COL; i++, j++) {

        myself_score_line[2].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
        other_score_line[2].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');
 

    }
    //б��
    for (i = pos.x + min(pos.y, COL - 1 - pos.x), j = pos.y - min(pos.y, COL - 1 - pos.x); i >= 0 && j < COL; i--, j++) {

        myself_score_line[3].push_back(boardstate[i][j] == role ? '1' : boardstate[i][j] == 0 ? '0' : '2');
        other_score_line[3].push_back(boardstate[i][j] == role ? '2' : boardstate[i][j] == 0 ? '0' : '1');

    }
    //���˵�������Ϣ�����������෴       char �� const char�޷��Ƚϣ������÷���
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
    memset(myself_secore, 0, sizeof(myself_secore));  //��������ȫΪ0�����飬�ֱ�洢�ᡢ����Ʋ��������̷�����
    memset(other_secore, 0, sizeof(other_secore));  //myself_secore����Լ�   other_secore��Ŷ���
    //�������
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
    //��ȥ��ǰ�ļ�¼
    for (i = 0; i < 2; i++) {
        allScore[i] -= scores[i][a];
        allScore[i] -= scores[i][b];
    }

    //scores˳�� �����ᡢ\��/
    scores[0][a] = myself_secore[0];  //���������״̬���£������Ҫ���¸��������ڵ��ĸ��������
    scores[1][a] = other_secore[0];
    scores[0][b] = myself_secore[1];
    scores[1][b] = other_secore[1];


    //�����µļ�¼
    for (i = 0; i < 2; i++) {
        allScore[i] += scores[i][a];
        allScore[i] += scores[i][b];
    }

    if (pos.y - pos.x >= -10 && pos.y - pos.x <= 10) {  // ��������Ŀ>=5ʱ���ٸ������ݣ�  �������������޿�ס��Χ  y-x+10 = 0  y-x-10=0

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
//����������������һ����������
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
    

    int score1 = evaluate(currentSearchRole);  //AI����

    int score2 = evaluate(currentSearchRole == COMPUTOR ? HUMAN : COMPUTOR);  //�������

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

    //�Ե�ǰ���ܳ��ֵ�λ�ý��д�������

    set<Position>::iterator iter;
    find_posible_position(boardstate);  //Ѱ�ҿ��������λ��

    for (iter = posible_position.begin(); iter != posible_position.end(); iter++) {
        possiblePositions.insert(Position_Score(iter->x, iter->y, evaluatePoint(boardstate, *iter)));  //��������λ�÷����Ĵ�С��������ǰ10��
    }
    //��ȡ��ɫ��������ɫ
    int color;
    if (currentSearchRole == COMPUTOR) {
        color = getcolor();
    }
    else{
        color = -getcolor();
    }

    while (!possiblePositions.empty()) {
        Position_Score pos = *possiblePositions.begin();

        possiblePositions.erase(possiblePositions.begin());  //ɾ���ʼ��Ԫ��
                                 
        //��������
        boardstate[pos.x][pos.y] = color;

        // �������̷���
        updateScore(boardstate, pos);

        pos.score = 0;
        // ���¼������ܳ��ֵ�λ��
        find_posible_position(boardstate);  //������ʱ����Ҫ�޸� 

        int val = -abSearch(boardstate, depth - 1, -beta, -alpha, currentSearchRole == HUMAN ? COMPUTOR : HUMAN);
        /*if (depth == DEPTH)
            cout << "score(" << pos.x << "," << pos.y << "):" << val << endl;
        */
        
        //ȡ������
        boardstate[pos.x][pos.y] = 0;

        //ȡ�����ú����¼�����λ
        find_posible_position(boardstate);  //������ʱ����Ҫ�޸�

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
    // ������ǰȫ�����̷���
    int score = abSearch(boardstate, DEPTH, MIN_SCORE, MAX_SCORE, COMPUTOR);
    return ;
}

