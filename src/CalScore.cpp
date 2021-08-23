//��CPP���㵱ǰ����÷�
#include <iostream>
#include <vector>
#include "../include/score_table.h"
#include "../include/const.h"
#include "../include/utils.h"
#include "../include/GetPossibility.h"
using namespace std;

extern ofstream out;
#define print_rb_score 0 //��ӡ����������Ϣcout
#define complex 1 //���Ӹ��ӵ���������
#define complex1 0 //���ӵ���������
#define simple1 1 //�򵥵���������
#define print_rb_score_elt 0 //��ӡ��������
int chess_index[130]; //�����������ͺ�������ӳ�䣬����Ѱ��
int position_score;
int chess_score;

// ˧(k)��ʿ(a)����(b)����(n)����(r)����(c)����(p)
void board_initial(char(&board)[board_row][board_col])//��ʼ������,û��Ϊ'\0'
{
	for (int i = 0; i < board_row; i++)
		for (int j = 0; j < board_col; j++)
			board[i][j] = '\0';
	//��ʼ�ڷ���������
	chess_index['k'] = 0;
	chess_index['a'] = 1;
	chess_index['b'] = 2;
	chess_index['n'] = 3;
	chess_index['r'] = 4;
	chess_index['c'] = 5;
	chess_index['p'] = 6;

	//��ʼ�췽��������
	chess_index['K'] = 0;
	chess_index['A'] = 1;
	chess_index['B'] = 2;
	chess_index['N'] = 3;
	chess_index['R'] = 4;
	chess_index['C'] = 5;
	chess_index['P'] = 6;
}


int init_score(char(&board)[board_row][board_col], char my_turn)
{
	cout << my_turn << " ���������" << endl;
	position_score = 0;
	chess_score = 0;
	int sign = 1;
	if (my_turn == 'r')
		sign = 1;
	else if (my_turn == 'b')
		sign = -1;
	for (int r = 0; r < board_row; r++)
		for (int c = 0; c < board_col; c++)
		{
			char type = chess_type(board[r][c]); //�ж�������ɫ
			if (type == 'r')                     //�췽
			{
				position_score += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c]; //λ�õ÷�
				chess_score += 1.0 * sign * chesses[chess_index[board[r][c]]].value;                //���ӵ÷�
			}
			else if (type == 'b') //�ڷ�
			{
				position_score -= 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
				chess_score -= 1.0 * sign * chesses[chess_index[board[r][c]]].value;                                                //���ӵ÷�
			}
		}
	return 0;
}

//���㵱ǰ����÷�
//boardΪ���̣�my_turnΪ�ҷ�������ɫ'r'��ʾ��ɫ��'b'��ʾ��ɫ
int cal_score(char(&board)[board_row][board_col], char my_turn)
{
	//ɨһ�����飬���λ�����ֺ����Ӵ������
	int sign = 1;
	if (my_turn == 'r')
		sign = 1;
	else if (my_turn == 'b')
		sign = -1;
	double score = 0;
	double weight_flex = 0.2;//�������������Ȩ�� 
	double weight_att = 0.05;//��������������Ȩ��
	double weight_dfn = 10;//��������������Ȩ��
#if print_rb_score
	double score_r = 0;
	double score_r_f = 0;
	double score_r_a = 0;
	double score_r_d = 0;
	double score_b = 0;
	double score_b_f = 0;
	double score_b_a = 0;
	double score_b_d = 0;
#endif
#if complex 
	vector <chess_info> infolist;
	infolist = get_chess_info(board);
#endif
#if print_rb_score
	cout << "ÿ�����ӵ���Ϣ : " << endl;
	for (int i = 0; i < infolist.size(); i++)
	{
		cout << "���� : " << board[infolist[i].row][infolist[i].col] << " ���ߵĿ�λ : " << infolist[i].movecount << " �������������� : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << infolist[i].attack[j] << " ";
		cout << " ������������ : " << infolist[i].protection << endl;
	}
#endif
	for (int r = 0; r < board_row; r++)
		for (int c = 0; c < board_col; c++)
		{
			char type = chess_type(board[r][c]); //�ж�������ɫ
			if (type == 'r')                     //�췽
			{
				score += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c]; //λ�õ÷�
				score += 1.0 * sign * chesses[chess_index[board[r][c]]].value;                //���ӵ÷�
#if print_rb_score
				//cout << "���� : " << board[r][c] << " λ�õ÷� : " << (int)chesses[chess_index[board[r][c]]].position_score[r][c] << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value << endl;
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c];//λ�õ÷�
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//���ӵ÷�
#endif
			}
			else if (type == 'b') //�ڷ�
			{
				score -= 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
				score -= 1.0 * sign * chesses[chess_index[board[r][c]]].value;                                                //���ӵ÷�
#if print_rb_score
				//cout << "���� : " << board[r][c] << " λ�õ÷� : " << (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value << endl;
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c];//λ�õ÷֣��ڷ���Ҫ���Գ�ת��
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//���ӵ÷�
#endif
			}
		}
#if complex 
	for (int i = 0; i < int(infolist.size()); i++)
	{
		//�������ӵ�����ԣ������Ժͷ�����
		int r = infolist[i].row;
		int c = infolist[i].col;
#if print_rb_score
		cout << "���� : " << board[r][c] << " λ�õ÷� : " << (board[r][c] <= 'Z' ? (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] : (int)chesses[chess_index[board[r][c]]].position_score[r][c]) << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value;
		cout << "����Ե÷� : " << weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount;
		cout << " �����Ե÷� : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << weight_att * chesses[chess_index[infolist[i].attack[j]]].value << "+"; //�����Ե÷�
		cout << " �����Ե÷� : " << weight_dfn * infolist[i].protection << endl;
#endif
		char type = chess_type(board[r][c]);//�ж�������ɫ
		if (type == 'r')                     //�췽
		{
			score += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
			{
				if (board[r][c] != 'k' && board[r][c] != 'K')
					score += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
				else
					score += 200; //�����Ե÷�
			}
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score += sign * weight_dfn * infolist[i].protection; //�����Ե÷�

#if print_rb_score
			score_r_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_r_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_r_d += sign * weight_dfn * infolist[i].protection; //�����Ե÷�
#endif
			}
		else if (type == 'b') //�ڷ�
		{
			score -= sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
			{
				if (board[r][c] != 'k' && board[r][c] != 'K')
					score -= sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
				else
					score -= 300; //�����Ե÷�
			}
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score -= sign * weight_dfn * infolist[i].protection; //�����Ե÷�

#if print_rb_score
			score_b_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_b_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_b_d += sign * weight_dfn * infolist[i].protection; //�����Ե÷�
#endif
		}
	}
#endif




#if print_rb_score
	cout.setf(ios::fixed, ios::floatfield);
	cout << "�췽���̺�λ�õ÷� : " << score_r;
	cout << " �췽����Ե÷� : " << score_r_f;
	cout << " �췽�����Ե÷� : " << score_r_a;
	cout << " �췽�����Ե÷� : " << score_r_d << endl;
	cout << "�ڷ����̺�λ�õ÷� : " << score_b;
	cout << " �ڷ�����Ե÷� : " << score_b_f;
	cout << " �ڷ������Ե÷� : " << score_b_a;
	cout << " �ڷ������Ե÷� : " << score_b_d << endl;
	cout << "�ܵ÷� : " << (int)score << endl;
#endif
	return score * 10;
		}


int cal_enlighten(char(&board)[board_row][board_col], char my_turn)
{
	//ɨһ�����飬���λ�����ֺ����Ӵ������
	int sign = 1;
	if (my_turn == 'r')
		sign = 1;
	else if (my_turn == 'b')
		sign = -1;
	double score = 0;
	double weight_flex = 0;//�������������Ȩ�� 
	double weight_att = 0;//��������������Ȩ��
	double weight_dfn = 0;//��������������Ȩ��
	double weight_pos = 1;
#if print_rb_score
	double score_r = 0;
	double score_r_f = 0;
	double score_r_a = 0;
	double score_r_d = 0;
	double score_b = 0;
	double score_b_f = 0;
	double score_b_a = 0;
	double score_b_d = 0;
#endif
#if complex1
	vector <chess_info> infolist;
	infolist = get_chess_info(board);
#endif
#if print_rb_score
	cout << "ÿ�����ӵ���Ϣ : " << endl;
	for (int i = 0; i < infolist.size(); i++)
	{
		cout << "���� : " << board[infolist[i].row][infolist[i].col] << " ���ߵĿ�λ : " << infolist[i].movecount << " �������������� : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << infolist[i].attack[j] << " ";
		cout << " ������������ : " << infolist[i].protection << endl;
	}
#endif
#if simple1
	for (int r = 0; r < board_row; r++)
		for (int c = 0; c < board_col; c++)
		{
			char type = chess_type(board[r][c]); //�ж�������ɫ
			if (type == 'r')                     //�췽
			{
				score += 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].position_score[r][c]; //λ�õ÷�
				score += 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].value;                //���ӵ÷�
#if print_rb_score
				//cout << "���� : " << board[r][c] << " λ�õ÷� : " << (int)chesses[chess_index[board[r][c]]].position_score[r][c] << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value << endl;
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c];//λ�õ÷�
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//���ӵ÷�
#endif
			}
			else if (type == 'b') //�ڷ�
			{
				score -= 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //λ�õ÷֣��ڷ���Ҫ���Գ�ת��
				score -= 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].value;                                                //���ӵ÷�
#if print_rb_score
				//cout << "���� : " << board[r][c] << " λ�õ÷� : " << (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value << endl;
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c];//λ�õ÷֣��ڷ���Ҫ���Գ�ת��
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//���ӵ÷�
#endif
			}
		}
#endif
#if complex1
	for (int i = 0; i < int(infolist.size()); i++)
	{
		//�������ӵ�����ԣ������Ժͷ�����
		int r = infolist[i].row;
		int c = infolist[i].col;
#if print_rb_score
		cout << "���� : " << board[r][c] << " λ�õ÷� : " << (board[r][c] <= 'Z' ? (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] : (int)chesses[chess_index[board[r][c]]].position_score[r][c]) << " ���ӵ÷� : " << chesses[chess_index[board[r][c]]].value;
		cout << "����Ե÷� : " << weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount;
		cout << " �����Ե÷� : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << weight_att * chesses[chess_index[infolist[i].attack[j]]].value << "+"; //�����Ե÷�
		cout << " �����Ե÷� : " << weight_dfn * infolist[i].protection << endl;
#endif
		char type = chess_type(board[r][c]);//�ж�������ɫ
		if (type == 'r')                     //�췽
		{
			score += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score += sign * weight_dfn * infolist[i].protection; //�����Ե÷�

#if print_rb_score
			score_r_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_r_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_r_d += sign * weight_dfn * infolist[i].protection; //�����Ե÷�
#endif
		}
		else if (type == 'b') //�ڷ�
		{
			score -= sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score -= sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score -= sign * weight_dfn * infolist[i].protection; //�����Ե÷�

#if print_rb_score
			score_b_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //����Ե÷�
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_b_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //�����Ե÷�
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_b_d += sign * weight_dfn * infolist[i].protection; //�����Ե÷�
#endif
		}
	}
#endif




#if print_rb_score
	cout.setf(ios::fixed, ios::floatfield);
	cout << "�췽���̺�λ�õ÷� : " << score_r;
	cout << " �췽����Ե÷� : " << score_r_f;
	cout << " �췽�����Ե÷� : " << score_r_a;
	cout << " �췽�����Ե÷� : " << score_r_d << endl;
	cout << "�ڷ����̺�λ�õ÷� : " << score_b;
	cout << " �ڷ�����Ե÷� : " << score_b_f;
	cout << " �ڷ������Ե÷� : " << score_b_a;
	cout << " �ڷ������Ե÷� : " << score_b_d << endl;
	cout << "�ܵ÷� : " << (int)score << endl;
#endif
	return score * 100;
			}

//�ú����ж��Ƿ񱻽���
//my_turn��ʾ����һ����
//ÿ�����ӵ���Ϣ
//����߷��������ϣ������£������ϣ������£������£������ϣ������£�������
//int n_step_dr[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
//int n_step_dc[8] = { 1,2,2,1,-1,-2,-2,-1 };
////ʿ���߷���
//int n_step_dr[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
//int n_step_dc[8] = { 1,2,2,1,-1,-2,-2,-1 };
//
//
//bool is_kill(char my_turn, char(&board)[board_row][board_col])
//{
//    int r, c;
//    char king = 'k';
//    if (my_turn == 'r')
//        king = 'K';
//    else
//        king = 'k';
//    //�ں�ɫ����˧
//    for (int i = 0; i <= 2; i++)
//    {
//        for (int j = 3; j <= 5; j++)
//        {
//            if (board[i][j] == 'K')//�ҵ���
//            {
//            }
//        }
//    }
//    //�ں�ɫ����˧
//    for (int i = 7; i <= 9; i++)
//    {
//        for (int j = 3; j <= 5; j++)//�ҵ���
//        {
//            if (board[i][j] == 'k')
//            {
//
//            }
//        }
//    }
//    return false;
//}






