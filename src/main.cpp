#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
#include "../include/score_table.h"
using namespace std;
int main() {
    string sel;
    char board[board_row][board_col]={0};
    int chess_index[130];//�����������ͺ�������ӳ�䣬����Ѱ��
    board_initial(board,chess_index);
    char who_turn = '\0';
    char my_turn = '\0';
    string board_status;
    vector<string> moves;//�ַ��������������뵱ǰ���̻����߹��Ĳ�
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
        else if(sel == "position")//����ֻ���˶����ַ�����ת�����̵Ĺ���
        {
            read_position(who_turn,board_status,moves);
            string2board(board,board_status,moves);
            int score = cal_score(board,my_turn,chess_index);
            cout<<"�����ֵ�"<<who_turn<<"������"<<endl;//��һ����
            board_print(board);//�������
            cout<<"��ǰ���̵÷�Ϊ : "<<score<<endl;
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