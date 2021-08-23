#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;


//用来读取position后面跟着的字符串，who_turn代表某人的回合，board_status代表棋盘状态，moves表示还要走的步数
void read_position(char& who_turn, string& board_status, vector<string>& moves)
{
	string buffer;
	moves.clear();	//清除过往着法

	cin >> buffer;
	cin >> board_status;
	cin >> who_turn;
	who_turn = (who_turn == 'b') ? 'b' : 'r';		//将who_turn转换为'r'或'b'
	cin >> buffer;	//-
	cin >> buffer;	//-
	cin >> buffer;	//双方没有吃子的走棋步数(半回合数)
	cin >> buffer;	//当前的回合数

	if (cin.peek() != '\n') {
		cin >> buffer;	//moves

		while (cin.peek() != '\n') {
			cin >> buffer;
			moves.push_back(buffer);
		}
	}

	if (moves.size() % 2)
		who_turn = (who_turn == 'b') ? 'r' : 'b';
}


