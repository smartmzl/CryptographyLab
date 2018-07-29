/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#include "stdafx.h"
#include <iostream>
#include <bitset>

using namespace std;

// 使用二进制格式输出字符串中的每一个字节
void PrintInBin(char* str, int length) {
	cout << "------------------------------------" << endl;
	for (int i = 0; i < length; i++)
	{
		cout << i << "\t";
		cout << bitset<8>(str[i]) << endl;
	}
	cout << "------------------------------------" << endl;
}

// 使用二进制格式输出字符串中的每一个字节
void PrintInBin(int num) {
	cout << "------------------------------------" << endl;
	cout << bitset<32>(num) << endl;
	cout << dec << num << endl;
	cout << hex << num << endl;
	cout << "------------------------------------" << endl;
}