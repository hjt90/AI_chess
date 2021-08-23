#include <iostream>
#include <cstring>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;

/************************************************
输入参数：
char board[10][9]: char型数组，用于存储棋盘, '\0'表示空
string board_status : 表示棋盘状态的字符串 只是FEN中的一部分
string moves : 表示运动的动作
返回参数：
已经更新过的棋盘 board
*************************************************/
void string2board(char (&board)[board_row][board_col], string &board_status, const vector<string> &moves)
{
    int index = 0;
	for (int r = board_row - 1; r >= 0; r--) //小写字母为黑方，因此是从上到下来更新
	{
		for (int c = 0; c < board_col; c++)
		{
			char chess = board_status[index]; //为了防止越界
			if (chess > '0' && chess <= '9')  //是空格
			{
				while (chess > '0') {
					board[r][c] = '\0';
					chess--;
					c++;
				}
				c--;
				index++;
				continue;
			}
			else if (chess == '/') //'/'不算数，因此要c--
			{
				index++;
				c--;
				continue;
			}
			board[r][c] = chess; //填入棋盘
			index++;
		}
	}
    //根据moves更新棋盘
    //moves 如 h2e2列在前，行在后
    for (int i = 0; i < moves.size(); i++)
    {
        int c_old = char2index(moves[i][0]);
        int r_old = char2index(moves[i][1]);
        int c_new = char2index(moves[i][2]);
        int r_new = char2index(moves[i][3]);
        char chess = board[r_old][c_old];
        chess_clear(board, r_old, c_old);
        chess_add(board, r_new, c_new, chess);
    }
}
