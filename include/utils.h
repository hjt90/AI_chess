#include <iostream>
#include <cstring>
#include <vector>
#include "const.h"
#pragma once
using namespace std;
int char2index(char ch);                                             //用于将字符转为整数索引
void chess_clear(char (&board)[board_row][board_col], int r, int c); //将棋子清除

void chess_add(char (&board)[board_row][board_col], int r, int c, char value); //添加棋子

//用来读取position后面跟着的字符串，who_turn代表某人的回合，board_status代表棋盘状态，moves表示还要走的步数
void read_position(char &who_turn, string &board_status, vector<string> &moves);

/************************************************
输入参数：
char board[10][9]: char型数组，用于存储棋盘, '\0'表示空
string board_status : 表示棋盘状态的字符串 只是FEN中的一部分
string moves : 表示运动的动作
返回参数：
已经更新过的棋盘 board
*************************************************/
void string2board(char (&board)[board_row][board_col], string &board_status, const vector<string> &moves);


void board_print(char (&board)[board_row][board_col]); //输出棋盘
void board_print(char(&board)[board_row][board_col], ofstream& out);//输出棋盘

//判断棋的类型，返回为'r'表示为红，返回为'b'表示为黑
char chess_type(char chess);