#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include "large_number_calculation.h"


large_number_calculation::large_number_calculation()
{

}

large_number_calculation::~large_number_calculation()
{
}

large_number_calculation* large_number_calculation::create() {
	large_number_calculation *obj = new large_number_calculation();
	return obj;
}

void large_number_calculation::runMultiple() {
	// 检查A和B是否有设置过值
	if (this->isNumberSet != 3) return;
	// 
}

void large_number_calculation::multipleSingleNumber(unsigned int A, unsigned int singleNumber, unsigned int &result, unsigned short &carryNumber) {
	// 
	unsigned long int mr = A * singleNumber;
	// 进位得到的数
	unsigned int carryNumber = 0;
	if (mr < A && mr < singleNumber ) {

	}
}

void large_number_calculation::runAdd() {
	// 检查A和B是否有设置过值
	if (this->isNumberSet != 3) return;
	// 初始化结构体
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL; (*current).prev = NULL;
	// largeInt指针
	largeInt *pA = this->numA_tail, *pB = this->numB_tail;
	// 进位标记
	bool ifCarry = false;
	// 计数
	unsigned int count = 0;
	// 开始执行加法
	while (pA != NULL || pB != NULL || ifCarry)
	{
		// 取当前int的值，并求加法
		unsigned int A = pA == NULL ? 0 : (*pA).v;
		unsigned int B = pB == NULL ? 0 : (*pB).v;
		unsigned int R = 0;

		// 检查是否会有溢出
		// 注意一种情况：A=B=0xFFFFFFFF，并且ifCarry=true
		if (A == UINT_MAX && B == UINT_MAX && ifCarry == true) {
			R = UINT_MAX;
			// 下次进位
			ifCarry = true;
		}else if (A > UINT_MAX - B - (ifCarry ? 1 : 0)) {
			// 溢出进位
			unsigned int tmp_add = UINT_MAX - A + 1;
			R = B + (ifCarry ? 1 : 0) - tmp_add;
			// 下次进位
			ifCarry = true;
		}
		else {
			// 未溢出不进位
			R = A + B + (ifCarry ? 1 : 0);
			// 下次不进位
			ifCarry = false;
		}
		// 设置值
		(*current).v = R;
		// 移至下一个
		if (pA != NULL || pB != NULL) {
			pA = (*pA).prev;
			pB = (*pB).prev;
		}
		// 创建新节点
		if (pA != NULL || pB != NULL || ifCarry) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current; (*tmp).prev = NULL; (*current).prev = tmp;
			current = tmp; head = current;
		}
	}

	// 求出A和B中位数最大的位数的值
	unsigned int max = this->bitsA > this->bitsB ? this->bitsA : this->bitsB;

	this->bitsC = ifCarry ? max + 1 : max;
	this->numC = head;
	this->numC_tail = tail;
}

void large_number_calculation::inputHex(int num_index, const char* input) {
	// 检查当前要设置的位是否被设置过
	if (num_index == 0 && this->isNumberSet & 1 == 0) {
		return;
	}
	if (num_index == 1 && this->isNumberSet & 2 == 0) {
		return;
	}
	// 初始化结构体
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL; (*current).prev = NULL;
	// 当前读取的元素和计数
	int p = *input;
	int count = 0;
	// 每个int存储8个十六进制位，这个变量存储当前已经存储了多少
	short int current_int_load = 0;
	// 应当从低位开始存储，因此先把指针放在最末尾
	while (p != '\0') {
		p = *(input + ++count);
	}
	// 开始存储
	int index = count-1;
	while (index >= 0)
	{
		// 如果当前largeInt节点已经存满，则再创建一个
		if (current_int_load >= 8) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current; (*tmp).prev = NULL; (*current).prev = tmp;
			current = tmp; head = current; 
			current_int_load = 0;
		}
		// 读取字符串值并格式化
		p = this->hexToDecBit(*(input + index--));
		if (p >= 0) {
			// 如果输入合法输入到结构体中
			int tmp = p << (current_int_load * 4);
			(*current).v += tmp;
			current_int_load++;
		}
	}
	if (num_index == 0) {
		this->bitsA = count * 4;
		this->numA = head;
		this->numA_tail = tail;
		this->isNumberSet = this->isNumberSet | 1;
	}
	else if (num_index == 1) {
		this->bitsB = count * 4;
		this->numB = head;
		this->numB_tail = tail;
		this->isNumberSet = this->isNumberSet | 2;
	}
}

short int large_number_calculation::hexToDecBit(const char num) {
	// 输入正确性检测
	if (num >= 97 and num <= 102) {
		return num - 87;
	}
	else if (num >= 65 and num <= 70) {
		return num - 55;
	}
	else if (num >= 48 and num <= 57) {
		return num - 48;
	}
	else {
		return -1;
	}
}

void large_number_calculation::getValue(int num_index) {
	unsigned int bits_count = 0;
	largeInt *head;
	if (num_index == 0) {
		head = this->numA;
	}
	else if (num_index == 0) {
		head = this->numB;
	}
	else {
		head = this->numC;
	}

	largeInt *current = head;
	while (current != NULL)
	{
		unsigned int num = (*current).v;
		for (size_t i = 8; i > 0; i--)
		{
			int offset = i - 1;
			unsigned int tmp = (num & (0xF << (offset * 4))) >> (offset * 4);
			std::cout << this->hex2char[tmp];
		}
		current = (*current).next;
	}
	std::cout << std::endl;
}