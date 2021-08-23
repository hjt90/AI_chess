//该头文件储存估值函数各种棋子每一个位置的得分（参考了去年AI）
//以及各个棋子的棋子分
#pragma once
#include <vector>
#include <iostream>
#include "const.h"
using namespace std;


//尝试使用动态更新方式
int init_score(char(&board)[board_row][board_col], char my_turn);

//计算当前局面得分
//board为棋盘，my_turn为我方棋子颜色'r'表示红色，'b'表示黑色
int cal_score(char (&board)[board_row][board_col], char my_turn);
void board_initial(char (&board)[board_row][board_col]); //初始化棋盘,没有为'+'



//计算当前局面启发式
//board为棋盘，my_turn为我方棋子颜色'r'表示红色，'b'表示黑色
int cal_enlighten(char(&board)[board_row][board_col], char my_turn);



struct Chess
{
    const char name;                                    //棋子的名字，与棋盘中的棋子名字相同，用来索引
    const int8_t position_score[board_row][board_col]; //棋子的位置得分
    int value;                                          //棋子自身价值
    int flex;                                       //表示棋子灵活性权重
};

// 子力位置价值表，针对红方，黑方需要转换
// 帅(k)，士(a)，相(b)，马(n)，车(r)，炮(c)，兵(p)
static Chess chesses[7] =
    {
        {
            'k',
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, -15, -10, -15, 0, 0, 0},
             {0, 0, 0, -10, -20, -10, 0, 0, 0},
             {0, 0, 0, 10, 30, 10, 0, 0, 0}},
            1000000, //这里不知道给帅多少，暂且给最多吧
            0      //
        },
        {
            'a',
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 10, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}},
            200,
            1 //
        },
        {
            'b',
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {-10, 0, 0, 0, 20, 0, 0, 0, -10},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}},
            200,
            1 //
        },
        {
            'n',
            {{5, 10, 15, 12, 15, 12, 15, 10, 5},
             {5, 22, 20, 22, 7, 22, 20, 22, 5},
             {5, 15, 20, 17, 20, 17, 20, 15, 5},
             {5, 17, 20, 22, 20, 22, 20, 17, 5},
             {5, 10, 15, 15, 20, 15, 15, 12, 5},
             {-5, 0, -3, 1, 1, 1, -3, 0, -5},
             {-5, -2, 0, -1, 1, -1, 0, -2, -5},
             {-8, 0, 0, -4, -7, -4, 0, 0, -8},
             {-5, -2, 0, -6, -4, -6, 0, -2, -5},
             {-5, -5, -8, -10, -10, -10, -8, -5, -5}},
            400,
            13 //未过河
        },
        {
            'r',
            {{15, 15, 12, 17, 20, 17, 12, 15, 15},
             {15, 17, 15, 22, 17, 22, 15, 17, 15},
             {12, 15, 15, 17, 17, 17, 15, 15, 12},
             {0, 2, 0, 17, 15, 17, 0, 2, 0},
             {10, 10, 7, 25, 25, 25, 7, 10, 10},
             {10, 10, 10, 26, 26, 26, 10, 10, 10},
             {0, -2, 0, 14, 14, 14, 0, -2, 0},
             {0, 0, 0, 11, 11, 11, 0, 0, 0},
             {0, -2, 0, 9, 11, 9, 0, -2, 0},
             {-10, 0, 0, 10, 10, 10, 0, 0, -10}},
            900,
            7 //未过河
        },
        {
            'c',
            {{0, 0, -3, -3, 0, -3, -3, 0, 0},
             {0, 2, 0, 2, -3, 2, 0, 2, 0},
             {-3, 0, 0, -3, -3, -3, 0, 0, -3},
             {0, 2, 0, 2, 0, 2, 0, 2, 0},
             {0, 0, -3, 0, 0, 0, -3, 0, 0},
             {0, 0, 0, 1, 1, 1, 0, 0, 0},
             {0, -2, 0, -1, 1, -1, 0, -2, 0},
             {0, 0, 0, -4, 3, -4, 0, 0, 0},
             {0, -2, 0, -6, -4, -6,0 ,-2 ,0},
             {0, 0, 0, -5, -5, -5, 0, 0, 0}},
            450,
            7 //未过河
        },
        {
            'p',
            {{0, 0, 5, 5, 10, 5, 5, 0, 0},
             {5, 10, 21, 30, 42, 30, 21, 10, 5},
             {4, 8, 18, 26, 37, 26, 18, 8, 4},
             {3, 6, 10, 17, 22, 17, 10, 6, 3},
             {2, 4, 7, 8, 12, 8, 7, 4, 2},
             {1, 2, 4, 4, 7, 4, 4, 2, 1},
             {0, 0, 1, 0, 2, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}},
            100, 
            15    
        }};
