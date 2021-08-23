#include <iostream>
#include <fstream>
#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
#include "../include/Search.h"
#include "../include/Zobrist.h"
#include "../include/OpeningBook.h"
using namespace std;

bool debug_fileout = true;		//�򿪺���debug�����д���ļ�
bool debug_stdout = false;		//
ofstream out;

int main()
{
	if (debug_fileout)
		out.open(R"(./test.txt)", ios::out);

	string sel;
	char board[board_row][board_col] = { 0 };
	board_initial(board);
	char who_turn = '\0';
	string board_status;
	vector<string> moves; //�ַ��������������뵱ǰ���̻����߹��Ĳ�
	moves.clear();
	Chess_AI chess_ai;
	chess_ai.init_max_t(1000);		//��ʼ�����������ʱ�䣬��λΪ����
	init_zobrist();
	init_opening_book();

	//��ʼ������
	board_status = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR";
	string2board(board, board_status, moves);
	chess_ai.init_Turn((gameTurn)'r');
	chess_ai.oppen_Go(board);

	while (1)
	{
		cin >> sel;
		if (debug_fileout) {
			out << "��������" << sel << endl;
		}
		if (sel == "ucci")
		{
			cout << "ucciok" << endl;
		}
		else if (sel == "isready")
		{
			cout << "readyok" << endl;
		}
		else if (sel == "position") //����ֻ���˶����ַ�����ת�����̵Ĺ���
		{
			read_position(who_turn, board_status, moves);
			chess_ai.init_Turn((gameTurn)who_turn);
			string2board(board, board_status, moves);
			chess_ai.oppen_Go(board);

			if (debug_fileout) {
				out << "position����Ϊ" << endl;
				board_print(board, out); //�������
			}
			if (debug_stdout) {
				cout << "position����Ϊ" << endl;
				board_print(board); //�������
			//cerr << "��ǰ���̵÷�Ϊ : " << chess_ai.board.value.black_values << endl;
			//pass
			}
		}
		else if (sel == "go")
		{
			//��ȡgo����������

			//position startpos moves c0e2 b7f7 b0c2 b9c7 a0b0 c6c5
			chess_ai.Search(10000, INT_MIN, INT_MAX);
			string move = move2uccistring(chess_ai.best_decision);

			if (debug_fileout) {
				out << "go����Ϊ" << endl;
				board_print(board, out);
				out << "���浱ǰzobristֵΪ0x" << hex << chess_ai.Zobrist_val << endl;
				out << "���ص�bestmoveΪ " << move << endl;
				out << dec;
				//out << "�ҷ�ִ" << (who_turn == 'b' ? "��" : "��") << " ���̵÷�Ϊ" << cal_score(board, who_turn) << endl;
			}

			cout << "bestmove " << move << endl;
		}
		else if (sel == "quit")
		{
			cout << "bye" << endl;
			break;
		}
		else
		{
			;
			//pass
		}
	}
	return 0;
}
