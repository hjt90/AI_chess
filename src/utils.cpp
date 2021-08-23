#include <fstream>
#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
using namespace std;

int char2index(char ch)//用于将字符转为整数索引
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	else
		return ch - 'a';
}

void chess_clear(char(&board)[board_row][board_col], int r, int c)//将棋子清除
{
	board[r][c] = '\0';
}

void chess_add(char(&board)[board_row][board_col], int r, int c, char value)//添加棋子
{
	board[r][c] = value;
}


void board_print(char(&board)[board_row][board_col])//输出棋盘
{
	cout << "  a b c d e f g h i" << endl;
	for (int i = 0; i < board_row; i++)
	{
		cout << i << ' ';
		for (int j = 0; j < board_col; j++)
		{
			if (board[i][j] == '\0')
				cout << "- ";
			else
				cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void board_print(char(&board)[board_row][board_col], ofstream& out)//输出棋盘
{
	out << "\ta\tb\tc\td\te\tf\tg\th\ti" << endl;
	for (int i = 0; i < board_row; i++)
	{
		out << i << '\t';
		for (int j = 0; j < board_col; j++)
		{
			if (board[i][j] == '\0')
				out << "-\t";
			else
				out << board[i][j] << "\t";
		}
		out << endl;
	}
}


//判断棋的类型，返回为'r'表示为红，返回为'b'表示为黑
char chess_type(char chess)
{
	if (chess >= 'a' && chess <= 'z')
		return 'b';
	else if (chess >= 'A' && chess <= 'Z')
		return 'r';
	else
		return '\0';
}



