#include <iostream>
#include <fstream>
#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
#include "../include/Search.h"
#include "../include/Zobrist.h"
#include "../include/OpeningBook.h"
using namespace std;

bool debug_fileout = true;		//打开后开启debug，结果写入文件
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
	vector<string> moves; //字符串描述的棋盘离当前棋盘还需走过的步
	moves.clear();
	Chess_AI chess_ai;
	chess_ai.init_max_t(1000);		//初始化搜索的最大时间，单位为毫秒
	init_zobrist();
	init_opening_book();

	//初始化棋盘
	board_status = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR";
	string2board(board, board_status, moves);
	chess_ai.init_Turn((gameTurn)'r');
	chess_ai.oppen_Go(board);

	while (1)
	{
		cin >> sel;
		if (debug_fileout) {
			out << "引擎输入" << sel << endl;
		}
		if (sel == "ucci")
		{
			cout << "ucciok" << endl;
		}
		else if (sel == "isready")
		{
			cout << "readyok" << endl;
		}
		else if (sel == "position") //这里只做了读入字符串和转换棋盘的工作
		{
			read_position(who_turn, board_status, moves);
			chess_ai.init_Turn((gameTurn)who_turn);
			string2board(board, board_status, moves);
			chess_ai.oppen_Go(board);

			if (debug_fileout) {
				out << "position棋盘为" << endl;
				board_print(board, out); //输出棋盘
			}
			if (debug_stdout) {
				cout << "position棋盘为" << endl;
				board_print(board); //输出棋盘
			//cerr << "当前棋盘得分为 : " << chess_ai.board.value.black_values << endl;
			//pass
			}
		}
		else if (sel == "go")
		{
			//读取go后续的限制

			//position startpos moves c0e2 b7f7 b0c2 b9c7 a0b0 c6c5
			chess_ai.Search(10000, INT_MIN, INT_MAX);
			string move = move2uccistring(chess_ai.best_decision);

			if (debug_fileout) {
				out << "go棋盘为" << endl;
				board_print(board, out);
				out << "局面当前zobrist值为0x" << hex << chess_ai.Zobrist_val << endl;
				out << "返回的bestmove为 " << move << endl;
				out << dec;
				//out << "我方执" << (who_turn == 'b' ? "黑" : "红") << " 棋盘得分为" << cal_score(board, who_turn) << endl;
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
