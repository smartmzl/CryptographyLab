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
	// ���A��B�Ƿ������ù�ֵ
	if (this->isNumberSet != 3) return;
	// 
}

void large_number_calculation::multipleSingleNumber(unsigned int A, unsigned int singleNumber, unsigned int &result, unsigned short &carryNumber) {
	// 
	unsigned long int mr = A * singleNumber;
	// ��λ�õ�����
	unsigned int carryNumber = 0;
	if (mr < A && mr < singleNumber ) {

	}
}

void large_number_calculation::runAdd() {
	// ���A��B�Ƿ������ù�ֵ
	if (this->isNumberSet != 3) return;
	// ��ʼ���ṹ��
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL; (*current).prev = NULL;
	// largeIntָ��
	largeInt *pA = this->numA_tail, *pB = this->numB_tail;
	// ��λ���
	bool ifCarry = false;
	// ����
	unsigned int count = 0;
	// ��ʼִ�мӷ�
	while (pA != NULL || pB != NULL || ifCarry)
	{
		// ȡ��ǰint��ֵ������ӷ�
		unsigned int A = pA == NULL ? 0 : (*pA).v;
		unsigned int B = pB == NULL ? 0 : (*pB).v;
		unsigned int R = 0;

		// ����Ƿ�������
		// ע��һ�������A=B=0xFFFFFFFF������ifCarry=true
		if (A == UINT_MAX && B == UINT_MAX && ifCarry == true) {
			R = UINT_MAX;
			// �´ν�λ
			ifCarry = true;
		}else if (A > UINT_MAX - B - (ifCarry ? 1 : 0)) {
			// �����λ
			unsigned int tmp_add = UINT_MAX - A + 1;
			R = B + (ifCarry ? 1 : 0) - tmp_add;
			// �´ν�λ
			ifCarry = true;
		}
		else {
			// δ�������λ
			R = A + B + (ifCarry ? 1 : 0);
			// �´β���λ
			ifCarry = false;
		}
		// ����ֵ
		(*current).v = R;
		// ������һ��
		if (pA != NULL || pB != NULL) {
			pA = (*pA).prev;
			pB = (*pB).prev;
		}
		// �����½ڵ�
		if (pA != NULL || pB != NULL || ifCarry) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current; (*tmp).prev = NULL; (*current).prev = tmp;
			current = tmp; head = current;
		}
	}

	// ���A��B��λ������λ����ֵ
	unsigned int max = this->bitsA > this->bitsB ? this->bitsA : this->bitsB;

	this->bitsC = ifCarry ? max + 1 : max;
	this->numC = head;
	this->numC_tail = tail;
}

void large_number_calculation::inputHex(int num_index, const char* input) {
	// ��鵱ǰҪ���õ�λ�Ƿ����ù�
	if (num_index == 0 && this->isNumberSet & 1 == 0) {
		return;
	}
	if (num_index == 1 && this->isNumberSet & 2 == 0) {
		return;
	}
	// ��ʼ���ṹ��
	largeInt *head = (largeInt*)malloc(sizeof(largeInt));
	largeInt *tail = head;
	largeInt *current = head;
	(*current).v = 0; (*current).next = NULL; (*current).prev = NULL;
	// ��ǰ��ȡ��Ԫ�غͼ���
	int p = *input;
	int count = 0;
	// ÿ��int�洢8��ʮ������λ����������洢��ǰ�Ѿ��洢�˶���
	short int current_int_load = 0;
	// Ӧ���ӵ�λ��ʼ�洢������Ȱ�ָ�������ĩβ
	while (p != '\0') {
		p = *(input + ++count);
	}
	// ��ʼ�洢
	int index = count-1;
	while (index >= 0)
	{
		// �����ǰlargeInt�ڵ��Ѿ����������ٴ���һ��
		if (current_int_load >= 8) {
			largeInt *tmp = (largeInt*)malloc(sizeof(largeInt));
			(*tmp).v = 0; (*tmp).next = current; (*tmp).prev = NULL; (*current).prev = tmp;
			current = tmp; head = current; 
			current_int_load = 0;
		}
		// ��ȡ�ַ���ֵ����ʽ��
		p = this->hexToDecBit(*(input + index--));
		if (p >= 0) {
			// �������Ϸ����뵽�ṹ����
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