#pragma once
#include<vector>
#include<string>
#include"const.h"
using namespace std;
/*
//���ܵĽ�Ľṹ��
struct pnode
{
	//��ʼ����
	int x1;
	int y1;
	//�յ�����
	int x2;
	int y2;
	//�Ƿ����
	bool eat;
};
*/

struct chess_info
{
	int row;
	int col;
	vector<char> attack;
	int protection;
	int movecount;//������ƶ����հ�
};

//����(������Ϊ����ʵ�ַ����ٶ���һ�Σ��ϲ�ʱ����ȥ��)
//const int board_col = 9; //���̵��� 
//const int board_row = 10; //���̵���

char whichside(char c);//�����ĺ���
vector<string> getnodes(char(&board)[board_row][board_col], char side);//һ�����������̣��ڶ���������˭�ߣ�����fen����b�Ǻ�r�Ǻ죩
//���ص���һ����string��vector��stringȡǰ��λ���ֱ�����ʼ�У���ʼ�У��յ��У��յ���
char judge(char(&board)[board_row][board_col]);//�ж���Ӯ����Ӯ����r����Ӯ����b�����෵��z
bool check_basicborder(int i, int j, int i1, int j1, int row0, int col0, int row1, int col1);//�������ĺ����жϱ߽�
bool is_correct_step(string step, char(&board)[board_row][board_col]);//�ж��Ƿ���ȷ�߷�
vector<chess_info> get_chess_info(char(&board)[board_row][board_col]);//һ������������

