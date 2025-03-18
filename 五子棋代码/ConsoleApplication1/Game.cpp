#include "Game.h"
#include"AI.h"
#define MAX_SCORE (10000000)
#define MIN_SCORE (-10000000)
#define DEPTH (3)  // �����㷨����
void Game::initPlayer() {
	string name;
	if (mode == 2) {
		player1 = &human1;
		player2 = &human2;
		display.showMessage("���һ��������");
		cin >> name;
		player1->setName(name);
		display.showMessage("��Ҷ���������");
		cin >> name;
		player2->setName(name);
	}
	else if (mode == 1) {
		player1 = &human1;
		display.showMessage("���һ��������");
		cin >> name;
		player1->setName(name);
		player2 = &ai;
		player2->setName("ai");
		system("cls");
		display.showMessage("Hi " + player1->getname() + "����AI");
		system("pause");
	}
}
Game::Game()
{
	this->mode = 0;
}
void Game::Mode() {
	while(1){
		system("cls");
		display.showMessage("ѡ�����ģʽ (�˻���������\"1\"�����˶�������\"2\")��");
		cin >> mode; 
		if (mode == 1 || mode == 2) {
			break;
		}
		else {
			display.showMessage("������������������1 or 2��");
		}
	}
}
void Game::decideOrder() {
	int j=0,flag=0,i=0;
	string name1 = " ", name2 = player2->getname();
	display.showMessage("ʯͷ�����������ж������Ⱥ�˳��:");
	display.showMessage("�ó���᲻�����У�ֱ���ֳ��Ⱥ���Ϊֹ��Ӯ��Ϊ���֣����Ϊ����");
	int num = 0;
	srand(time(0));  //���������
	while (true) {    //�˻�ģʽ�£�������־�������ʤ����ֱ��������������֣�
		if (mode == 1) {  //�˻�
			j = rand() % 3;
		}
		num += 1;
		name1 = player1->getname();
		display.showMessage("��ң�" + name1);
		display.showMessage("���������֣�0��1��2�������ʾ���壺0-ʯͷ��1-������2-��");
		cin >> i;
		system("cls");  //��ͬһ�������壬������Ҫ�����Ļ����
		if (mode == 2) {  //����
		
			string message = "��ң�" + name2;
			display.showMessage(message);
			display.showMessage("���������֣�0��1��2�������ʾ���壺0-ʯͷ��1-������2-��");
			cin >> j;
			system("cls");  //��ͬһ�������壬������Ҫ�����Ļ����
		}
		if (i == 0) {
			if (j == 0) continue; //ƽ��
			if (j == 2) {  // ��
				flag = 0;
				break;
			}
			else flag = 1; // Ӯ
		}
		if (i == 1) {
			if (j == 1) continue; //ƽ��
			if (j == 0) {  // ��
				flag = 0;
				break;
			}
			else flag = 1; //Ӯ
		}
		if (i == 2) {
			if (j == 2) continue; //ƽ��
			if (j == 1) {  // ��
				flag = 0;
				break;
			}
			else flag = 1; //Ӯ
		}
		if (num >= 2) {   //�˻�ģʽ�����������������ֱ�ӻ�ʤ
			flag = 1; 
			break;
		}
	}
	flag = 1;
	if (flag == 1) 
	{
		string message = "��ң�" + name1 + "����";
		display.showMessage(message);
		system("pause");
		if (mode == 1) {   //�˻�
			first_hand = &human1;
			first_hand->setcolor(-1);  //����
			second_hand = &ai;
			second_hand->setcolor(1);   //����
		}
		if (mode == 2) {  //����
			first_hand = &human1;
			first_hand->setcolor(-1);  //����
			second_hand = &human2;
			second_hand->setcolor(1);   //����
		}
	}
	else
	{
		string message = "��ң�" + name2 + "����";
		display.showMessage(message);
		system("pause");
		if (mode == 1) {   //�˻�
			first_hand = &ai;
			first_hand->setcolor(-1);  //����
			second_hand = &human1;
			second_hand->setcolor(1);   //����
		}
		if (mode == 2) {  //����
			first_hand = &human2;
			first_hand->setcolor(-1);  //����
			second_hand = &human1;
			second_hand->setcolor(1);   //����
		}
	}
	
}
void Game::initGame() {
	Mode();
	initPlayer();
	decideOrder();   //�����Ⱥ���
}
void Game::startGame() {
	string input_msg = "";
	Chess chess;
	Judge equity;
	bool win = false;
	while (1)
	{
		int flag = 0;  //�Ծֽ�����־ 0�����¿�ʼ  1�����˻�ʤ  2��ƽ��   3������
		initGame();
		board.board_Init();  //������̣�
		system("cls");
		display.showBoard(board);
		string name1 = first_hand->getname(), name2 = second_hand->getname();
		string message = " ";
		while (1) {
			// ��������
			display.showMessage("��ң�" + name1 + "  ����");
			while (1) {
				if (first_hand->getname() == "ai") { 					
					ai.getMove(board);
				}
				chess = first_hand->play_chess();
				current_hand = first_hand;
				if (equity.isLegal(chess, board)) {	
					board.addChess(chess);
					vector<vector<int> > boardstate = board.getBoardState();
					ai.updateScore(boardstate, chess.getPosition());
					system("cls");
					display.showBoard(board);			
					break;
				}
		}
			// ��ʤ
			if (board.getRecords().size() >= 9) {
				if (judge.checkWin(board)) {
					cout << current_hand->getname() << "Ӯ�ñ���" << endl;
					system("pause");
					break;
				}
			}
			// ��������
			display.showMessage("��ң�" + name2 + "  ����");
			while (1) {
				if (second_hand->getname() == "ai") {
				ai.getMove(board);
				}		
				chess = second_hand->play_chess();
				current_hand = second_hand;
				if (equity.isLegal(chess, board)) {		
					board.addChess(chess);
					vector<vector<int> > boardstate = board.getBoardState();
					ai.updateScore(boardstate, chess.getPosition());
					system("cls");
					display.showBoard(board);
					break;
				}
			}
		
		
			// ��ʤ
			if (board.getRecords().size() >= 9) {
				if (judge.checkWin(board)) {
					cout << current_hand->getname() << "Ӯ�ñ���" << endl;
					system("pause");
					break;
				}
			}
			// ����
			if (board.getRecords().size() == COL * ROW) {
				cout << "ƽ��" << endl;
			}
		}
	}
}