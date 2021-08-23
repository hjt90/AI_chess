#include <iostream>
#include <cstring>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;

/************************************************
���������
char board[10][9]: char�����飬���ڴ洢����, '\0'��ʾ��
string board_status : ��ʾ����״̬���ַ��� ֻ��FEN�е�һ����
string moves : ��ʾ�˶��Ķ���
���ز�����
�Ѿ����¹������� board
*************************************************/
void string2board(char (&board)[board_row][board_col], string &board_status, const vector<string> &moves)
{
    int index = 0;
	for (int r = board_row - 1; r >= 0; r--) //Сд��ĸΪ�ڷ�������Ǵ��ϵ���������
	{
		for (int c = 0; c < board_col; c++)
		{
			char chess = board_status[index]; //Ϊ�˷�ֹԽ��
			if (chess > '0' && chess <= '9')  //�ǿո�
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
			else if (chess == '/') //'/'�����������Ҫc--
			{
				index++;
				c--;
				continue;
			}
			board[r][c] = chess; //��������
			index++;
		}
	}
    //����moves��������
    //moves �� h2e2����ǰ�����ں�
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
