#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;

//用来读取position后面跟着的字符串，who_turn代表某人的回合，board_status代表棋盘状态，moves表示还要走的步数
void read_position(char &who_turn,string &board_status,vector<string> &moves)
{
    char pd = '\0';
    string temp;
    for(int i=0;;i++)
    {
        pd = cin.get();    
        if(pd==' ')//空格代表还没到末尾
        {
            if(i==0)//第一个读入
                cin>>temp;
            else if(i==1)
                cin>>board_status;
            else if(i==2)
                cin>>who_turn;
            else if(i==3||i==4||i==5||i==6||i==7)//这里忽略了"- - 0 1 moves"五个部分，如果以后要用的话可以修改
            {
                cin>>temp;
                continue;
            }
            else
            {
                cin>>temp;
                moves.push_back(temp);
            }
        }
        else if(pd=='\n')//读完了
            break;
    }
}


