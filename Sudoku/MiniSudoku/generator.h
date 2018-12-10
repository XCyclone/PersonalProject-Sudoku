#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std;

class Generator
{
private:
	int num = 0;								//���������վָ���
	int now = 0;								//�����������վָ���
	clock_t start, finish;						//���忪ʼ������ʱ��
	double totaltime;							//����������ʱ��
	int box[9][9] = { 0 };						//����9*9�����������
	int temp[9] = { 0 };						//�����һ���������ִ������
	int mark[9] = { 0 };						//�������������
	char model[9][9] = {						//����ģ�壺����ģ�巨���ɿ��Խ�ʡ�ݹ�����ʱ������Ч�ʣ������Ѷ�1e6���ݽ�����֤���������ظ��վ�
			{ 'i','g','h','c','a','b','f','d','e' },{ 'c','a','b','f','d','e','i','g','h' },{ 'f','d','e','i','g','h','c','a','b' },{ 'g','h','i','a','b','c','d','e','f' },{ 'a','b','c','d','e','f','g','h','i' },{ 'd','e','f','g','h','i','a','b','c' },{ 'h','i','g','b','c','a','e','f','d' },

		{ 'b','c','a','e','f','d','h','i','g' },{ 'e','f','d','h','i','g','b','c','a' }
	};
	FILE *fp = NULL;							//���������վִ���ļ�


public:
	Generator(int);								//��ʼ��
	void change_to_num();						//����ģ��͵�һ����������ת��Ϊ�վ�
	void generate_first_line(int);				//�ݹ������վֵ�һ��
	void wrap_row(int, int);					//������
	void wrap_col(int, int);					//������
	void wrap(int);								//���������վֽ����������վ�
	void output();								//������ļ�

};



#endif // !1