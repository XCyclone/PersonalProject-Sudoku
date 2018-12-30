#pragma once
#ifndef BLANK_H
#define BLANK_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std;

class Blank
{
private:
	int box[9][9] = { 0 };
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;
public:
	Blank(const char*);
	void block_much(int*);
	void block_few(int*);
	void read_file();
	void output();
};



#endif // !1