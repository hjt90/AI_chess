#include <iostream>
#include "../include/utils.h"
#include "../include/const.h"
using namespace std;


//������ȡposition������ŵ��ַ�����who_turn����ĳ�˵Ļغϣ�board_status��������״̬��moves��ʾ��Ҫ�ߵĲ���
void read_position(char& who_turn, string& board_status, vector<string>& moves)
{
	string buffer;
	moves.clear();	//��������ŷ�

	cin >> buffer;
	cin >> board_status;
	cin >> who_turn;
	who_turn = (who_turn == 'b') ? 'b' : 'r';		//��who_turnת��Ϊ'r'��'b'
	cin >> buffer;	//-
	cin >> buffer;	//-
	cin >> buffer;	//˫��û�г��ӵ����岽��(��غ���)
	cin >> buffer;	//��ǰ�Ļغ���

	if (cin.peek() != '\n') {
		cin >> buffer;	//moves

		while (cin.peek() != '\n') {
			cin >> buffer;
			moves.push_back(buffer);
		}
	}

	if (moves.size() % 2)
		who_turn = (who_turn == 'b') ? 'r' : 'b';
}


