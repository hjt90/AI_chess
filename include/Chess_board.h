#pragma once
#include "const.h"
#include "score_table.h"
#include "GetPossibility.h"
#include "utils.h"

//游戏状态
enum GameResult : char
{
    RED_WIN = 'r',
    BLACK_WIN = 'b',
    R_DRAW = 'z'
};

//轮到谁下
enum gameTurn : char
{
    T_RED = 'r',
    T_BLACK = 'b'
};

// 帅(k)，士(a)，相(b)，马(n)，车(r)，炮(c)，兵(p)
// 红小写,黑大写
enum Pieces_type : char
{
    R_King = 'k',
    R_shuai = 'k',
    B_King = 'K',
    B_shuai = 'K',

    R_Advisors = 'a',
    R_shi = 'a',
    B_Advisors = 'A',
    B_shi = 'A',

    R_Bishop = 'b',
    R_xiang = 'b',
    B_Bishop = 'B',
    B_xiang = 'B',

    R_Knights = 'n',
    R_ma = 'n',
    B_Knights = 'N',
    B_ma = 'N',

    R_Rook = 'r',
    R_che = 'r',
    B_Rook = 'R',
    B_che = 'R',

    R_Cannons = 'c',
    R_pao = 'c',
    B_Cannons = 'C',
    B_pao = 'C',

    R_Pawn = 'p',
    R_bing = 'p',
    B_Pawn = 'P',
    B_bing = 'P',

    P_NONE = '\0'
};

//棋子移动
struct piece_move
{
    //起始坐标
    int from_row;
    int from_col;
    //终点坐标
    int to_row;
    int to_col;
    //是否吃子
    bool eat;
    Pieces_type eat_type;
};

//当前形势
typedef int position_values;
typedef int static_eval_values;     //静态评估值

struct piece_position
{
    int ROW;
    int COL;
};

typedef char chess_board[board_row][board_col];

class ChessBoard
{
private:
    position_values getvalue();

public:
    chess_board board;
    gameTurn myTurn;
    position_values value;

    ChessBoard();
    void move_piece_value(piece_move pos);
    void move_piece(piece_move pos);
    void remove_piece(piece_move pos);
    void remove_piece_value(piece_move pos);
};
