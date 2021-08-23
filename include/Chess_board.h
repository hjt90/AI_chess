#pragma once
#include "const.h"
#include "score_table.h"
#include "GetPossibility.h"
#include "utils.h"

//��Ϸ״̬
enum GameResult : char
{
    RED_WIN = 'r',
    BLACK_WIN = 'b',
    R_DRAW = 'z'
};

//�ֵ�˭��
enum gameTurn : char
{
    T_RED = 'r',
    T_BLACK = 'b'
};

// ˧(k)��ʿ(a)����(b)����(n)����(r)����(c)����(p)
// ��Сд,�ڴ�д
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

//�����ƶ�
struct piece_move
{
    //��ʼ����
    int from_row;
    int from_col;
    //�յ�����
    int to_row;
    int to_col;
    //�Ƿ����
    bool eat;
    Pieces_type eat_type;
};

//��ǰ����
typedef int position_values;
typedef int static_eval_values;     //��̬����ֵ

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
