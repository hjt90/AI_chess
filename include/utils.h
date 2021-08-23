#include <iostream>
#include <cstring>
#include <vector>
#include "const.h"
#pragma once
using namespace std;
int char2index(char ch);                                             //���ڽ��ַ�תΪ��������
void chess_clear(char (&board)[board_row][board_col], int r, int c); //���������

void chess_add(char (&board)[board_row][board_col], int r, int c, char value); //�������

//������ȡposition������ŵ��ַ�����who_turn����ĳ�˵Ļغϣ�board_status��������״̬��moves��ʾ��Ҫ�ߵĲ���
void read_position(char &who_turn, string &board_status, vector<string> &moves);

/************************************************
���������
char board[10][9]: char�����飬���ڴ洢����, '\0'��ʾ��
string board_status : ��ʾ����״̬���ַ��� ֻ��FEN�е�һ����
string moves : ��ʾ�˶��Ķ���
���ز�����
�Ѿ����¹������� board
*************************************************/
void string2board(char (&board)[board_row][board_col], string &board_status, const vector<string> &moves);


void board_print(char (&board)[board_row][board_col]); //�������
void board_print(char(&board)[board_row][board_col], ofstream& out);//�������

//�ж�������ͣ�����Ϊ'r'��ʾΪ�죬����Ϊ'b'��ʾΪ��
char chess_type(char chess);