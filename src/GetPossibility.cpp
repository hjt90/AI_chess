#include<iostream>
#include<vector>
#include<map>
#include"../include/GetPossibility.h"
using namespace std;

/*fen规则
r车 n马 b相 a士 k帅 c炮 p兵
*/

char whichside(char c)
{
	if (c == '\0')
		return 'z';
	if (c >= 'a')
		return 'b';
	else
		return 'r';
}

vector<string> getnodes(char(&board)[board_row][board_col], char side)//一个参数是棋盘，第二个参数是谁走（按照fen规则b是黑r是红）
{
	vector<string> result;
	int i, j, k, q;//一些随便的计数器
	string temp="0000";//先放一个缓存
	//先放一个字典来存储当前棋子的符号
	map<char, char> m;
	//存放一些界限
	//九宫格
	int row91, row92, col91, col92;
	if (side == 'b')
	{
		row91 = 7;
		row92 = 9;
		col91 = 3;
		col92 = 5;
	}
	else
	{
		row91 = 0;
		row92 = 2;
		col91 = 3;
		col92 = 5;
	}
	//半场
	int halfrow1, halfrow2;
	if (side == 'b')
	{
		halfrow1 = 5;
		halfrow2 = 9;
	}
	else
	{
		halfrow1 = 0;
		halfrow2 = 4;
	}

	if (side == 'b')
	{
		m['r'] = 'r';
		m['n'] = 'n';
		m['b'] = 'b';
		m['a'] = 'a';
		m['k'] = 'k';
		m['c'] = 'c';
		m['p'] = 'p';
	}
	else
	{
		m['r'] = 'R';
		m['n'] = 'N';
		m['b'] = 'B';
		m['a'] = 'A';
		m['k'] = 'K';
		m['c'] = 'C';
		m['p'] = 'P';
	}
	//遍历棋盘
	for (i = 0; i < board_row; i++)
	{
		for (j = 0; j < board_col; j++)
		{
			//对每一个棋盘位置进行分析
			if (whichside(board[i][j]) != side)//空的或者是红色的
				;
			else if (board[i][j] == m['r'])//是车
			{
				for (k = i + 1; k < board_row && whichside(board[k][j]) != side; k++)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = i - 1; k >= 0 && whichside(board[k][j]) != side; k--)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['n'])//是马
			{
				//先判断上下左右是否别马脚，然后在走
				if (i + 1 < board_row && board[i + 1][j] == '\0')
				{
					if (i + 2 < board_row && j - 1 >= 0 && whichside(board[i + 2][j - 1]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 2 + '0';
						temp[3] = j - 1 + '0';
						result.push_back(temp);
					}
					if (i + 2 < board_row && j + 1 < board_col && whichside(board[i + 2][j + 1]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 2 + '0';
						temp[3] = j + 1 + '0';
						result.push_back(temp);
					}
				}
				if (i - 1 >= 0 && board[i - 1][j] == '\0')
				{
					if (i - 2 >= 0 && j - 1 >= 0 && whichside(board[i - 2][j - 1]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 2 + '0';
						temp[3] = j - 1 + '0';
						result.push_back(temp);
					}
					if (i - 2 >= 0 && j + 1 < board_col && whichside(board[i - 2][j + 1]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 2 + '0';
						temp[3] = j + 1 + '0';
						result.push_back(temp);
					}
				}
				if (j + 1 < board_row && board[i][j + 1] == '\0')
				{
					if (i - 1 >= 0 && j + 2 < board_col && whichside(board[i - 1][j + 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 1 + '0';
						temp[3] = j + 2 + '0';
						result.push_back(temp);
					}
					if (i + 1 < board_row && j + 2 < board_col && whichside(board[i + 1][j + 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 1 + '0';
						temp[3] = j + 2 + '0';
						result.push_back(temp);
					}
				}
				if (j - 1 >= 0 && board[i][j + 1] == '\0')
				{
					if (i - 1 >= 0 && j - 2 >= 0 && whichside(board[i - 1][j - 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 1 + '0';
						temp[3] = j - 2 + '0';
						result.push_back(temp);
					}
					if (i + 1 < board_row && j - 2 >= 0 && whichside(board[i + 1][j - 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 1 + '0';
						temp[3] = j - 2 + '0';
						result.push_back(temp);
					}
				}
			}
			else if (board[i][j] == m['b'])//是相
			{
				if (i + 1 <= halfrow2 && j + 1 < board_col && board[i + 1][j + 1] == '\0')
				{
					if (i + 2 <= halfrow2 && j + 2 < board_col && whichside(board[i + 2][j + 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 2 + '0';
						temp[3] = j + 2 + '0';
						result.push_back(temp);
					}
				}
				if (i + 1 <= halfrow2 && j - 1 >= 0 && board[i + 1][j - 1] == '\0')
				{
					if (i + 2 <= halfrow2 && j - 2 >= 0 && whichside(board[i + 2][j - 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i + 2 + '0';
						temp[3] = j - 2 + '0';
						result.push_back(temp);
					}
				}
				if (i - 1 >= halfrow1 && j + 1 < board_col && board[i - 1][j + 1] == '\0')
				{
					if (i - 2 >= halfrow1 && j + 2 < board_col && whichside(board[i - 2][j + 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 2 + '0';
						temp[3] = j + 2 + '0';
						result.push_back(temp);
					}
				}
				if (i - 1 >= halfrow1 && j - 1 >= 0 && board[i - 1][j - 1] == '\0')
				{
					if (i - 2 >= halfrow1 && j - 2 >= 0 && whichside(board[i - 2][j - 2]) != side)
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = i - 2 + '0';
						temp[3] = j - 2 + '0';
						result.push_back(temp);
					}
				}
			}
			else if (board[i][j] == m['a'])//是士
			{
				if (i + 1 <= row92 && j + 1 <= col92 && whichside(board[i + 1][j + 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + 1 + '0';
					temp[3] = j + 1 + '0';
					result.push_back(temp);
				}
				if (i + 1 <= row92 && j - 1 >= col91 && whichside(board[i + 1][j - 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + 1 + '0';
					temp[3] = j - 1 + '0';
					result.push_back(temp);
				}
				if (i - 1 >= row91 && j + 1 <= col92 && whichside(board[i - 1][j + 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i - 1 + '0';
					temp[3] = j + 1 + '0';
					result.push_back(temp);
				}
				if (i - 1 >= row91 && j - 1 >= col91 && whichside(board[i - 1][j - 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i - 1 + '0';
					temp[3] = j - 1 + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['k'])//是帅
			{
				//特殊情况直接对将
				int flag = 0;
				if (side == 'b')
				{
					for (k = i - 1; k >= 0; k--)//一路向下去找对面的将
					{
						if (board[k][j] == 'K')
						{
							flag = 1;
							break;
						}
						else if (board[k][j] != '\0')
						{
							break;
						}
					}
					if (flag == 1)//能对
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = k + '0';
						temp[3] = j + '0';
						result.push_back(temp);
					}
				}
				else if (side == 'r')
				{
					for (k = i + 1; k < board_row; k++)//一路向上
					{
						if (board[k][j] == 'k')
						{
							flag = 1;
							break;
						}
						else if (board[k][j] != '\0')
						{
							break;
						}
					}
					if (flag == 1)//能对
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = k + '0';
						temp[3] = j + '0';
						result.push_back(temp);
					}
				}
				//普通情况
				if (i + 1 <= row92 && whichside(board[i + 1][j]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + 1 + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				if (i - 1 >= row91 && whichside(board[i - 1][j]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i - 1 + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				if (j + 1 <= col92 && whichside(board[i][j + 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = j + 1 + '0';
					result.push_back(temp);
				}
				if (j - 1 >= col91 && whichside(board[i][j - 1]) != side)
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = j - 1 + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['c'])//是炮
			{
				//炮和车略有不同
				for (k = i + 1; k < board_row && board[k][j] == '\0'; k++)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = k + 1; k < board_row && board[k][j] == '\0'; k++)//找开炮点
					;
				if (k < board_row && whichside(board[k][j]) != side)//判断是不是能吃的子
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}

				for (k = i - 1; k >= 0 && board[k][j] == '\0'; k--)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = k - 1; k >= 0 && board[k][j] == '\0'; k--)//找开炮点
					;
				if (k >= 0 && whichside(board[k][j]) != side)//判断是不是能吃的子
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}

				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = k + 1; k < board_col && board[i][k] == '\0'; k++)//找开炮点
					;
				if (k < board_col && whichside(board[i][k]) != side)//判断是不是能吃的子
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}

				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = k - 1; k >= 0 && board[i][k] == '\0'; k--)//找开炮点
					;
				if (k >= 0 && whichside(board[i][k]) != side)//判断是不是能吃的子
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['p'])//是兵
			{
				//兵比较麻烦需要分类讨论
				if (side == 'b')//黑色方向下冲
				{
					if (i >= 5)//没过河
					{
						if (whichside(board[i - 1][j]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i - 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
					}
					else//过河了
					{
						if (i - 1 >= 0 && whichside(board[i - 1][j]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i - 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
						if (j - 1 >= 0 && whichside(board[i][j - 1]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j - 1 + '0';
							result.push_back(temp);
						}
						if (j + 1 < board_col && whichside(board[i][j + 1]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j + 1 + '0';
							result.push_back(temp);
						}
					}
				}
				else//红色方向上冲
				{
					if (i <= 4)//没过河
					{
						if (whichside(board[i + 1][j]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
					}
					else//过河了
					{
						if (i + 1 < board_row && whichside(board[i + 1][j]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
						if (j - 1 >= 0 && whichside(board[i][j - 1]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j - 1 + '0';
							result.push_back(temp);
						}
						if (j + 1 < board_col && whichside(board[i][j + 1]) != side)//冲
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j + 1 + '0';
							result.push_back(temp);
						}
					}
				}

			}
		}
	}
	return result;
}

//判断输赢
//简单地处理，只要谁将没了谁就输了
char judge(char(&board)[board_row][board_col])
{
	int i, j;
	int flag1,flag2;
	//在红色方找帅
	flag1 = 0;
	flag2 = 0;
	for (i = 0; i <=2; i++)
	{
		for (j = 3; j <= 5; j++)
		{
			if (board[i][j] == 'K')
			{
				flag1 = 1;
			}
			else if ( board[i][j] == 'k')
			{
				flag2 = 1;
			}
		}
	}
	//在黑色方找帅
	for (i = 7; i <= 9; i++)
	{
		for (j = 3; j <= 5; j++)
		{
			if (board[i][j] == 'K')
			{
				flag1 = 1;
			}
			else if (board[i][j] == 'k')
			{
				flag2 = 1;
			}
		}
	}
	if (flag1 == 0 && flag2 == 1)
		return 'b';
	else if (flag1 == 1 && flag2 == 0)
		return 'r';
	else
		return 'z';

}