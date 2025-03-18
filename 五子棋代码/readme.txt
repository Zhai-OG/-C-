
依赖标准库
string、vector、map、stack、set

代码平台：vs2019

1、运行程序
1）直接运行main文件
2）与电脑进行剪刀、石头、布决定先后手
0、1、2分别代表剪刀、石头、布；输入数字后，按回车即可。
3）下棋
先输入纵坐标，后行坐标，用小写字母表示，按下回车即可读入坐标。例如：bc  代表第二行，第三列坐标位置。


2、程序结构
0）Position结构体
x、y用于表示坐标

1）Chess类（棋子类）
私有成员：
位置（x，y）、颜色
公有成员：
Chess（）：构造函数
getColor（）：返回棋子颜色
getPosition（）： 返回棋子位置

2）ChessBoard类（棋盘类）
私有成员：
scal（棋盘规格）：ROW、COL（行列）
board_state（棋子记录）：存放棋盘棋子的摆放位置
chess_symbol：定义棋子的样式（"●","○","▲","△" ）
board_symbol：字符型棋盘状态，由board_state转化而来
last_chess：最后一颗棋子的位置
records：记录棋谱，用于悔棋等操作
公有成员：
ChessBoard(int row,int col)：构造函数
set_size(int row,int col)：设置棋盘规格
addChess(Chess chess)：添加棋子
takebackChess(int num)： 悔棋N个
Chess get_lastchess()：获取最后一个棋子位置
board_Init()：初始化棋盘
getBoardSymbol(): 给出棋谱摆放形式(可以用作输出棋盘结果)
getBoardState（）：获得详细棋谱
getRecords()：获得下棋记录
getChessScal()：获得棋盘规格

3）Display类（显示类）
公有成员：
showBoard(ChessBoard board)：在命令行输出棋盘
showMessage(string msg)：输出字符串信息

4）Player类（玩家类）
私有成员：
name：名字
color：下棋颜色
公有成员：
Player(string name, int color)：构造函数
getcolor()：得到下棋颜色
setcolor(int color)：设置棋子颜色
getname()：得到玩家姓名
setName(string name)：设置玩家姓名
Chess play_chess()：下棋

4-1）Human类（人类） 继承Player类获得
公有成员：
play_chess（）：下棋，为虚函数

4-2）AI类（机器人） 继承Player类获得
私有成员：
posible_position：存放下一步可能的下棋位置，只需要考虑现有棋子旁边的点，
	            即与现有棋子相差一格且没有棋子的点（八个方向）。
scores：保存棋局分数（2个角色:标准棋局（72行），包括横竖撇捺）
allScore：局面总评分（2个角色） allScore[0] 电脑  allScore[1] 敌人
searchResult：下一步下棋位置
公有成员：
play_chess（）：下棋，为虚函数
evaluate(Role role)：获得role角色的分数
find_posible_position(vector<vector<int> > boardstate)：找到可能的下棋位置
evaluatePoint(vector<vector<int> > boardstate, Position p)：对可能下棋位置进行评分
 updateScore(vector<vector<int> > boardstate, Position p)：更新棋盘分数
Rollback(Position)：删除增加的点位
abSearch(vector<vector<int> > boardstate, int depth, int alpha, int beta, Role currentSearchRole)：ab剪枝算法
getMove(ChessBoard board)：得到下一步下棋的位置

5）Judge类（裁判类）
checkWin(ChessBoard chess_state)：判断是否获胜
isLegal(Chess chess, ChessBoard board)：判断下棋是否合法，包含对黑棋的禁手判断；
ban_patterns：用于禁手棋型判断


6）Game类（游戏类）
私有成员：
ai：机器人
Player：玩家
judge：裁判
board：棋盘
display：显示成员
mode：对弈模式
公有成员：
Mode（）：对弈模式初始化
initPlayer()：初始化参赛对象
decideOrder()：决定先后手  随机
initGame()：初始化游戏：模式、对象、先后手
startGame()：开始游戏

7）ACMatcher类
该类为辅助类，用于AC搜索算法，与评价棋盘分数配合使用。
