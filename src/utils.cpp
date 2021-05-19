#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
using namespace std;

int char2index(char ch)//���ڽ��ַ�תΪ��������
{
    if(ch>='0'&&ch<='9')
        return ch-'0';
    else
        return ch-'a';
}

void chess_clear(char (&board)[board_row][board_col],int r,int c)//���������
{
    board[r][c] = '\0';
}

void chess_add(char (&board)[board_row][board_col],int r,int c,char value)//�������
{
    board[r][c] = value;
}


void board_print(char (&board)[board_row][board_col])//�������
{
    for(int i=0;i<board_row;i++)
    {
        for(int j=0;j<board_col;j++)
        {
            if(board[i][j]=='\0')
                cout<<"  ";
            else
                cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

// ˧(k)��ʿ(a)����(b)����(n)����(r)����(c)����(p)
void board_initial(char (&board)[board_row][board_col],int chess_index[])//��ʼ������,û��Ϊ'\0'
{
    for(int i=0;i<board_row;i++)
        for(int j=0;j<board_col;j++)
            board[i][j] = '\0';
    //��ʼ�췽��������
    chess_index['k'] = 0;
    chess_index['a'] = 1;
    chess_index['b'] = 2;
    chess_index['n'] = 3;
    chess_index['r'] = 4;
    chess_index['c'] = 5;
    chess_index['p'] = 6;

    //��ʼ�ڷ���������
    chess_index['K'] = 0;
    chess_index['A'] = 1;
    chess_index['B'] = 2;
    chess_index['N'] = 3;
    chess_index['R'] = 4;
    chess_index['C'] = 5;
    chess_index['P'] = 6;
}

//�ж�������ͣ�����Ϊ'r'��ʾΪ�죬����Ϊ'b'��ʾΪ��
char chess_type(char chess)
{
    if(chess>='a'&&chess<='z')
        return 'r';
    else if(chess>='A'&&chess<='Z')
        return 'b';
    else
        return '\0';
}



