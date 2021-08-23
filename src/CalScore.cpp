//该CPP计算当前局面得分
#include <iostream>
#include <vector>
#include "../include/score_table.h"
#include "../include/const.h"
#include "../include/utils.h"
#include "../include/GetPossibility.h"
using namespace std;

extern ofstream out;
#define print_rb_score 0 //打印评估函数信息cout
#define complex 1 //更加复杂的评估函数
#define complex1 0 //复杂的启发函数
#define simple1 1 //简单的启发函数
#define print_rb_score_elt 0 //打印启发函数
int chess_index[130]; //建立棋子类型和索引的映射，快速寻找
int position_score;
int chess_score;

// 帅(k)，士(a)，相(b)，马(n)，车(r)，炮(c)，兵(p)
void board_initial(char(&board)[board_row][board_col])//初始化棋盘,没有为'\0'
{
	for (int i = 0; i < board_row; i++)
		for (int j = 0; j < board_col; j++)
			board[i][j] = '\0';
	//初始黑方棋子索引
	chess_index['k'] = 0;
	chess_index['a'] = 1;
	chess_index['b'] = 2;
	chess_index['n'] = 3;
	chess_index['r'] = 4;
	chess_index['c'] = 5;
	chess_index['p'] = 6;

	//初始红方棋子索引
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
	cout << my_turn << " 这里更新了" << endl;
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
			char type = chess_type(board[r][c]); //判断棋子颜色
			if (type == 'r')                     //红方
			{
				position_score += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c]; //位置得分
				chess_score += 1.0 * sign * chesses[chess_index[board[r][c]]].value;                //棋子得分
			}
			else if (type == 'b') //黑方
			{
				position_score -= 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //位置得分，黑方需要做对称转换
				chess_score -= 1.0 * sign * chesses[chess_index[board[r][c]]].value;                                                //棋子得分
			}
		}
	return 0;
}

//计算当前局面得分
//board为棋盘，my_turn为我方棋子颜色'r'表示红色，'b'表示黑色
int cal_score(char(&board)[board_row][board_col], char my_turn)
{
	//扫一遍数组，完成位置评分和棋子存活评分
	int sign = 1;
	if (my_turn == 'r')
		sign = 1;
	else if (my_turn == 'b')
		sign = -1;
	double score = 0;
	double weight_flex = 0.2;//评估函数灵活性权重 
	double weight_att = 0.05;//评估函数进攻性权重
	double weight_dfn = 10;//评估函数防守性权重
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
	cout << "每个棋子的信息 : " << endl;
	for (int i = 0; i < infolist.size(); i++)
	{
		cout << "棋子 : " << board[infolist[i].row][infolist[i].col] << " 可走的空位 : " << infolist[i].movecount << " 攻击的棋子类型 : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << infolist[i].attack[j] << " ";
		cout << " 防御的棋子数 : " << infolist[i].protection << endl;
	}
#endif
	for (int r = 0; r < board_row; r++)
		for (int c = 0; c < board_col; c++)
		{
			char type = chess_type(board[r][c]); //判断棋子颜色
			if (type == 'r')                     //红方
			{
				score += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c]; //位置得分
				score += 1.0 * sign * chesses[chess_index[board[r][c]]].value;                //棋子得分
#if print_rb_score
				//cout << "棋子 : " << board[r][c] << " 位置得分 : " << (int)chesses[chess_index[board[r][c]]].position_score[r][c] << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value << endl;
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c];//位置得分
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//棋子得分
#endif
			}
			else if (type == 'b') //黑方
			{
				score -= 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //位置得分，黑方需要做对称转换
				score -= 1.0 * sign * chesses[chess_index[board[r][c]]].value;                                                //棋子得分
#if print_rb_score
				//cout << "棋子 : " << board[r][c] << " 位置得分 : " << (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value << endl;
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c];//位置得分，黑方需要做对称转换
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//棋子得分
#endif
			}
		}
#if complex 
	for (int i = 0; i < int(infolist.size()); i++)
	{
		//考虑棋子的灵活性，进攻性和防御性
		int r = infolist[i].row;
		int c = infolist[i].col;
#if print_rb_score
		cout << "棋子 : " << board[r][c] << " 位置得分 : " << (board[r][c] <= 'Z' ? (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] : (int)chesses[chess_index[board[r][c]]].position_score[r][c]) << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value;
		cout << "灵活性得分 : " << weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount;
		cout << " 进攻性得分 : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << weight_att * chesses[chess_index[infolist[i].attack[j]]].value << "+"; //进攻性得分
		cout << " 防守性得分 : " << weight_dfn * infolist[i].protection << endl;
#endif
		char type = chess_type(board[r][c]);//判断棋子颜色
		if (type == 'r')                     //红方
		{
			score += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
			{
				if (board[r][c] != 'k' && board[r][c] != 'K')
					score += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
				else
					score += 200; //进攻性得分
			}
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score += sign * weight_dfn * infolist[i].protection; //防守性得分

#if print_rb_score
			score_r_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_r_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_r_d += sign * weight_dfn * infolist[i].protection; //防守性得分
#endif
			}
		else if (type == 'b') //黑方
		{
			score -= sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
			{
				if (board[r][c] != 'k' && board[r][c] != 'K')
					score -= sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
				else
					score -= 300; //进攻性得分
			}
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score -= sign * weight_dfn * infolist[i].protection; //防守性得分

#if print_rb_score
			score_b_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_b_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_b_d += sign * weight_dfn * infolist[i].protection; //防守性得分
#endif
		}
	}
#endif




#if print_rb_score
	cout.setf(ios::fixed, ios::floatfield);
	cout << "红方棋盘和位置得分 : " << score_r;
	cout << " 红方灵活性得分 : " << score_r_f;
	cout << " 红方进攻性得分 : " << score_r_a;
	cout << " 红方防守性得分 : " << score_r_d << endl;
	cout << "黑方棋盘和位置得分 : " << score_b;
	cout << " 黑方灵活性得分 : " << score_b_f;
	cout << " 黑方进攻性得分 : " << score_b_a;
	cout << " 黑方防守性得分 : " << score_b_d << endl;
	cout << "总得分 : " << (int)score << endl;
#endif
	return score * 10;
		}


int cal_enlighten(char(&board)[board_row][board_col], char my_turn)
{
	//扫一遍数组，完成位置评分和棋子存活评分
	int sign = 1;
	if (my_turn == 'r')
		sign = 1;
	else if (my_turn == 'b')
		sign = -1;
	double score = 0;
	double weight_flex = 0;//评估函数灵活性权重 
	double weight_att = 0;//评估函数进攻性权重
	double weight_dfn = 0;//评估函数防守性权重
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
	cout << "每个棋子的信息 : " << endl;
	for (int i = 0; i < infolist.size(); i++)
	{
		cout << "棋子 : " << board[infolist[i].row][infolist[i].col] << " 可走的空位 : " << infolist[i].movecount << " 攻击的棋子类型 : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << infolist[i].attack[j] << " ";
		cout << " 防御的棋子数 : " << infolist[i].protection << endl;
	}
#endif
#if simple1
	for (int r = 0; r < board_row; r++)
		for (int c = 0; c < board_col; c++)
		{
			char type = chess_type(board[r][c]); //判断棋子颜色
			if (type == 'r')                     //红方
			{
				score += 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].position_score[r][c]; //位置得分
				score += 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].value;                //棋子得分
#if print_rb_score
				//cout << "棋子 : " << board[r][c] << " 位置得分 : " << (int)chesses[chess_index[board[r][c]]].position_score[r][c] << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value << endl;
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[r][c];//位置得分
				score_r += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//棋子得分
#endif
			}
			else if (type == 'b') //黑方
			{
				score -= 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c]; //位置得分，黑方需要做对称转换
				score -= 1.0 * sign * weight_pos * chesses[chess_index[board[r][c]]].value;                                                //棋子得分
#if print_rb_score
				//cout << "棋子 : " << board[r][c] << " 位置得分 : " << (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value << endl;
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c];//位置得分，黑方需要做对称转换
				score_b += 1.0 * sign * chesses[chess_index[board[r][c]]].value;//棋子得分
#endif
			}
		}
#endif
#if complex1
	for (int i = 0; i < int(infolist.size()); i++)
	{
		//考虑棋子的灵活性，进攻性和防御性
		int r = infolist[i].row;
		int c = infolist[i].col;
#if print_rb_score
		cout << "棋子 : " << board[r][c] << " 位置得分 : " << (board[r][c] <= 'Z' ? (int)chesses[chess_index[board[r][c]]].position_score[board_row - 1 - r][board_col - 1 - c] : (int)chesses[chess_index[board[r][c]]].position_score[r][c]) << " 棋子得分 : " << chesses[chess_index[board[r][c]]].value;
		cout << "灵活性得分 : " << weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount;
		cout << " 进攻性得分 : ";
		for (int j = 0; j < infolist[i].attack.size(); j++)
			cout << weight_att * chesses[chess_index[infolist[i].attack[j]]].value << "+"; //进攻性得分
		cout << " 防守性得分 : " << weight_dfn * infolist[i].protection << endl;
#endif
		char type = chess_type(board[r][c]);//判断棋子颜色
		if (type == 'r')                     //红方
		{
			score += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score += sign * weight_dfn * infolist[i].protection; //防守性得分

#if print_rb_score
			score_r_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_r_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_r_d += sign * weight_dfn * infolist[i].protection; //防守性得分
#endif
		}
		else if (type == 'b') //黑方
		{
			score -= sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score -= sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score -= sign * weight_dfn * infolist[i].protection; //防守性得分

#if print_rb_score
			score_b_f += sign * weight_flex * chesses[chess_index[board[r][c]]].flex * infolist[i].movecount; //灵活性得分
			for (int j = 0; j < infolist[i].attack.size(); j++)
				score_b_a += sign * weight_att * chesses[chess_index[infolist[i].attack[j]]].value; //进攻性得分
			if (board[r][c] != 'k' && board[r][c] != 'K')
				score_b_d += sign * weight_dfn * infolist[i].protection; //防守性得分
#endif
		}
	}
#endif




#if print_rb_score
	cout.setf(ios::fixed, ios::floatfield);
	cout << "红方棋盘和位置得分 : " << score_r;
	cout << " 红方灵活性得分 : " << score_r_f;
	cout << " 红方进攻性得分 : " << score_r_a;
	cout << " 红方防守性得分 : " << score_r_d << endl;
	cout << "黑方棋盘和位置得分 : " << score_b;
	cout << " 黑方灵活性得分 : " << score_b_f;
	cout << " 黑方进攻性得分 : " << score_b_a;
	cout << " 黑方防守性得分 : " << score_b_d << endl;
	cout << "总得分 : " << (int)score << endl;
#endif
	return score * 100;
			}

//该函数判断是否被将军
//my_turn表示是哪一方，
//每个棋子的信息
//马的走法，右上上，右上下，右下上，右下下，左下下，左下上，左上下，左上上
//int n_step_dr[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
//int n_step_dc[8] = { 1,2,2,1,-1,-2,-2,-1 };
////士的走法，
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
//    //在红色方找帅
//    for (int i = 0; i <= 2; i++)
//    {
//        for (int j = 3; j <= 5; j++)
//        {
//            if (board[i][j] == 'K')//找到了
//            {
//            }
//        }
//    }
//    //在黑色方找帅
//    for (int i = 7; i <= 9; i++)
//    {
//        for (int j = 3; j <= 5; j++)//找到了
//        {
//            if (board[i][j] == 'k')
//            {
//
//            }
//        }
//    }
//    return false;
//}






