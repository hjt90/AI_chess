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
    //�������ӵ�������ֵ
#if is_dynamic
    int sign = 1;//�ж�������ɫ
    if (myTurn == T_RED)
        sign = 1;
    else if (myTurn == T_BLACK)
        sign = -1;
    //����ʱ��������ֵ�Լ���Ӧ��λ��
    if (move.eat == true)//�������
    {
        char type = chess_type(move.eat_type); //�жϱ��Ե�������ɫ
        if (type == 'r')                     //�췽
        {
            chess_score -= sign * chesses[chess_index[move.eat_type]].value; //���ӵ÷�
            position_score -= sign * chesses[chess_index[move.eat_type]].position_score[move.to_row][move.to_col]; //�ҷ���Ӧλ�õ���λ�õ÷�Ϊ��
        }
        else if (type == 'b') //�ڷ�
        {
            chess_score += sign * chesses[chess_index[move.eat_type]].value;//���ӵ÷�
            position_score += sign * chesses[chess_index[move.eat_type]].position_score[board_row - 1 - move.to_row][board_col - 1 - move.to_col]; //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
        }
    }
    //����λ��ֵ
    int f_r = move.from_row;
    int f_c = move.from_col;
    int t_r = move.to_row;
    int t_c = move.to_col;//����һ�±����ñ�ʾ
    int chess = board[move.to_row][move.to_col];
    char type_pos = chess_type(chess); //�ж��ƶ�������������ɫ
    if (type_pos == 'r')                     //�췽
        position_score += (sign * chesses[chess_index[chess]].position_score[t_r][t_c] - sign * chesses[chess_index[chess]].position_score[f_r][f_c]); //����λ��ֵ
    else if (type_pos == 'b') //�ڷ�
        position_score -= (sign * chesses[chess_index[chess]].position_score[board_row - 1 - t_r][board_col - 1 - t_c] - sign * chesses[chess_index[chess]].position_score[board_row - 1 - f_r][board_col - 1 - f_c]); //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
#endif
    return;
}

void ChessBoard::remove_piece(piece_move move)
{
    board[move.from_row][move.from_col] = board[move.to_row][move.to_col];
    board[move.to_row][move.to_col] = move.eat ? (char)move.eat_type : (char)P_NONE;
    //�������ӵ�������ֵ
#if is_dynamic
    int sign = 1;//�ж�������ɫ
    if (myTurn == T_RED)
        sign = 1;
    else if (myTurn == T_BLACK)
        sign = -1;
    //����ʱ��������ֵ�Լ���Ӧ��λ��
    if (move.eat == true)//�������
    {
        char type = chess_type(move.eat_type); //�жϱ��Ե�������ɫ
        if (type == 'r')                     //�췽
        {
            chess_score += sign * chesses[chess_index[move.eat_type]].value; //���ӵ÷�
            position_score += sign * chesses[chess_index[move.eat_type]].position_score[move.to_row][move.to_col]; //�ҷ���Ӧλ�õ���λ�õ÷�Ϊ��
        }
        else if (type == 'b') //�ڷ�
        {
            chess_score -= sign * chesses[chess_index[move.eat_type]].value;//���ӵ÷�
            position_score -= sign * chesses[chess_index[move.eat_type]].position_score[board_row - 1 - move.to_row][board_col - 1 - move.to_col]; //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
        }
    }
    //����λ��ֵ
    int f_r = move.from_row;
    int f_c = move.from_col;
    int t_r = move.to_row;
    int t_c = move.to_col;//����һ�±��� �ñ�ʾ
    char type_pos = chess_type(board[move.from_row][move.from_col]); //�ж��ƶ�������������ɫ
    if (type_pos == 'r')                     //�췽
        position_score -= (sign * chesses[chess_index[board[f_r][f_c]]].position_score[t_r][t_c] - sign * chesses[chess_index[board[f_r][f_c]]].position_score[f_r][f_c]); //����λ��ֵ
    else if (type_pos == 'b') //�ڷ�
        position_score += (sign * chesses[chess_index[board[f_r][f_c]]].position_score[board_row - 1 - t_r][board_col - 1 - t_c] - sign * chesses[chess_index[board[f_r][f_c]]].position_score[board_row - 1 - f_r][board_col - 1 - f_c]); //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
#endif
    return;
}

//void ChessBoard::remove_piece_value(piece_move move)
//{
//    remove_piece(move);
//    value = getvalue();
//    return;
//}
