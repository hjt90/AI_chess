#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
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
	char otherside = side == 'r' ? 'b' : 'r';
	int i, j, k;//一些随便的计数器
	string temp = "0000";//先放一个缓存
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
					if (whichside(board[k][j]) == otherside)
						break;
				}
				for (k = i - 1; k >= 0 && whichside(board[k][j]) != side; k--)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
					if (whichside(board[k][j]) == otherside)
						break;
				}
				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
					if (whichside(board[i][k]) == otherside)
						break;
				}
				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//找同一行的走法 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
					if (whichside(board[i][k]) == otherside)
						break;
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
				if (j - 1 >= 0 && board[i][j - 1] == '\0')
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

				for (k = j + 1; k < board_col && board[i][k] == '\0'; k++)//找同一行的走法 
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

				for (k = j - 1; k >= 0 && board[i][k] == '\0'; k--)//找同一行的走法 
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
	int flag1, flag2;
	//在红色方找帅
	flag1 = 0;
	flag2 = 0;
	for (i = 0; i <= 2; i++)
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

bool check_basicborder(int i, int j, int i1, int j1, int row0, int col0, int row1, int col1)
{

	if (i<row0 || i>row1)
		return false;
	else if (i1<row0 || i1>row1)
		return false;
	else if (j<col0 || j>col1)
		return false;
	else if (j1<col0 || j1>col1)
		return false;
	else
		return true;

}

/*fen规则
r车 n马 b相 a士 k帅 c炮 p兵
*/
bool is_correct_step(string step, char(&board)[board_row][board_col])
{
	int i, j, i1, j1;//提取位置信息
	i = step[0] - '0';
	j = step[1] - '0';
	i1 = step[2] - '0';
	j1 = step[3] - '0';
	char chara = board[step[0]][step[1]];//先把这个子找到
	if (chara == '\0')//如果移动了一个不存在的棋子
		return false;
	char side = whichside(chara);//找到这是哪一方的子
	if (side == whichside(board[i1][j1]))//起点和终点是同一方的子，显然也不行
		return false;
	/*
	-------------------------------
	此处可自行增加判定是否是正确的走子方的棋子
	-------------------------------
	*/

	int p;
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
	if (chara == m['r'])//是车
	{
		//越界
		if (check_basicborder(i, j, i1, j1, 0, 0, board_row, board_col) == false)
			return false;
		if (i == i1)//同一行
		{
			for (p = min(j, j1) + 1; p < max(j, j1); p++)
			{
				if (board[i][p] != '\0')
					return false;
			}
			return true;
		}
		else if (j == j1)//同一列
		{
			for (p = min(i, i1) + 1; p < max(i, i1); p++)
			{
				if (board[p][j] != '\0')
					return false;
			}
			return true;
		}
		else
			return false;
	}
	else if (chara == m['n'])//是马
	{
		//越界
		if (check_basicborder(i, j, i1, j1, 0, 0, board_row, board_col) == false)
			return false;
		//分别判断情况
		if ((i1 == i + 2 && j1 == j + 1) || (i1 == i + 2 && j1 == j - 1))
		{
			if (board[i + 1][j] != '\0')//蹩马腿
				return false;
			else
				return true;
		}
		else if ((i1 == i - 2 && j1 == j + 1) || (i1 == i - 2 && j1 == j - 1))
		{
			if (board[i - 1][j] != '\0')//蹩马腿
				return false;
			else
				return true;
		}
		else if ((i1 == i + 1 && j1 == j + 2) || (i1 == i - 1 && j1 == j + 2))
		{
			if (board[i][j + 1] != '\0')//蹩马腿
				return false;
			else
				return true;
		}
		else if ((i1 == i + 1 && j1 == j - 2) || (i1 == i - 1 && j1 == j - 2))
		{
			if (board[i][j - 1] != '\0')//蹩马腿
				return false;
			else
				return true;
		}
		else//根本就走错了
			return false;
	}
	else if (chara == m['b'])//是相
	{
		if (check_basicborder(i, j, i1, j1, halfrow1, 0, halfrow2, board_col) == false)
			return false;
		//分别判断情况
		if (i1 == i + 2 && j1 == j + 2)
		{
			if (board[i + 1][j + 1] != '\0')
				return false;
			else
				return true;
		}
		else if (i1 == i - 2 && j1 == j + 2)
		{
			if (board[i - 1][j + 1] != '\0')
				return false;
			else
				return true;
		}
		else if (i1 == i + 2 && j1 == j - 2)
		{
			if (board[i + 1][j - 1] != '\0')
				return false;
			else
				return true;
		}
		else if (i1 == i - 2 && j1 == j - 2)
		{
			if (board[i - 1][j - 1] != '\0')
				return false;
			else
				return true;
		}
		else
			return false;//压根就没走对
	}
	else if (chara == m['a'])//是士
	{
		//越界
		if (check_basicborder(i, j, i1, j1, row91, col91, row92, col92) == false)
			return false;
		//没走对
		if (abs(i1 - i) != 1 && abs(j1 - j) != 1)
			return false;
		return true;
	}
	else if (chara == m['k'])//是帅
	{
		char otherking = side == 'r' ? 'k' : 'K';
		//越界
		if (check_basicborder(i, j, i1, j1, 0, 0, board_row, board_col) == false)
			return false;
		if (board[i1][j1] != otherking)
		{
			if (check_basicborder(i, j, i1, j1, row91, col91, row92, col92) == false)
				return false;
		}

		if (abs(i1 - i) == 1)
		{
			if (j1 == j)
				return true;
		}
		else if (abs(j1 - j) == 1)
		{
			if (i1 == i)
				return true;
		}
		else
		{
			if (board[i1][j1] == otherking)
			{
				for (p = min(i, i1) + 1; p < max(i, i1); p++)
				{
					if (board[p][j] != '\0')
						return false;
				}
				return true;
			}
			return false;//走错了
		}

	}
	else if (chara == m['c'])//走炮
	{
		//越界
		if (check_basicborder(i, j, i1, j1, 0, 0, board_row, board_col) == false)
			return false;
		if (board[i1][j1] == '\0')//不开炮的情况
		{
			if (i == i1)//同一行
			{
				for (p = min(j, j1) + 1; p < max(j, j1); p++)
				{
					if (board[i][p] != '\0')
						return false;
				}
				return true;
			}
			else if (j == j1)//同一列
			{
				for (p = min(i, i1) + 1; p < max(i, i1); p++)
				{
					if (board[p][j] != '\0')
						return false;
				}
				return true;
			}
			else
				return false;
		}
		else//开炮的情况
		{
			int count = 0;
			if (i == i1)//同一行
			{
				for (p = min(j, j1) + 1; p < max(j, j1); p++)
				{
					if (board[i][p] == '\0')
						;
					else//跳板
						count++;
				}
				if (count == 1)
					return true;
				else
					return false;
			}
			else if (j == j1)//同一列
			{
				for (p = min(i, i1) + 1; p < max(i, i1); p++)
				{
					if (board[p][j] == '\0')
						;
					else//跳板
						count++;
				}
				if (count == 1)
					return true;
				else
					return false;
			}
			else
				return false;
		}
	}
	else if (chara == m['p'])
	{
		//越界
		if (check_basicborder(i, j, i1, j1, 0, 0, board_row, board_col) == false)
			return false;
		//兵需要分类讨论
		if (side == 'b')//黑色方向下冲
		{
			if (i >= 5)//没过河
			{
				if (i1 == i - 1 && j1 == j)
					return true;
				else
					return false;
			}
			else//过河了
			{
				if ((i1 == i - 1 && j1 == j) || (i1 == i && j1 == j + 1) || (i1 == i && j1 == j - 1))
					return true;
				else
					return false;
			}
		}
		else//红色方向上冲
		{
			if (i <= 4)//没过河
			{
				if (i1 == i + 1 && j1 == j)
					return true;
				else
					return false;
			}
			else//过河了
			{
				if ((i1 == i + 1 && j1 == j) || (i1 == i && j1 == j + 1) || (i1 == i && j1 == j - 1))
					return true;
				else
					return false;
			}
		}
	}
	else
		return false;
}

vector<chess_info> get_chess_info(char(&board)[board_row][board_col])//一个参数是棋盘
{
	vector<chess_info> infolist;
	int i, j, k;//一些随便的计数器
	chess_info temp;
	//存放一些界限
	//九宫格
	int row91, row92, col91, col92;
	//半场
	int halfrow1, halfrow2;
	//一些缓存
	char side, otherside;
	char tempside;
	//遍历棋盘
	for (i = 0; i < board_row; i++)
	{
		for (j = 0; j < board_col; j++)
		{
			side = whichside(board[i][j]);
			if (board[i][j] == '\0')//空的
				continue;
			otherside = side == 'r' ? 'b' : 'r';
			//规定边界
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
			//清空temp
			temp.row = i;
			temp.col = j;
			temp.attack.clear();
			temp.protection = 0;
			temp.movecount = 0;
			//对每一个棋盘位置进行分析
			if (board[i][j] == 'r' || board[i][j] == 'R')//是车
			{
				for (k = i + 1; k < board_row && whichside(board[k][j]) != side; k++)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					if (whichside(board[k][j]) == otherside)//吃子
					{
						temp.attack.push_back(board[k][j]);
						break;
					}
					else
						temp.movecount++;
				}
				if (k < board_row && whichside(board[k][j]) == side)
					temp.protection++;

				for (k = i - 1; k >= 0 && whichside(board[k][j]) != side; k--)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					if (whichside(board[k][j]) == otherside)//吃子
					{
						temp.attack.push_back(board[k][j]);
						break;
					}
					else
						temp.movecount++;
				}
				if (k >= 0 && whichside(board[k][j]) == side)
					temp.protection++;

				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//找同一行的走法 
				{
					if (whichside(board[i][k]) == otherside)//吃子
					{
						temp.attack.push_back(board[i][k]);
						break;
					}
					else
						temp.movecount++;
				}
				if (k < board_col && whichside(board[i][k]) == side)
					temp.protection++;

				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//找同一行的走法 
				{
					if (whichside(board[i][k]) == otherside)//吃子
					{
						temp.attack.push_back(board[i][k]);
						break;
					}
					else
						temp.movecount++;
				}
				if (k >= 0 && whichside(board[i][k]) == side)
					temp.protection++;
			}
			else if (board[i][j] == 'n' || board[i][j] == 'N')//是马
			{
				//先判断上下左右是否别马脚，然后在走
				if (i + 1 < board_row && board[i + 1][j] == '\0')
				{
					if (i + 2 < board_row && j - 1 >= 0)
					{
						tempside = whichside(board[i + 2][j - 1]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 2][j - 1]);
						else
							temp.movecount++;
					}
					if (i + 2 < board_row && j + 1 < board_col)
					{
						tempside = whichside(board[i + 2][j + 1]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 2][j + 1]);
						else
							temp.movecount++;
					}
				}
				if (i - 1 >= 0 && board[i - 1][j] == '\0')
				{
					if (i - 2 >= 0 && j - 1 >= 0)
					{
						tempside = whichside(board[i - 2][j - 1]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 2][j - 1]);
						else
							temp.movecount++;
					}
					if (i - 2 >= 0 && j + 1 < board_col)
					{
						tempside = whichside(board[i - 2][j + 1]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 2][j + 1]);
						else
							temp.movecount++;
					}
				}
				if (j + 1 < board_row && board[i][j + 1] == '\0')
				{
					if (i - 1 >= 0 && j + 2 < board_col)
					{
						tempside = whichside(board[i - 1][j + 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 1][j + 2]);
						else
							temp.movecount++;
					}
					if (i + 1 < board_row && j + 2 < board_col)
					{
						tempside = whichside(board[i + 1][j + 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 1][j + 2]);
						else
							temp.movecount++;
					}
				}
				if (j - 1 >= 0 && board[i][j - 1] == '\0')
				{
					if (i - 1 >= 0 && j - 2 >= 0)
					{
						tempside = whichside(board[i - 1][j - 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 1][j - 2]);
						else
							temp.movecount++;
					}
					if (i + 1 < board_row && j - 2 >= 0)
					{
						tempside = whichside(board[i + 1][j - 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 1][j - 2]);
						else
							temp.movecount++;
					}
				}
			}
			else if (board[i][j] == 'b' || board[i][j] == 'B')//是相
			{
				if (i + 1 <= halfrow2 && j + 1 < board_col && board[i + 1][j + 1] == '\0')
				{
					if (i + 2 <= halfrow2 && j + 2 < board_col)
					{
						tempside = whichside(board[i + 2][j + 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 2][j + 2]);
						else
							temp.movecount++;
					}
				}
				if (i + 1 <= halfrow2 && j - 1 >= 0 && board[i + 1][j - 1] == '\0')
				{
					if (i + 2 <= halfrow2 && j - 2 >= 0)
					{
						tempside = whichside(board[i + 2][j - 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 2][j - 2]);
						else
							temp.movecount++;
					}
				}
				if (i - 1 >= halfrow1 && j + 1 < board_col && board[i - 1][j + 1] == '\0')
				{
					if (i - 2 >= halfrow1 && j + 2 < board_col)
					{
						tempside = whichside(board[i - 2][j + 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 2][j + 2]);
						else
							temp.movecount++;
					}
				}
				if (i - 1 >= halfrow1 && j - 1 >= 0 && board[i - 1][j - 1] == '\0')
				{
					if (i - 2 >= halfrow1 && j - 2 >= 0)
					{
						tempside = whichside(board[i - 2][j - 2]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 2][j - 2]);
						else
							temp.movecount++;
					}
				}
			}
			else if (board[i][j] == 'a' || board[i][j] == 'A')//是士
			{
				if (i + 1 <= row92 && j + 1 <= col92)
				{
					tempside = whichside(board[i + 1][j + 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i + 1][j + 1]);
					else
						temp.movecount++;
				}
				if (i + 1 <= row92 && j - 1 >= col91)
				{
					tempside = whichside(board[i + 1][j - 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i + 1][j - 1]);
					else
						temp.movecount++;
				}
				if (i - 1 >= row91 && j + 1 <= col92)
				{
					tempside = whichside(board[i - 1][j + 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i - 1][j + 1]);
					else
						temp.movecount++;
				}
				if (i - 1 >= row91 && j - 1 >= col91)
				{
					tempside = whichside(board[i - 1][j - 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i - 1][j - 1]);
					else
						temp.movecount++;
				}
			}
			else if (board[i][j] == 'k' || board[i][j] == 'K')//是帅
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
						temp.attack.push_back('K');
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
						temp.attack.push_back('k');
					}
				}
				//普通情况
				if (i + 1 <= row92)
				{
					tempside = whichside(board[i + 1][j]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i + 1][j]);
					else
						temp.movecount++;
				}
				if (i - 1 >= row91)
				{
					tempside = whichside(board[i - 1][j]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i - 1][j]);
					else
						temp.movecount++;
				}
				if (j + 1 <= col92)
				{
					tempside = whichside(board[i][j + 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i][j + 1]);
					else
						temp.movecount++;
				}
				if (j - 1 >= col91)
				{
					tempside = whichside(board[i][j - 1]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i][j - 1]);
					else
						temp.movecount++;
				}
			}
			else if (board[i][j] == 'c' || board[i][j] == 'C')//是炮
			{
				//炮和车略有不同
				for (k = i + 1; k < board_row && board[k][j] == '\0'; k++)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp.movecount++;
				}
				for (k = k + 1; k < board_row && board[k][j] == '\0'; k++)//找开炮点
					;
				if (k < board_row)//判断是不是能吃的子
				{
					tempside = whichside(board[k][j]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[k][j]);
					else
						temp.movecount++;
				}

				for (k = i - 1; k >= 0 && board[k][j] == '\0'; k--)//找同一列的走法 (到被自己的棋子堵住为止）
				{
					temp.movecount++;
				}
				for (k = k - 1; k >= 0 && board[k][j] == '\0'; k--)//找开炮点
					;
				if (k >= 0)//判断是不是能吃的子
				{
					tempside = whichside(board[k][j]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[k][j]);
					else
						temp.movecount++;
				}

				for (k = j + 1; k < board_col && board[i][k] == '\0'; k++)//找同一行的走法 
				{
					temp.movecount++;
				}
				for (k = k + 1; k < board_col && board[i][k] == '\0'; k++)//找开炮点
					;
				if (k < board_col)//判断是不是能吃的子
				{
					tempside = whichside(board[i][k]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i][k]);
					else
						temp.movecount++;
				}

				for (k = j - 1; k >= 0 && board[i][k] == '\0'; k--)//找同一行的走法 
				{
					temp.movecount++;
				}
				for (k = k - 1; k >= 0 && board[i][k] == '\0'; k--)//找开炮点
					;
				if (k >= 0)//判断是不是能吃的子
				{
					tempside = whichside(board[i][k]);
					if (tempside == side)
						temp.protection++;
					else if (tempside == otherside)
						temp.attack.push_back(board[i][k]);
					else
						temp.movecount++;
				}
			}
			else if (board[i][j] == 'p' || board[i][j] == 'P')//是兵
			{
				//兵比较麻烦需要分类讨论
				if (side == 'b')//黑色方向下冲
				{
					if (i >= 5)//没过河
					{
						tempside = whichside(board[i - 1][j]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i - 1][j]);
						else
							temp.movecount++;
					}
					else//过河了
					{
						if (i - 1 >= 0)//冲
						{
							tempside = whichside(board[i - 1][j]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i - 1][j]);
							else
								temp.movecount++;
						}
						if (j - 1 >= 0)//冲
						{
							tempside = whichside(board[i][j - 1]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i][j - 1]);
							else
								temp.movecount++;
						}
						if (j + 1 < board_col)//冲
						{
							tempside = whichside(board[i][j + 1]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i][j + 1]);
							else
								temp.movecount++;
						}
					}
				}
				else//红色方向上冲
				{
					if (i <= 4)//没过河
					{
						tempside = whichside(board[i + 1][j]);
						if (tempside == side)
							temp.protection++;
						else if (tempside == otherside)
							temp.attack.push_back(board[i + 1][j]);
						else
							temp.movecount++;
					}
					else//过河了
					{
						if (i + 1 < board_row)//冲
						{
							tempside = whichside(board[i + 1][j]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i + 1][j]);
							else
								temp.movecount++;
						}
						if (j - 1 >= 0)//冲
						{
							tempside = whichside(board[i][j - 1]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i][j - 1]);
							else
								temp.movecount++;
						}
						if (j + 1 < board_col)//冲
						{
							tempside = whichside(board[i][j + 1]);
							if (tempside == side)
								temp.protection++;
							else if (tempside == otherside)
								temp.attack.push_back(board[i][j + 1]);
							else
								temp.movecount++;
						}
					}
				}

			}
			infolist.push_back(temp);
		}
	}
	return infolist;
}
