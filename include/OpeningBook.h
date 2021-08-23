#include <iostream>
#include <string>
#include "const.h"

//���ֿ���Ϣ
struct BookInfo		//��Ϊmap��Ӧ��ϵ�Ĳο�
{
	//uint32_t dwLock;
	uint16_t move;	//�ر�ע��,�˴���moveʵ�����Ѿ�����4��char����ʽ�洢,ÿ��charռ4bit
	uint16_t weight;
};

//��ʼ�����ֿ�.�˺�����Ҫ��main������ʼʱ����
void init_opening_book();

/*********************************************************
* ������: move_to_uccimove
* ����:  �����ǵ�moveת��Ϊucci��move��ʽ
* move: ���ǵ��ŷ��ַ���,��"1234"��ʾ1��2���ߵ�3��4��
* ����ֵ: ucci��move��,��"1234"��Ӧ"c1e3"
*********************************************************/
std::string move_to_uccimove(const std::string move);

/*********************************************************
* ������: search_openging_book
* ����:  ���ҿ��ֿ�
* zobrist: ��ǰ���̵�zobristֵ
* mirr_zobrist: ��ǰ���̵�**����**�����zobristֵ
* board: ��ǰ����
* ����ֵ: �ŷ��б�,��"1234"��ʾ1��2���ߵ�3��4��
* ע��: ����ֵ�����ǿ�vector,��ʾ���ֿ�û���ŷ�
*********************************************************/
std::vector<std::string> search_openging_book(const uint64_t zobrist, const uint64_t mirr_zobrist, const char(&board)[board_row][board_col]);