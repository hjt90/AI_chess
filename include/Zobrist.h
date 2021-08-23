#pragma once
#include "const.h"

typedef uint64_t U64;
typedef uint32_t U32;

/*********************************************************
* 函数名: init_zobrist
* 功能:  初始化zobrist中使用到的各项随机数和map等数据
*********************************************************/
void init_zobrist();

/*********************************************************
* 函数名: get_zobrist_by_board
* 功能:  根据棋盘和当前下棋的人生成zobrist值
* board: 当前棋盘
* player: 当前走棋方
* 返回值: 棋盘的zobrist值
*********************************************************/
U64 get_zobrist_by_board(const char(&board)[board_row][board_col], const char player);

/*********************************************************
* 函数名: get_zobrist_by_move
* 功能:  根据原zobrist值,棋盘和走法,计算走一步后的zobrist值
* board: 当前棋盘
* zobrist_old: 走之前的zobrist值
* move: 着法. 如1234,表示1行2列走到3行4列
* 返回值: 按照move走了一步以后的新棋盘的zobrist值
*********************************************************/
U64 get_zobrist_by_move(const char(&board)[board_row][board_col], const U64 zobrist_old, const std::string& move);

/*********************************************************
* 函数名: get_mirror_zobrist_by_board
* 功能:  根据棋盘和当前下棋的人生成**镜像局面**zobrist值
* board: 当前棋盘
* player: 当前走棋方
* 返回值: **镜像局面**棋盘的zobrist值
*********************************************************/
U64 get_mirror_zobrist_by_board(const char(&board)[board_row][board_col], const char player);

/*********************************************************
* 函数名: get_mirror_zobrist_by_move
* 功能:  根据原**镜像局面**zobrist值,棋盘和走法,计算走一步后的**镜像局面**zobrist值
* board: 当前棋盘
* mirr_zobrist_old: 走之前**镜像局面**的zobrist值
* move: 着法. 如1234,表示1行2列走到3行4列
* 返回值: 按照move走了一步以后的**镜像局面**新棋盘的zobrist值
* 注意: board和move均传入正向即可,函数中会自动转换.
*********************************************************/
U64 get_mirror_zobrist_by_move(const char(&board)[board_row][board_col], const U64 mirr_zobrist_old, const std::string& move);