#pragma once

// unsigned int 可以表示的最大 ‭4294967295‬

// 使用链表
typedef struct largeInt {
	unsigned int v;
	largeInt *next;
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
	char* getResult();
	
	// 运算
	void runAdd();
	void runMinus();
	void runMultiple();
	void runDivide();

private:

	largeInt * numA, *numA_tail;
	largeInt * numB, *numB_tail;
	largeInt * numC, *numC_tail;
	largeInt * numD, *numD_tail;

	// 将一个十六进制位转换成一个十进制数
	short int hexToDecBit(const char a);

};

