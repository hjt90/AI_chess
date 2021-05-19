#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
using namespace std;

int char2index(char ch)//用于将字符转为整数索引
{
    if(ch>='0'&&ch<='9')
        return ch-'0';
    else
        return ch-'a';
}

void chess_clear(char (&board)[board_row][board_col],int r,int c)//将棋子清除
{
    board[r][c] = '\0';
}

void chess_add(char (&board)[board_row][board_col],int r,int c,char value)//添加棋子
{
    board[r][c] = value;
}


void board_print(char (&board)[board_row][board_col])//输出棋盘
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

// 帅(k)，士(a)，相(b)，马(n)，车(r)，炮(c)，兵(p)
void board_initial(char (&board)[board_row][board_col],int chess_index[])//初始化棋盘,没有为'\0'
{
    for(int i=0;i<board_row;i++)
        for(int j=0;j<board_col;j++)
            board[i][j] = '\0';
    //初始红方棋子索引
    chess_index['k'] = 0;
    chess_index['a'] = 1;
    chess_index['b'] = 2;
    chess_index['n'] = 3;
    chess_index['r'] = 4;
    chess_index['c'] = 5;
    chess_index['p'] = 6;

    //初始黑方棋子索引
    chess_index['K'] = 0;
    chess_index['A'] = 1;
    chess_index['B'] = 2;
    chess_index['N'] = 3;
    chess_index['R'] = 4;
    chess_index['C'] = 5;
    chess_index['P'] = 6;
}

//判断棋的类型，返回为'r'表示为红，返回为'b'表示为黑
char chess_type(char chess)
{
    if(chess>='a'&&chess<='z')
        return 'r';
    else if(chess>='A'&&chess<='Z')
        return 'b';
    else
        return '\0';
}



