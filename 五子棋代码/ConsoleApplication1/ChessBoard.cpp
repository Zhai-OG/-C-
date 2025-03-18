#include"ChessBoard.h"
#include<vector>
#include"Chess.h"
#include<stack>
ChessBoard::ChessBoard() {
	set_size(ROW, COL);
}
ChessBoard::ChessBoard(int row, int col) {
    set_size(row, col); 
}
void ChessBoard::set_size(int row, int col) {
    this->scal.row = row;
    this->scal.col = col;
    board_state.resize(scal.row);
    for (int i = 0; i < scal.row; ++i) {
        board_state[i].resize(scal.col);
    }
}
Chess ChessBoard::get_lastchess() {
   return last_chess = records.top();  
}

void ChessBoard::addChess(Chess chess) {
    records.push(chess);  //记录棋谱
    Position pos = chess.getPosition();
    board_state[pos.x][pos.y] = chess.getColor(); //black -1 ; white 1
}
Scale ChessBoard::getChessScal() {
    return scal;
}
vector<vector<string> > ChessBoard::getBoardSymbol() {
	// 初始化棋盘
	board_symbol.resize(scal.row);
	for (int i = 0; i < scal.row; ++i) {
		board_symbol[i].resize(scal.col);
	}
	for (int i = 0; i < scal.row; i++) {
		for (int j = 0; j < scal.col; j++) {
			if (i == 0) {
				if (j == 0) board_symbol[i][j] = "┏ ";
				else if (j == scal.col - 1) {
					board_symbol[i][j] = "┓ ";
				}
				else {
					board_symbol[i][j] = "┳ ";
				}
			}
			else if (i == scal.row - 1) {
				if (j == 0) board_symbol[i][j] = "┗ ";
				else if (j == scal.col - 1)
				{
					board_symbol[i][j] = "┛ ";
				}
				else {
					board_symbol[i][j] = "┻ ";
				}
			}
			else {
				if (j == 0) board_symbol[i][j] = "┣ ";
				else if (j == scal.col - 1) {
					board_symbol[i][j] = "┫ ";
				}
				else
					board_symbol[i][j] = "╋ ";
			}
		}
	}
	
	// 根据下棋进度改变棋盘状态
	while (!records.empty()) {
		Chess last_chess = get_lastchess();
		Position last_pos = last_chess.getPosition();
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++)
			{
				if (board_state[i][j] == 0) continue;
				if (records.size() < 2 || records.size() == 2) { //只下了两次棋
					if (board_state[i][j] == -1) board_symbol[i][j] = chess_symbol[3];  //黑棋

					if (board_state[i][j] == 1) board_symbol[i][j] = chess_symbol[4];  //白棋
				}
				else {
					if (board_state[i][j] == -1) board_symbol[i][j] = chess_symbol[1];  //黑棋
					if (board_state[i][j] == 1) board_symbol[i][j] = chess_symbol[2];   //白棋
				}
			}
		}
		if (records.size() == 3) {
			if (board_state[last_pos.x][last_pos.y] == -1) board_symbol[last_pos.x][last_pos.y] = chess_symbol[3];  //黑棋
			if (board_state[last_pos.x][last_pos.y] == 1) board_symbol[last_pos.x][last_pos.y] = chess_symbol[4];   //白棋
		}
		if (records.size() >= 4) {
			records.pop();
			Chess last_second_chess = get_lastchess();
			Position last_secondpos = last_second_chess.getPosition();
			records.push(last_chess);
			if (board_state[last_pos.x][last_pos.y] == -1) board_symbol[last_pos.x][last_pos.y] = chess_symbol[3];  //黑棋
			if (board_state[last_pos.x][last_pos.y] == 1) board_symbol[last_pos.x][last_pos.y] = chess_symbol[4];   //白棋
			if (board_state[last_secondpos.x][last_secondpos.y] == -1) board_symbol[last_secondpos.x][last_secondpos.y] = chess_symbol[3];  //黑棋
			if (board_state[last_secondpos.x][last_secondpos.y] == 1) board_symbol[last_secondpos.x][last_secondpos.y] = chess_symbol[4];   //白棋
		}
		break;
	}
	//更新完毕
	return	board_symbol;
}
vector<vector<int> > ChessBoard::getBoardState() {
	return board_state;
}
void ChessBoard::board_Init() {
	while (!records.empty()) records.pop();  //清空所有记录
	last_chess = *new Chess;
	for (int i = 0; i < board_state.size(); i++) {
		for (int j = 0; j < board_state[0].size(); j++) {
			board_state[i][j] = 0;
		}
	}
}
stack<Chess> ChessBoard::getRecords() {
	return records;
}

