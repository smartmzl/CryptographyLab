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
	// ��ʼ���ṹ��
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL;
	// ��ǰ��ȡ��Ԫ�غͼ���
	int p = *input;
	int count = 0;
	// ÿ��int�洢8��ʮ������λ����������洢��ǰ�Ѿ��洢�˶���
	int current_int_load = 0;
	// Ӧ���ӵ�λ��ʼ�洢������Ȱ�ָ�������ĩβ
	while (p != '\0') {
		p = *(input + ++count);
	}
	// ��ʼ�洢
	int index = count - 1;
	while (index >= 0)
	{
		// �����ǰlargeInt�ڵ��Ѿ����������ٴ���һ��
		if (current_int_load >= 8) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current;
			current = tmp; head = current;
			current_int_load = 0;
			printf_s("----- new int -----");
		}
		// ��ȡ�ַ���ֵ����ʽ��
		p = this->hexToDecBit(*(input + index--));

		printf_s("%s", *(input + index--));
		
		// ���뵽�ṹ����
		int tmp = p << (current_int_load * 4);
		(*current).v += tmp;
		current_int_load++;
	}

	this->numA = head;
	this->numA_tail = tail;

}

short int large_number_calculation::hexToDecBit(const char num) {
	// ������ȷ�Լ��
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