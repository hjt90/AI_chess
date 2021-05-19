//该头文件储存估值函数各种棋子每一个位置的得分（参考了去年AI）
//以及各个棋子的棋子分
#pragma once
#include <vector>
#include <iostream>
#include "const.h"
using namespace std;


static int chess_index[130];//建立棋子类型和索引的映射，快速寻找


//计算当前局面得分
//board为棋盘，my_turn为我方棋子颜色'r'表示红色，'b'表示黑色
int cal_score(char (&board)[board_row][board_col], char my_turn,int chess_index[]);

struct Chess{
const char name;//棋子的名字，与棋盘中的棋子名字相同，用来索引
const uint8_t position_score[board_row][board_col];//棋子的位置得分
int value;//棋子自身价值
uint8_t type;//表示棋子是否过河
};
// 子力位置价值表，针对红方，黑方需要转换
// 帅(k)，士(a)，相(b)，马(n)，车(r)，炮(c)，兵(p)
static Chess chesses[7] = 
{
{   'k',
    {{0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  1,  1,  1,  0,  0,  0},
    {0,  0,  0,  2,  2,  2,  0,  0,  0},
    {0,  0,  0, 11, 15, 11,  0,  0,  0}},
    10000,//这里不知道给帅多少，暂且给最多吧
    0 //未过河
},
{   'a',
    {{0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0, 20,  0, 20,  0,  0,  0},
    {0,  0,  0,  0, 23,  0,  0,  0,  0},
    {0,  0,  0, 20,  0, 20,  0,  0,  0}},
    200,
    0 //未过河
},
{   'b',
    {{0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0, 20,  0,  0,  0, 20,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {18, 0,  0,  0, 23,  0,  0,  0, 18},
    {0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0, 20,  0,  0,  0, 20,  0,  0}},
    200,
    0 //未过河
},
{   'n',
	{{90, 90, 90, 96, 90, 96, 90, 90, 90},
	{90, 96,103, 97, 94, 97,103, 96, 90},
	{92, 98, 99,103, 99,103, 99, 98, 92},
	{93,108,100,107,100,107,100,108, 93},
	{90,100, 99,103,104,103, 99,100, 90},
	{90, 98,101,102,103,102,101, 98, 90},
	{92, 94, 98, 95, 98, 95, 98, 94, 92},
	{93, 92, 94, 95, 92, 95, 94, 92, 93},
	{85, 90, 92, 93, 78, 93, 92, 90, 85},
	{88, 85, 90, 88, 90, 88, 90, 85, 88}},
    400,
    0 //未过河
},
{   'r',
	{{206,208,207,213,214,213,207,208,206},
	{206,212,209,216,233,216,209,212,206},
	{206,208,207,214,216,214,207,208,206},
	{206,213,213,216,216,216,213,213,206},
	{208,211,211,214,215,214,211,211,208},
	{208,212,212,214,215,214,212,212,208},
	{204,209,204,212,214,212,204,209,204},
	{198,208,204,212,212,212,204,208,198},
	{200,208,206,212,200,212,206,208,200},
	{194,206,204,212,200,212,204,206,194}},
    900,
    0 //未过河
},
{   'c',
	{{100,100, 96, 91, 90, 91, 96,100,100},
	{ 98, 98, 96, 92, 89, 92, 96, 98, 98},
	{ 97, 97, 96, 91, 92, 91, 96, 97, 97},
	{ 96, 99, 99, 98,100, 98, 99, 99, 96},
	{ 96, 96, 96, 96,100, 96, 96, 96, 96},
	{ 95, 96, 99, 96,100, 96, 99, 96, 95},
	{ 96, 96, 96, 96, 96, 96, 96, 96, 96},
	{ 97, 96,100, 99,101, 99,100, 96, 97},
	{ 96, 97, 98, 98, 98, 98, 98, 97, 96},
	{ 96, 96, 97, 99, 99, 99, 97, 96, 96}},
    450,
    0 //未过河
},
{   'p',
	{{ 9,  9,  9, 11, 13, 11,  9,  9,  9},
	{19, 24, 34, 42, 44, 42, 34, 24, 19},
	{19, 24, 32, 37, 37, 37, 32, 24, 19},
	{19, 23, 27, 29, 30, 29, 27, 23, 19},
	{14, 18, 20, 27, 29, 27, 20, 18, 14},
	{ 7,  0, 13,  0, 16,  0, 13,  0,  7},
	{ 7,  0,  7,  0, 15,  0,  7,  0,  7},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}},
    100,//为过河的兵是100，过了河是200
    0 //未过河
}
};






