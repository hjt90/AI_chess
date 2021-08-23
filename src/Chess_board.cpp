#include "../include/Chess_board.h"
#include <string.h>
#include "../include/Search.h"




ChessBoard::ChessBoard()
{
}

//position_values ChessBoard::getvalue()
//{
//    position_values ret;
//    ret = cal_score(board, myTurn);
//    return ret;
//}

//void ChessBoard::move_piece_value(piece_move move)
//{
//    board[move.to_row][move.to_col] = board[move.from_row][move.from_col];
//    board[move.from_row][move.from_col] = P_NONE;
//    value = getvalue();
//    return;
//}

void ChessBoard::move_piece(piece_move move)
{
    board[move.to_row][move.to_col] = board[move.from_row][move.from_col];
    board[move.from_row][move.from_col] = P_NONE;
    //更新棋子的总棋力值
#if is_dynamic
    int sign = 1;//判断棋子颜色
    if (myTurn == T_RED)
        sign = 1;
    else if (myTurn == T_BLACK)
        sign = -1;
    //吃子时更新棋力值以及相应的位置
    if (move.eat == true)//如果吃子
    {
        char type = chess_type(move.eat_type); //判断被吃的棋子颜色
        if (type == 'r')                     //红方
        {
            chess_score -= sign * chesses[chess_index[move.eat_type]].value; //棋子得分
            position_score -= sign * chesses[chess_index[move.eat_type]].position_score[move.to_row][move.to_col]; //我方对应位置的棋位置得分为零
        }
        else if (type == 'b') //黑方
        {
            chess_score += sign * chesses[chess_index[move.eat_type]].value;//棋子得分
            position_score += sign * chesses[chess_index[move.eat_type]].position_score[board_row - 1 - move.to_row][board_col - 1 - move.to_col]; //位置得分，黑方需要做对称转换
        }
    }
    //更新位置值
    int f_r = move.from_row;
    int f_c = move.from_col;
    int t_r = move.to_row;
    int t_c = move.to_col;//定义一下变量好表示
    int chess = board[move.to_row][move.to_col];
    char type_pos = chess_type(chess); //判断移动的棋子棋子颜色
    if (type_pos == 'r')                     //红方
        position_score += (sign * chesses[chess_index[chess]].position_score[t_r][t_c] - sign * chesses[chess_index[chess]].position_score[f_r][f_c]); //更新位置值
    else if (type_pos == 'b') //黑方
        position_score -= (sign * chesses[chess_index[chess]].position_score[board_row - 1 - t_r][board_col - 1 - t_c] - sign * chesses[chess_index[chess]].position_score[board_row - 1 - f_r][board_col - 1 - f_c]); //位置得分，黑方需要做对称转换
#endif
    return;
}

void ChessBoard::remove_piece(piece_move move)
{
    board[move.from_row][move.from_col] = board[move.to_row][move.to_col];
    board[move.to_row][move.to_col] = move.eat ? (char)move.eat_type : (char)P_NONE;
    //更新棋子的总棋力值
#if is_dynamic
    int sign = 1;//判断棋子颜色
    if (myTurn == T_RED)
        sign = 1;
    else if (myTurn == T_BLACK)
        sign = -1;
    //吃子时更新棋力值以及相应的位置
    if (move.eat == true)//如果吃子
    {
        char type = chess_type(move.eat_type); //判断被吃的棋子颜色
        if (type == 'r')                     //红方
        {
            chess_score += sign * chesses[chess_index[move.eat_type]].value; //棋子得分
            position_score += sign * chesses[chess_index[move.eat_type]].position_score[move.to_row][move.to_col]; //我方对应位置的棋位置得分为零
        }
        else if (type == 'b') //黑方
        {
            chess_score -= sign * chesses[chess_index[move.eat_type]].value;//棋子得分
            position_score -= sign * chesses[chess_index[move.eat_type]].position_score[board_row - 1 - move.to_row][board_col - 1 - move.to_col]; //位置得分，黑方需要做对称转换
        }
    }
    //更新位置值
    int f_r = move.from_row;
    int f_c = move.from_col;
    int t_r = move.to_row;
    int t_c = move.to_col;//定义一下变量 好表示
    char type_pos = chess_type(board[move.from_row][move.from_col]); //判断移动的棋子棋子颜色
    if (type_pos == 'r')                     //红方
        position_score -= (sign * chesses[chess_index[board[f_r][f_c]]].position_score[t_r][t_c] - sign * chesses[chess_index[board[f_r][f_c]]].position_score[f_r][f_c]); //更新位置值
    else if (type_pos == 'b') //黑方
        position_score += (sign * chesses[chess_index[board[f_r][f_c]]].position_score[board_row - 1 - t_r][board_col - 1 - t_c] - sign * chesses[chess_index[board[f_r][f_c]]].position_score[board_row - 1 - f_r][board_col - 1 - f_c]); //位置得分，黑方需要做对称转换
#endif
    return;
}

//void ChessBoard::remove_piece_value(piece_move move)
//{
//    remove_piece(move);
//    value = getvalue();
//    return;
//}
