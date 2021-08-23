#include <fstream>
#include "../include/Search.h"
#include "../include/Chess_board.h"
#include "../include/OpeningBook.h"
using namespace std;
extern bool debug_fileout;
extern ofstream out;

inline gameTurn Change_Turn(gameTurn turn)
{
	if (turn == T_BLACK)
		return T_RED;

	return T_BLACK;
}

piece_move Chess_AI::string2move(const string& str)
{
	piece_move res;
	res.from_row = str[0] - '0';
	res.from_col = str[1] - '0';
	res.to_row = str[2] - '0';
	res.to_col = str[3] - '0';
	res.eat = board.board[res.to_row][res.to_col] != P_NONE;
	res.eat_type = (Pieces_type)board.board[res.to_row][res.to_col];
	return res;
}

string move2string(piece_move mv)
{
	char ret[5] = "0000";
	ret[0] += mv.from_row;
	ret[1] += mv.from_col;
	ret[2] += mv.to_row;
	ret[3] += mv.to_col;
	return string(ret);
}

string move2uccistring(piece_move mv)
{
	char ret[5] = "a0a0";
	ret[0] += mv.from_col;
	ret[1] += mv.from_row;
	ret[2] += mv.to_col;
	ret[3] += mv.to_row;
	return string(ret);
}

Chess_AI::Chess_AI()
{
}

Chess_AI::Chess_AI(gameTurn myturn)
{
	turn = myturn;
	board.myTurn = myturn;
}

void Chess_AI::init_Turn(gameTurn myturn)
{
	turn = myturn;
	board.myTurn = myturn;
}

void Chess_AI::init_max_t(const long true_max_t) //��ʼ�����ʱ��
{
	this->max_t = (clock_t)(0.9 * true_max_t);
}

void Chess_AI::oppen_Go(chess_board new_board)
{
	memcpy(board.board, new_board, sizeof(chess_board));

	//board.value = cal_score(board.board, turn);
	Zobrist_val = get_zobrist_by_board(board.board, turn);
	Zobrist_mirror_val = get_mirror_zobrist_by_board(board.board, turn);
	//history_moves = move;
}

//�����û���,��������򷵻ؼ�ֵ���Ͳ�Ϊitem��ֵ
//���򷵻���
const Zobrist_Type Chess_AI::is_in_ZobristMap(Zobrist_Item& item, const U64 zobrist_value, const U64 zobrist_mirr_value)
{
	if (Zobrist_map.find(zobrist_value) != Zobrist_map.end())
	{
		item = Zobrist_map[zobrist_value];
		return Zobrist_Type::zobrist;
	}
	else if (Zobrist_map.find(zobrist_mirr_value) != Zobrist_map.end())
	{
		item = Zobrist_map[zobrist_mirr_value];
		return Zobrist_Type::zobrist_mirr;
	}
	return Zobrist_Type::none;
}

position_values Chess_AI::get_board_score(const U64 Zobrist_val, const U64 Zobrist_mirror_val)
{
	bool use_zobrist = true;
	//���ؾ���ֵ
	Zobrist_Item item;
	Zobrist_Type type;
	type = is_in_ZobristMap(item, Zobrist_val, Zobrist_mirror_val);
	if (type == Zobrist_Type::zobrist)
	{
		if (item.score == Undefined)
		{
#if is_dynamic
			item.score = chess_score + position_score;
#else
			item.score = cal_score(board.board, turn);
#endif
			Zobrist_map[Zobrist_val].score = item.score;

			use_zobrist = false;
		}
	}
	else if (type == Zobrist_Type::zobrist_mirr)
	{
		if (item.score == Undefined)
		{
#if is_dynamic
			item.score = chess_score + position_score;
#else
			item.score = cal_score(board.board, turn);
#endif
			Zobrist_map[Zobrist_mirror_val].score = item.score;

			use_zobrist = false;
		}
	}
	else
	{
#if is_dynamic
		item.score = chess_score + position_score;
#else
		item.score = cal_score(board.board, turn);
#endif
		Zobrist_map[Zobrist_val] = item;


		use_zobrist = false;
	}

	if (debug_fileout)
	{
		if (use_zobrist)
			use_zobrist_score_count++;
		else
			unuse_score_count++;
	}

	return item.score;
}

static_eval_values Chess_AI::get_board_static_value(const U64 Zobrist_val, const U64 Zobrist_mirror_val)
{
	bool use_zobrist = true;
	//���ؾ���ֵ
	Zobrist_Item item;
	Zobrist_Type type;
	type = is_in_ZobristMap(item, Zobrist_val, Zobrist_mirror_val);
	if (type == Zobrist_Type::zobrist)
	{
		if (item.static_value == Undefined)
		{
#if is_dynamic
			item.static_value = chess_score + position_score;
#else
			item.static_value = cal_enlighten(board.board, turn);
#endif
			Zobrist_map[Zobrist_val].static_value = item.static_value;

			use_zobrist = false;
		}
	}
	else if (type == Zobrist_Type::zobrist_mirr)
	{
		if (item.static_value == Undefined)
		{
#if is_dynamic
			item.static_value = chess_score + position_score;
#else
			item.static_value = cal_enlighten(board.board, turn);
#endif
			Zobrist_map[Zobrist_mirror_val].static_value = item.static_value;

			use_zobrist = false;
		}
	}
	else
	{
#if is_dynamic
		item.static_value = chess_score + position_score;
#else
		item.static_value = cal_enlighten(board.board, turn);
#endif
		Zobrist_map[Zobrist_val] = item;

		use_zobrist = false;
	}

	if (debug_fileout)
	{
		if (use_zobrist)
			use_zobrist_staticcount++;
		else
			unuse_static_count++;
	}

	return item.static_value;
}

const int Chess_AI::is_in_killer_table(const std::string& move, const int depth)const
{
	for (int i = 0; i < killer_moves_table[depth].size(); i++)
		if (move == killer_moves_table[depth][i].move)
			return i;
	return -1;
}

void Chess_AI::update_killer_table(const std::string& move, const int depth)
{
	int index = is_in_killer_table(move, depth);
	if (index != -1) {
		killer_moves_table[depth][index].count++;
		while (index > 0 && killer_moves_table[depth][index].count > killer_moves_table[depth][index - 1].count) {
			swap(killer_moves_table[depth][index], killer_moves_table[depth][index - 1]);
			index--;
		}
		return;
	}
	killer_moves_table[depth].push_back({ move,1 });
}

//const bool Chess_AI::judge_long_move(const std::string& move)
//{
//	int len = history_moves.size();
//
//	if (len <= 11)
//		return false;
//
//	if (history_moves[len - 2] == move && history_moves[len - 6] == move && history_moves[len - 10] == move)
//		return true;
//
//	return false;
//}

int Chess_AI::inner_Search(int depth, int alpha, int beta)
{
	if (depth < 0)
		return INT_MIN;
	clock_t delta_time = (clock() - this->start_t) * 1000 / CLOCKS_PER_SEC;
	if (judge(board.board) != GameResult::R_DRAW || this->timeout || delta_time > this->max_t)
	{
		if (delta_time > this->max_t)
			this->timeout = true;

		return get_board_score(Zobrist_val, Zobrist_mirror_val);
	}

	gameTurn this_turn = turn;
	if (depth % 2)
		this_turn = Change_Turn(turn); //���ָ�˭��

	U64 this_Zobrist = Zobrist_val;
	U64 this_mirror_Zobrist = Zobrist_mirror_val;
	vector<pair<piece_move, int>> seek_result;
	int ret;

	if (depth == 0)
	{ //�ִ������
		into_depth_count++;


		int max_score;
		seek_result = seekPoints(this_turn, depth);
		board.move_piece(seek_result[0].first);
		max_score = get_board_score(Zobrist_val, Zobrist_mirror_val);
		board.remove_piece(seek_result[0].first);
		if (this_max_value < max_score)
		{
			this_best_process = AI_Search_process;
			this_max_value = max_score;
		}
		return max_score;
	}
	else if (depth % 2 == 0)
	{ //max��,�ҷ�����
		seek_result = seekPoints(this_turn, depth);
		int len = seek_result.size();
		int i;
		for (i = 0; i < len; ++i)
		{
			//if (depth == 4)
			//{
			//	out << "���Խ��п��Ųü�" << endl;
			//}
			//if (pre_best_process.empty()) {
			//	ret = inner_Search(depth - 1, beta - 1, beta);
			//	if (ret >= beta)
			//	{
			//		if (debug_fileout)
			//			out << "������Ч" << endl;
			//		return beta;
			//	}
			//}

			Zobrist_val = get_zobrist_by_move(board.board, Zobrist_val, move2string(seek_result[i].first));
			Zobrist_mirror_val = get_mirror_zobrist_by_move(board.board, Zobrist_mirror_val, move2string(seek_result[i].first));
			board.move_piece(seek_result[i].first);
			AI_Search_process.push_back(seek_result[i].first);

			ret = inner_Search(depth - 1, alpha, beta);

			AI_Search_process.pop_back();
			board.remove_piece(seek_result[i].first);
			Zobrist_val = this_Zobrist;
			Zobrist_mirror_val = this_mirror_Zobrist;

			if (ret > alpha)
			{
				alpha = ret;
				//if (depth == this_depth && !judge_long_move(move2uccistring(seek_result[i].first))) //�������ž���
				if (depth == this_depth) //�������ž���
				{
					best_decision = seek_result[i].first;
					best_score = ret;
				}
			}
			if (beta <= alpha) {
				update_killer_table(move2string(seek_result[i].first), depth);
				/*if (debug_fileout)
					out << "�ɹ���֦, ����Ϊ" << depth << ", lenΪ" << len << ", ��ǰiΪ " << i << endl;*/
				break;
			}
		}
		/*if (debug_fileout && i == len)
			out << "�ŷ�����" << len << "��, ����Ϊ" << depth << ",һ����֧��û��" << endl;*/
		return alpha;
	}
	else
	{ //min��,�з�����
		seek_result = seekPoints(this_turn, depth);
		int len = seek_result.size();
		int i;
		for (i = 0; i < len; ++i)
		{
			Zobrist_val = get_zobrist_by_move(board.board, Zobrist_val, move2string(seek_result[i].first));
			Zobrist_mirror_val = get_mirror_zobrist_by_move(board.board, Zobrist_mirror_val, move2string(seek_result[i].first));
			board.move_piece(seek_result[i].first);
			AI_Search_process.push_back(seek_result[i].first);

			ret = inner_Search(depth - 1, alpha, beta);

			AI_Search_process.pop_back();
			board.remove_piece(seek_result[i].first);
			Zobrist_val = this_Zobrist;
			Zobrist_mirror_val = this_mirror_Zobrist;

			if (ret < beta)
				beta = ret;
			if (beta <= alpha) {
				update_killer_table(move2string(seek_result[i].first), depth);
				/*if (debug_fileout)
					out << "�ɹ���֦, ����Ϊ" << depth << ", lenΪ" << len << ", ��ǰiΪ " << i << endl;*/
				break;
			}
		}
		/*if (debug_fileout && i == len)
			out << "�ŷ�����" << len << "��, ����Ϊ" << depth << ",һ����֧��û��" << endl;*/
		return beta;
	}
}

/* *
 * Ѱ����һ��������λ��
 * ����һ��λ�����飻�������ȼ�����
 *
 * ���ȼ���
 *   ��̰���㷨����
 * */
vector<pair<piece_move, int>> Chess_AI::seekPoints(gameTurn analy_turn, const int depth)
{
	vector<piece_move> res;
	vector<pair<piece_move, int>> sorted_pos;
	vector<string> next_pos = search_openging_book(Zobrist_val, Zobrist_mirror_val, board.board);
	if (next_pos.empty())
		next_pos = getnodes(board.board, analy_turn);
	position_values this_val = board.value;
	piece_move move;
	U64 zobrist_pred;
	U64 zobrist_mirr_pred;

	for (auto iter = next_pos.cbegin(); iter != next_pos.cend(); iter++)
	{
		move = string2move(*iter);
		zobrist_pred = get_zobrist_by_move(board.board, Zobrist_val, *iter);
		zobrist_mirr_pred = get_mirror_zobrist_by_move(board.board, Zobrist_mirror_val, *iter); //���̱�

		board.move_piece(move);
		//��̬����
		int value = get_board_static_value(zobrist_pred, zobrist_mirr_pred);
		//ɱ��
		int killer_table_index = is_in_killer_table(*iter, depth);
		if (killer_table_index != -1 && killer_table_index <= max_killer_move)
			value += (analy_turn == turn) ? 10000 : (-10000);//ɱ���ŷ���������

		sorted_pos.push_back({ move,value });

		board.remove_piece(move);
	}

	if (!pre_best_process.empty()) //��������������Ҫ����
	{
		piece_move tmp = pre_best_process.front();
		pre_best_process.erase(pre_best_process.begin()); //��������
		if (analy_turn == turn)							  //MAX�� �����ֵ���
		{
			auto iter = find_if(sorted_pos.begin(), sorted_pos.end(), [tmp](const pair<piece_move, int>& lhs)
				{ return lhs.first.from_col == tmp.from_col && lhs.first.from_row == tmp.from_row && lhs.first.to_row == tmp.to_row && lhs.first.to_col == tmp.to_col; });
			if (iter != sorted_pos.end()) // �ҵ���
				iter->second = INT_MAX;	  //������ȼ�
			else
			{
				pre_best_process.clear();
			}
		}
		else
		{
			auto iter = find_if(sorted_pos.begin(), sorted_pos.end(), [tmp](const pair<piece_move, int>& lhs)
				{ return lhs.first.from_col == tmp.from_col && lhs.first.from_row == tmp.from_row && lhs.first.to_row == tmp.to_row && lhs.first.to_col == tmp.to_col; });
			if (iter != sorted_pos.end()) // �ҵ���
				iter->second = INT_MIN;	  //������ȼ�
			else
			{
				pre_best_process.clear();
			}
		}
	}

	//position startpos moves h2e2 b7e7 c3c4
	if (analy_turn == turn) //MAX�� ѡ��Ԥ�����Ľڵ�
		sort(sorted_pos.begin(), sorted_pos.end(), [](pair<piece_move, int> lhs, pair<piece_move, int> rhs)
			{ return lhs.second > rhs.second; });
	else
		sort(sorted_pos.begin(), sorted_pos.end(), [](pair<piece_move, int> lhs, pair<piece_move, int> rhs)
			{ return lhs.second < rhs.second; });

	//if (debug_fileout)
	//{
	//	board_print(board.board, out);
	//	for (int i = 0; i < sorted_pos.size(); i++)
	//	{
	//		out << "��ǰ�ߵ���Ϊ " << board.board[sorted_pos[i].first.from_row][sorted_pos[i].first.from_col];
	//		out << ", �߷�Ϊ " << sorted_pos[i].first.from_row << sorted_pos[i].first.from_col << sorted_pos[i].first.to_row << sorted_pos[i].first.to_col;
	//		out << ", ����ʽ�÷�Ϊ " << sorted_pos[i].second << endl;
	//	}
	//	out << endl
	//		<< endl
	//		<< endl;
	//}

	return sorted_pos;
}

int Chess_AI::Search(int depth, int alpha, int beta)
{
	use_zobrist_score_count = unuse_score_count = into_depth_count = use_zobrist_staticcount = unuse_static_count = 0;

	this->start_t = clock();
	this->timeout = false;
	int res = 0;
	int max_depth = depth;
	killer_moves_table.clear();		//���ɱ�ֱ�
	for (int i = 0; i <= max_depth; i++)	//Ϊÿһ�����һ��ɱ���ŷ���
		killer_moves_table.push_back(vector<Killer_Struct>());
	pre_best_process.clear();
	this_best_process.clear();
	AI_Search_process.clear();
	for (int i = 2; i <= max_depth; i += 2)
	{
#if is_dynamic
		init_score(board.board, turn);
#endif
		this_max_value = 0;
		pre_best_process = this_best_process;
		this_best_process.clear();
		AI_Search_process.clear();
		this_depth = i;
		res = inner_Search(i, alpha, beta);
		if (this->timeout)
			break;
	}

	if (debug_fileout) {
		out << "�û���������ֵʹ��" << use_zobrist_score_count << "��, δʹ��" << unuse_score_count << "��" << endl;
		out << "�û���������ֵʹ��" << use_zobrist_staticcount << "��, δʹ��" << unuse_static_count << "��" << endl;
		out << "���������" << into_depth_count << endl;
	}

	return res;
}
