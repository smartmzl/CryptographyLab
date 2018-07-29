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

// ʹ�ö����Ƹ�ʽ����ַ����е�ÿһ���ֽ�
void PrintInBin(char* str, int length) {
	cout << "------------------------------------" << endl;
	for (int i = 0; i < length; i++)
	{
		cout << i << "\t";
		cout << bitset<8>(str[i]) << endl;
	}
	cout << "------------------------------------" << endl;
}

// ʹ�ö����Ƹ�ʽ����ַ����е�ÿһ���ֽ�
void PrintInBin(int num) {
	cout << "------------------------------------" << endl;
	cout << bitset<32>(num) << endl;
	cout << dec << num << endl;
	cout << hex << num << endl;
	cout << "------------------------------------" << endl;
}