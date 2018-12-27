#ifndef SOLUTION_H
#define SOLUTION_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Solution
{
private:
	int box[9][9] = { 0 };	//����9*9�����������
	FILE *fp_read = NULL;	//�����ȡ�����ļ�λ��
	FILE *fp_write = NULL;	//�����������ļ�λ��
	int sign[81][10];		//����ÿ��������λ����д������
	int flag = 0;			//�����Ƿ��Ѿ���������Ψһ���λ������
	int flag2 = 0;			//�����Ƿ��Ѿ���������Ψһ���λ������
	clock_t start, finish;						//���忪ʼ������ʱ��
	double totaltime;							//����������ʱ��
	int numm = 0;
public:
	Solution(const char*);			//��ʼ��
	void read_file();				//��ȡ�ļ�
	void full();					//���ո�
	void full_block(int, int);		//���ĳ�ո�
	bool full_dfs(int, int);		//ɨ�����ո���Ϻ�ݹ����ʣ��ո�
	void output();					//������ļ�
	bool find_next_block(int, int*, int*);	//Ѱ����һ�ո�
};


#endif
