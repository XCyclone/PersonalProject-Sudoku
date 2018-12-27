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
	//获取命令行输入参数
	if (argc > 1)
	{
		//输入为“-c”时生成终端，获取生成终端数
		if (strcmp(argv[1], "-c") == 0)
		{
			int input;
			if (sscanf_s(argv[2], "%d", &input) && input > 0 && input <=1000000) {
					new Generator(input);
			}
			else
			{
				cout << "参数格式错误！请输入正确参数：" << endl;
				cout << "--------------------------------------------------" << endl;
				cout << "例如：Sudoku.exe -c 20" << endl;
				exit(0);
			}
		}
		//输入为“-s”时求解数独，获取数独文件地址
		else if (strcmp(argv[1], "-s") == 0)
		{
			const char* input = argv[2];
			//cout << input;
			FILE *fp;
			fp = fopen(input, "r+");
			if (fp == NULL)
			{
				cout << "文件路径不存在！请输入正确路径：" << endl;
				cout << "--------------------------------------------------" << endl;
				cout << "例如：Sudoku.exe -s .\\input.txt" << endl;
				exit(0);
			}
			new Solution(input);
		}
		//else if (strcmp(argv[1], "-b") == 0)		//挖空部分
		//{
		//	const char* input = argv[2];
		//	new Blank(input);
		//}
		else
		{
			cout << "输入格式错误！请输入正确的参数：" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "生成终局：Sudoku.exe -c 终局数" << endl;
			cout << "例如：Sudoku.exe -c 20" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "求解数独：Sudoku.exe -s 所需求解数独的存储路径" << endl;
			cout << "例如：Sudoku.exe -s .\\input.txt" << endl;
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