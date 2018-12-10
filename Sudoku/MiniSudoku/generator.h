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
	int num = 0;								//定义生成终局个数
	int now = 0;								//定义已生成终局个数
	clock_t start, finish;						//定义开始、结束时间
	double totaltime;							//定义总生成时长
	int box[9][9] = { 0 };						//定义9*9数独存放数组
	int temp[9] = { 0 };						//定义第一行生成数字存放数组
	int mark[9] = { 0 };						//定义已填充数组
	char model[9][9] = {						//定义模板：采用模板法生成可以节省递归求解的时间增加效率，其中已对1e6数据进行验证不会生成重复终局
			{ 'i','g','h','c','a','b','f','d','e' },{ 'c','a','b','f','d','e','i','g','h' },{ 'f','d','e','i','g','h','c','a','b' },{ 'g','h','i','a','b','c','d','e','f' },{ 'a','b','c','d','e','f','g','h','i' },{ 'd','e','f','g','h','i','a','b','c' },{ 'h','i','g','b','c','a','e','f','d' },

		{ 'b','c','a','e','f','d','h','i','g' },{ 'e','f','d','h','i','g','b','c','a' }
	};
	FILE *fp = NULL;							//定义生成终局存放文件


public:
	Generator(int);								//初始化
	void change_to_num();						//根据模板和第一行生成数列转换为终局
	void generate_first_line(int);				//递归生成终局第一行
	void wrap_row(int, int);					//交换行
	void wrap_col(int, int);					//交换列
	void wrap(int);								//对已生成终局交换生成新终局
	void output();								//输出到文件

};



#endif // !1