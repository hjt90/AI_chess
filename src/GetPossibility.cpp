#include<iostream>
#include<vector>
#include<map>
#include"../include/GetPossibility.h"
using namespace std;

/*fen����
r�� n�� b�� aʿ k˧ c�� p��
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

vector<string> getnodes(char(&board)[board_row][board_col], char side)//һ�����������̣��ڶ���������˭�ߣ�����fen����b�Ǻ�r�Ǻ죩
{
	vector<string> result;
	int i, j, k, q;//һЩ���ļ�����
	string temp="0000";//�ȷ�һ������
	//�ȷ�һ���ֵ����洢��ǰ���ӵķ���
	map<char, char> m;
	//���һЩ����
	//�Ź���
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
	//�볡
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
	//��������
	for (i = 0; i < board_row; i++)
	{
		for (j = 0; j < board_col; j++)
		{
			//��ÿһ������λ�ý��з���
			if (whichside(board[i][j]) != side)//�յĻ����Ǻ�ɫ��
				;
			else if (board[i][j] == m['r'])//�ǳ�
			{
				for (k = i + 1; k < board_row && whichside(board[k][j]) != side; k++)//��ͬһ�е��߷� (�����Լ������Ӷ�סΪֹ��
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = i - 1; k >= 0 && whichside(board[k][j]) != side; k--)//��ͬһ�е��߷� (�����Լ������Ӷ�סΪֹ��
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//��ͬһ�е��߷� 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//��ͬһ�е��߷� 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['n'])//����
			{
				//���ж����������Ƿ����ţ�Ȼ������
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
			else if (board[i][j] == m['b'])//����
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
			else if (board[i][j] == m['a'])//��ʿ
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
			else if (board[i][j] == m['k'])//��˧
			{
				//�������ֱ�ӶԽ�
				int flag = 0;
				if (side == 'b')
				{
					for (k = i - 1; k >= 0; k--)//һ·����ȥ�Ҷ���Ľ�
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
					if (flag == 1)//�ܶ�
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
					for (k = i + 1; k < board_row; k++)//һ·����
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
					if (flag == 1)//�ܶ�
					{
						temp[0] = i + '0';
						temp[1] = j + '0';
						temp[2] = k + '0';
						temp[3] = j + '0';
						result.push_back(temp);
					}
				}
				//��ͨ���
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
			else if (board[i][j] == m['c'])//����
			{
				//�ںͳ����в�ͬ
				for (k = i + 1; k < board_row && board[k][j] == '\0'; k++)//��ͬһ�е��߷� (�����Լ������Ӷ�סΪֹ��
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = k + 1; k < board_row && board[k][j] == '\0'; k++)//�ҿ��ڵ�
					;
				if (k < board_row && whichside(board[k][j]) != side)//�ж��ǲ����ܳԵ���
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}

				for (k = i - 1; k >= 0 && board[k][j] == '\0'; k--)//��ͬһ�е��߷� (�����Լ������Ӷ�סΪֹ��
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}
				for (k = k - 1; k >= 0 && board[k][j] == '\0'; k--)//�ҿ��ڵ�
					;
				if (k >= 0 && whichside(board[k][j]) != side)//�ж��ǲ����ܳԵ���
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = k + '0';
					temp[3] = j + '0';
					result.push_back(temp);
				}

				for (k = j + 1; k < board_col && whichside(board[i][k]) != side; k++)//��ͬһ�е��߷� 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = k + 1; k < board_col && board[i][k] == '\0'; k++)//�ҿ��ڵ�
					;
				if (k < board_col && whichside(board[i][k]) != side)//�ж��ǲ����ܳԵ���
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}

				for (k = j - 1; k >= 0 && whichside(board[i][k]) != side; k--)//��ͬһ�е��߷� 
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
				for (k = k - 1; k >= 0 && board[i][k] == '\0'; k--)//�ҿ��ڵ�
					;
				if (k >= 0 && whichside(board[i][k]) != side)//�ж��ǲ����ܳԵ���
				{
					temp[0] = i + '0';
					temp[1] = j + '0';
					temp[2] = i + '0';
					temp[3] = k + '0';
					result.push_back(temp);
				}
			}
			else if (board[i][j] == m['p'])//�Ǳ�
			{
				//���Ƚ��鷳��Ҫ��������
				if (side == 'b')//��ɫ�����³�
				{
					if (i >= 5)//û����
					{
						if (whichside(board[i - 1][j]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i - 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
					}
					else//������
					{
						if (i - 1 >= 0 && whichside(board[i - 1][j]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i - 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
						if (j - 1 >= 0 && whichside(board[i][j - 1]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j - 1 + '0';
							result.push_back(temp);
						}
						if (j + 1 < board_col && whichside(board[i][j + 1]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j + 1 + '0';
							result.push_back(temp);
						}
					}
				}
				else//��ɫ�����ϳ�
				{
					if (i <= 4)//û����
					{
						if (whichside(board[i + 1][j]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
					}
					else//������
					{
						if (i + 1 < board_row && whichside(board[i + 1][j]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + 1 + '0';
							temp[3] = j + '0';
							result.push_back(temp);
						}
						if (j - 1 >= 0 && whichside(board[i][j - 1]) != side)//��
						{
							temp[0] = i + '0';
							temp[1] = j + '0';
							temp[2] = i + '0';
							temp[3] = j - 1 + '0';
							result.push_back(temp);
						}
						if (j + 1 < board_col && whichside(board[i][j + 1]) != side)//��
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

//�ж���Ӯ
//�򵥵ش���ֻҪ˭��û��˭������
char judge(char(&board)[board_row][board_col])
{
	int i, j;
	int flag1,flag2;
	//�ں�ɫ����˧
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
	//�ں�ɫ����˧
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