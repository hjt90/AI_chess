//��CPP���㵱ǰ����÷�
#include <iostream>
#include <vector>
#include "../include/score_table.h"
#include "../include/const.h"
#include "../include/utils.h"
using namespace std;


//���㵱ǰ����÷�
//boardΪ���̣�my_turnΪ�ҷ�������ɫ'r'��ʾ��ɫ��'b'��ʾ��ɫ
int cal_score(char (&board)[board_row][board_col], char my_turn,int chess_index[])
{
    //ɨһ�����飬���λ�����ֺ����Ӵ������
    int sign = 1;
    if(my_turn == 'r')
        sign = 1;
    else if(my_turn == 'b')
        sign = -1;
    int score = 0;
    // int score_r = 0;
    // int score_b = 0;
    for(int r=0;r<board_row;r++)
        for(int c=0;c<board_col;c++)
        {
            char type = chess_type(board[r][c]);//�ж�������ɫ
            if(type == 'r')//�췽
            {
                score+=sign*chesses[chess_index[board[r][c]]].position_score[r][c];//λ�õ÷�
                score+=sign*chesses[chess_index[board[r][c]]].value;//���ӵ÷�
                // score_r+=sign*chesses[chess_index[board[r][c]]].position_score[r][c];//λ�õ÷�
                // score_r+=sign*chesses[chess_index[board[r][c]]].value;//���ӵ÷�
            }
            else if(type=='b')//�ڷ�
            {
                score-=sign*chesses[chess_index[board[r][c]]].position_score[board_row-1-r][board_col-1-c];//λ�õ÷֣��ڷ���Ҫ���Գ�ת��
                score-=sign*chesses[chess_index[board[r][c]]].value;//���ӵ÷�
                // score_b+=sign*chesses[chess_index[board[r][c]]].position_score[board_row-1-r][board_col-1-c];//λ�õ÷֣��ڷ���Ҫ���Գ�ת��
                // score_b+=sign*chesses[chess_index[board[r][c]]].value;//���ӵ÷�
            }
        }
    // cout<<"�췽�÷� : "<<score_r<<endl;
    // cout<<"�ڷ��÷� : "<<score_b<<endl;
    
    return score;
}

