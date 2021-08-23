#include <iostream>
#include <string>
#include "const.h"

//开局库信息
struct BookInfo		//作为map对应关系的参考
{
	//uint32_t dwLock;
	uint16_t move;	//特别注意,此处的move实际上已经是以4个char的形式存储,每个char占4bit
	uint16_t weight;
};

//初始化开局库.此函数需要在main函数初始时调用
void init_opening_book();

/*********************************************************
* 函数名: move_to_uccimove
* 功能:  将我们的move转换为ucci的move格式
* move: 我们的着法字符串,如"1234"表示1行2列走到3行4列
* 返回值: ucci的move串,如"1234"对应"c1e3"
*********************************************************/
std::string move_to_uccimove(const std::string move);

/*********************************************************
* 函数名: search_openging_book
* 功能:  查找开局库
* zobrist: 当前棋盘的zobrist值
* mirr_zobrist: 当前棋盘的**镜像**局面的zobrist值
* board: 当前棋盘
* 返回值: 着法列表,如"1234"表示1行2列走到3行4列
* 注意: 返回值可能是空vector,表示开局库没有着法
*********************************************************/
std::vector<std::string> search_openging_book(const uint64_t zobrist, const uint64_t mirr_zobrist, const char(&board)[board_row][board_col]);