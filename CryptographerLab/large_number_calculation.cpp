#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
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

void large_number_calculation::inputHex(int num_index, const char* input) {
	// 初始化结构体
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL;
	// 当前读取的元素和计数
	int p = *input;
	int count = 0;
	// 每个int存储8个十六进制位，这个变量存储当前已经存储了多少
	int current_int_load = 0;
	// 应当从低位开始存储，因此先把指针放在最末尾
	while (p != '\0') {
		p = *(input + ++count);
	}
	// 开始存储
	int index = count - 1;
	while (index >= 0)
	{
		// 如果当前largeInt节点已经存满，则再创建一个
		if (current_int_load >= 8) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current;
			current = tmp; head = current;
			current_int_load = 0;
			printf_s("----- new int -----");
		}
		// 读取字符串值并格式化
		p = this->hexToDecBit(*(input + index--));

		printf_s("%s", *(input + index--));
		
		// 输入到结构体中
		int tmp = p << (current_int_load * 4);
		(*current).v += tmp;
		current_int_load++;
	}

	this->numA = head;
	this->numA_tail = tail;

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
}