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
	int box[9][9] = { 0 };	//定义9*9数独存放数组
	FILE *fp_read = NULL;	//定义读取数独文件位置
	FILE *fp_write = NULL;	//定义存放数独文件位置
	int sign[81][10];		//定义每个数独空位可填写的数组
	int flag = 0;			//定义是否已经将所有有唯一解的位置填满
	int flag2 = 0;			//定义是否已经将所有有唯一解的位置填满
	clock_t start, finish;						//定义开始、结束时间
	double totaltime;							//定义总生成时长
	int numm = 0;
public:
	Solution(const char*);			//初始化
	void read_file();				//读取文件
	void full();					//填充空格
	void full_block(int, int);		//填充某空格
	bool full_dfs(int, int);		//扫描填充空格完毕后递归求解剩余空格
	void output();					//输出到文件
	bool find_next_block(int, int*, int*);	//寻找下一空格
};


#endif
