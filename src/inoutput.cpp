#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;

//������ȡposition������ŵ��ַ�����who_turn����ĳ�˵Ļغϣ�board_status��������״̬��moves��ʾ��Ҫ�ߵĲ���
void read_position(char &who_turn,string &board_status,vector<string> &moves)
{
    char pd = '\0';
    string temp;
    for(int i=0;;i++)
    {
        pd = cin.get();    
        if(pd==' ')//�ո����û��ĩβ
        {
            if(i==0)//��һ������
                cin>>temp;
            else if(i==1)
                cin>>board_status;
            else if(i==2)
                cin>>who_turn;
            else if(i==3||i==4||i==5||i==6||i==7)//���������"- - 0 1 moves"������֣�����Ժ�Ҫ�õĻ������޸�
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
        else if(pd=='\n')//������
            break;
    }
}


