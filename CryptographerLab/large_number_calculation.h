#pragma once

// unsigned int 可以表示的最大 ‭4294967295‬

// 使用链表
typedef struct largeInt {
	unsigned int v;
	largeInt *next;
	largeInt *prev;
}largeInt;

class large_number_calculation
{
public:
	large_number_calculation();
	~large_number_calculation();

	// 工厂方法
	static large_number_calculation* create();

	// 输入大整数，index={0|1|2|3}，输入以字符串形式输入，只支持16进制
	// 高位在前，低位在后
	void inputHex(int num_index, const char* input);
	
	// 获取运算结果
	void getValue(int num_index);
	
	// 运算
	void runAdd();
	void runMinus();
	void runMultiple();
	void runDivide();

private:

	// 是否已经设置了值
	// 0:未设置 1:A设置了 2:B设置了 3:A和B都设置了
	short isNumberSet = 0;

	// 大数寄存器
	largeInt * numA, *numA_tail;
	largeInt * numB, *numB_tail;
	largeInt * numC, *numC_tail;

	// 位数计数
	int bitsA = 0, bitsB = 0, bitsC = 0;

	// 将一个十六进制位转换成一个十进制数
	short int hexToDecBit(const char a);

	// 乘数乘以乘以一个十进制数
	void multipleSingleNumber(unsigned int A, unsigned int singleNumber, unsigned int &result, unsigned short &carryNumber);

	// hex2char
	char hex2char[16] = { '0' ,'1' ,'2' ,'3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9' ,'A' ,'B' ,'C' ,'D' ,'E','F' };

};

