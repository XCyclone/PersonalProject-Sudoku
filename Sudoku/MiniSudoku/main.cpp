#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "generator.h"
#include "solution.h"
#include "blank.h"
using namespace std;

int main(int argc, char *argv[])
{
	//��ȡ�������������
	if (argc > 1)
	{
		//����Ϊ��-c��ʱ�����նˣ���ȡ�����ն���
		if (strcmp(argv[1], "-c") == 0)
		{
			int input;
			if (sscanf_s(argv[2], "%d", &input) && input > 0 && input <=1000000) {
					new Generator(input);
			}
			else
			{
				cout << "������ʽ������������ȷ������" << endl;
				cout << "--------------------------------------------------" << endl;
				cout << "���磺Sudoku.exe -c 20" << endl;
				exit(0);
			}
		}
		//����Ϊ��-s��ʱ�����������ȡ�����ļ���ַ
		else if (strcmp(argv[1], "-s") == 0)
		{
			const char* input = argv[2];
			//cout << input;
			FILE *fp;
			fp = fopen(input, "r+");
			if (fp == NULL)
			{
				cout << "�ļ�·�������ڣ���������ȷ·����" << endl;
				cout << "--------------------------------------------------" << endl;
				cout << "���磺Sudoku.exe -s .\\input.txt" << endl;
				exit(0);
			}
			new Solution(input);
		}
		//else if (strcmp(argv[1], "-b") == 0)		//�ڿղ���
		//{
		//	const char* input = argv[2];
		//	new Blank(input);
		//}
		else
		{
			cout << "�����ʽ������������ȷ�Ĳ�����" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "�����վ֣�Sudoku.exe -c �վ���" << endl;
			cout << "���磺Sudoku.exe -c 20" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "���������Sudoku.exe -s ������������Ĵ洢·��" << endl;
			cout << "���磺Sudoku.exe -s .\\input.txt" << endl;
			exit(0);
		}
	}
	//else
	//{
	//	char format[2];
	//	cin >> format;
	//	if (format[0] == '-' && format[1] == 'c')
	//	{
	//		int input;
	//		cin >> input;
	//		new Generator(input);
	//	}
	//	else if (format[0] == '-' && format[1] == 's')
	//	{
	//		char* input = { 0 };
	//		cin >> input;
	//		new Solution(input);
	//	}
	//}
	//int input;
	//cin >> input;
	//new Generator(input);
	return 0;
}