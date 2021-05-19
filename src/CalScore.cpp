//该CPP计算当前局面得分
#include <iostream>
#include <vector>
#include "../include/score_table.h"
#include "../include/const.h"
#include "../include/utils.h"
using namespace std;


//计算当前局面得分
//board为棋盘，my_turn为我方棋子颜色'r'表示红色，'b'表示黑色
int cal_score(char (&board)[board_row][board_col], char my_turn,int chess_index[])
{
    //扫一遍数组，完成位置评分和棋子存活评分
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
            char type = chess_type(board[r][c]);//判断棋子颜色
            if(type == 'r')//红方
            {
                score+=sign*chesses[chess_index[board[r][c]]].position_score[r][c];//位置得分
                score+=sign*chesses[chess_index[board[r][c]]].value;//棋子得分
                // score_r+=sign*chesses[chess_index[board[r][c]]].position_score[r][c];//位置得分
                // score_r+=sign*chesses[chess_index[board[r][c]]].value;//棋子得分
            }
            else if(type=='b')//黑方
            {
                score-=sign*chesses[chess_index[board[r][c]]].position_score[board_row-1-r][board_col-1-c];//位置得分，黑方需要做对称转换
                score-=sign*chesses[chess_index[board[r][c]]].value;//棋子得分
                // score_b+=sign*chesses[chess_index[board[r][c]]].position_score[board_row-1-r][board_col-1-c];//位置得分，黑方需要做对称转换
                // score_b+=sign*chesses[chess_index[board[r][c]]].value;//棋子得分
            }
        }
    // cout<<"红方得分 : "<<score_r<<endl;
    // cout<<"黑方得分 : "<<score_b<<endl;
    
    return score;
}

