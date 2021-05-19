#pragma once
#include<vector>
#include<string>
using namespace std;
/*
//可能的解的结构体
struct pnode
{
	//起始坐标
	int x1;
	int y1;
	//终点坐标
	int x2;
	int y2;
	//是否吃子
	bool eat;
};
*/

//常数(我这里为了我实现方便再定义一次，合并时可以去除)
const int board_col = 9; //棋盘的列 
const int board_row = 10; //棋盘的行

char whichside(char c);//辅助的函数
vector<string> getnodes(char(&board)[board_row][board_col], char side);//一个参数是棋盘，第二个参数是谁走（按照fen规则b是黑r是红）
//返回的是一个有string的vector，string取前四位，分别是起始行，起始列，终点行，终点列
char judge(char(&board)[board_row][board_col]);//判断输赢，红赢返回r，黑赢返回b，其余返回z
