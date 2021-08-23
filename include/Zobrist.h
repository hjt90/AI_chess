#pragma once
#include "const.h"

typedef uint64_t U64;
typedef uint32_t U32;

/*********************************************************
* ������: init_zobrist
* ����:  ��ʼ��zobrist��ʹ�õ��ĸ����������map������
*********************************************************/
void init_zobrist();

/*********************************************************
* ������: get_zobrist_by_board
* ����:  �������̺͵�ǰ�����������zobristֵ
* board: ��ǰ����
* player: ��ǰ���巽
* ����ֵ: ���̵�zobristֵ
*********************************************************/
U64 get_zobrist_by_board(const char(&board)[board_row][board_col], const char player);

/*********************************************************
* ������: get_zobrist_by_move
* ����:  ����ԭzobristֵ,���̺��߷�,������һ�����zobristֵ
* board: ��ǰ����
* zobrist_old: ��֮ǰ��zobristֵ
* move: �ŷ�. ��1234,��ʾ1��2���ߵ�3��4��
* ����ֵ: ����move����һ���Ժ�������̵�zobristֵ
*********************************************************/
U64 get_zobrist_by_move(const char(&board)[board_row][board_col], const U64 zobrist_old, const std::string& move);

/*********************************************************
* ������: get_mirror_zobrist_by_board
* ����:  �������̺͵�ǰ�����������**�������**zobristֵ
* board: ��ǰ����
* player: ��ǰ���巽
* ����ֵ: **�������**���̵�zobristֵ
*********************************************************/
U64 get_mirror_zobrist_by_board(const char(&board)[board_row][board_col], const char player);

/*********************************************************
* ������: get_mirror_zobrist_by_move
* ����:  ����ԭ**�������**zobristֵ,���̺��߷�,������һ�����**�������**zobristֵ
* board: ��ǰ����
* mirr_zobrist_old: ��֮ǰ**�������**��zobristֵ
* move: �ŷ�. ��1234,��ʾ1��2���ߵ�3��4��
* ����ֵ: ����move����һ���Ժ��**�������**�����̵�zobristֵ
* ע��: board��move���������򼴿�,�����л��Զ�ת��.
*********************************************************/
U64 get_mirror_zobrist_by_move(const char(&board)[board_row][board_col], const U64 mirr_zobrist_old, const std::string& move);