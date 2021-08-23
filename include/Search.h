#pragma once
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <string>
#include <vector>
#include <utility>
#include "const.h"
#include "Zobrist.h"
#include "utils.h"
#include "Chess_board.h"
#include "score_table.h"
#include <ctime>
#include "GetPossibility.h"
using namespace std;

#define is_dynamic 0
extern int chess_index[130];
extern int chess_score;
extern int position_score;

const int Undefined = 0x7fffffff;

string move2string(piece_move mv);
string move2uccistring(piece_move mv);

//本结构体为置换表内容
struct Zobrist_Item
{
	//初始时分数为未定义,表示还没被赋值过
	position_values score = Undefined;			 //局面的值,暂时还不知道怎么用
	static_eval_values static_value = Undefined; //静态评估值
};
enum class Zobrist_Type
{
	none,
	zobrist,
	zobrist_mirr
};
//杀手着法结构体
struct Killer_Struct
{
	std::string move;
	short count;
};
const int max_killer_move = 4;//每层最多记录max_killer_move个杀手着法

class Chess_AI
{
private:
	int inner_Search(int depth, int alpha, int beta);
	piece_move string2move(const string& str);
	vector<pair<piece_move, int>> seekPoints(gameTurn analy_turn, const int depth);
	const Zobrist_Type is_in_ZobristMap(Zobrist_Item&, const U64, const U64);

	int this_depth;
	//时间检测
	clock_t start_t;
	clock_t max_t;
	bool timeout; //是否超时
	std::unordered_map<U64, Zobrist_Item> Zobrist_map;
	vector<piece_move> pre_best_process; //迭代加深时优先扩展上一次最优结点
	vector<piece_move> this_best_process;
	vector<piece_move> AI_Search_process;
	position_values this_max_value;
	vector<vector<Killer_Struct>> killer_moves_table;
	const int is_in_killer_table(const std::string& move, const int depth)const;
	void update_killer_table(const std::string& move, const int depth);
	//const bool judge_long_move(const std::string& move);

public:
	Chess_AI();
	Chess_AI(gameTurn);
	void init_Turn(gameTurn);
	void init_max_t(const long); //初始化最大时间
	void oppen_Go(chess_board new_board);
	int Search(int depth, int alpha, int beta);
	position_values get_board_score(const U64 Zobrist_val, const U64 Zobrist_mirror_val);
	static_eval_values get_board_static_value(const U64 Zobrist_val, const U64 Zobrist_mirror_val);

	U64 Zobrist_val;
	U64 Zobrist_mirror_val;

	ChessBoard board;
	gameTurn turn;
	piece_move best_decision;
	int best_score;
	//vector<string>history_moves;	//记录历史着法

	int use_zobrist_score_count, unuse_score_count;
	int use_zobrist_staticcount, unuse_static_count;
	int into_depth_count;
};
