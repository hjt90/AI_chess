#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
using namespace std;
int main() {
    string sel;
    char board[board_row][board_col]={0};
    int chess_index[130];//建立棋子类型和索引的映射，快速寻找
    board_initial(board,chess_index);
    char who_turn = '\0';
    char my_turn = '\0';
    string board_status;
    vector<string> moves;//字符串描述的棋盘离当前棋盘还需走过的步
    while(1)
    {
        cin >> sel;
        if(sel=="ucci")
        {
            ;
            //pass
        }
        else if(sel == "isready")
        {
            ;
            //pass
        }
        else if(sel == "position")//这里只做了读入字符串和转换棋盘的工作
        {
            read_position(who_turn,board_status,moves);
            string2board(board,board_status,moves);
            int score = cal_score(board,my_turn,chess_index);
            cout<<"现在轮到"<<who_turn<<"方动了"<<endl;//哪一方动
            board_print(board);//输出棋盘
            cout<<"当前棋盘得分为 : "<<score<<endl;
            //pass
        }
        else if(sel=="go")
        {
            ;
            //pass
        }
        else
        {
            ;
            //pass
            break;
        }
    }    
    return 0;
}