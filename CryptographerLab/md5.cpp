/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "md5.h"
#include <time.h>
#include <windows.h>  
#include <iostream>  

using namespace std;

/*
使用方法实例：

md5* obj = md5::create();
char *cipher = new char[32];
obj->md5_str("123456", cipher);
cout << "md5 text: " << cipher << endl;

*/

// 创建md5对象
md5* md5::create() {
	// 创建对象
	md5 *obj = new md5();
	return obj;
}
void md5::destroy() {
	delete this;
}
md5::md5() {

}
md5::~md5() {

}

// 对字符串进行加密
void md5::md5_str(const char cstr[], char *cipher) {

	// 初始化缓存区(每个32bit)
	// 在实际的存储中，采用最低位有效字节优先的顺序存储
	this->A = 0x67452301;
	this->B = 0xEFCDAB89;
	this->C = 0x98BADCFE;
	this->D = 0x10325476;

	// 首先获取字符串的比特长度，分为字节长度和比特长度。
	// string::size_type 一定是unsigned的，但可能是int或long。
	// unsigned long long 为64位类型，
	// 可以表示的数据大小刚好与“填充长度”的位长度一致。
	ULL byte_size = strlen(cstr);
	ULL bit_size = byte_size << 3;

	// 输入长度加上长度填充后的长度
	ULL expect_length = byte_size + 8;
	// 余数（填充消息的长度）
	US group_modulus = expect_length % 64;
	// 分组总数
	ULL group_count = (expect_length >> 6) + 1;
	// 消息填充的字节数
	US msg_padding_byte = (64 - group_modulus) & 0x3F;
	// 长度填充的字节数（紧随输入的第一个字节）
	US msg_padding_byte_128 = msg_padding_byte == 0 ? 0 : 1;

	// 对输入数据进行格式化，填补比特，并将返回值存储在一个新的存储空间中
	// 首先全部设置为0，
	ULL total_byte = (group_count << 6);
	char *data = new char[total_byte];
	memset(data, 0, (size_t)total_byte);

	// 复制原有数据
	memcpy(data, cstr, byte_size);

	// 末尾需要补上1
	if (msg_padding_byte_128 = 1) {
		data[byte_size] = 128;
	}

	// 补上消息长度，八字节
	// 特别说明，这里是最低有效字节优先的顺序存储的
	memcpy(data + total_byte - 8, &bit_size, 8);

	// 当前正在处理的分组，以及对应的比特范围
	ULL group_num = 0;

	// 开始处理消息分组
	for (; group_num < group_count; ++group_num)
	{ 
		// 使用Hmd5计算
		this->Hmd5(data, group_num);
	}

	// 拼装缓冲区
	UI *result = new UI[16];
	this->md5_final(result);
	for (int i = 0; i < 16; ++i) {
		sprintf_s((cipher + (i << 1)), 4, "%02x", result[i]);
	}

	// 清空资源
	delete result;
	delete data;

}

bool md5::Hmd5(const char *data, ULL group_num) {
	// 计算需要处理的比特范围
	ULL start_byte = (group_num << 6);
	
	// 临时存储缓存A,B,C,D
	UI a = this->A, b = this->B, c = this->C, d = this->D;
	UI SUB_GROUP;

	// Round 1
	ROUND_STEP(7, 0xd76aa478, 0, gF, a, b, c, d);
	ROUND_STEP(12, 0xe8c7b756, 1, gF, d, a, b, c);
	ROUND_STEP(17, 0x242070db, 2, gF, c, d, a, b);
	ROUND_STEP(22, 0xc1bdceee, 3, gF, b, c, d, a);
	ROUND_STEP(7, 0xf57c0faf, 4, gF, a, b, c, d);
	ROUND_STEP(12, 0x4787c62a, 5, gF, d, a, b, c);
	ROUND_STEP(17, 0xa8304613, 6, gF, c, d, a, b);
	ROUND_STEP(22, 0xfd469501, 7, gF, b, c, d, a);
	ROUND_STEP(7, 0x698098d8, 8, gF, a, b, c, d);
	ROUND_STEP(12, 0x8b44f7af, 9, gF, d, a, b, c);
	ROUND_STEP(17, 0xffff5bb1, 10, gF, c, d, a, b);
	ROUND_STEP(22, 0x895cd7be, 11, gF, b, c, d, a);
	ROUND_STEP(7, 0x6b901122, 12, gF, a, b, c, d);
	ROUND_STEP(12, 0xfd987193, 13, gF, d, a, b, c);
	ROUND_STEP(17, 0xa679438e, 14, gF, c, d, a, b);
	ROUND_STEP(22, 0x49b40821, 15, gF, b, c, d, a);

	// Round 2
	ROUND_STEP(5, 0xf61e2562, 1, gG, a, b, c, d);
	ROUND_STEP(9, 0xc040b340, 6, gG, d, a, b, c);
	ROUND_STEP(14, 0x265e5a51, 11, gG, c, d, a, b);
	ROUND_STEP(20, 0xe9b6c7aa, 0, gG, b, c, d, a);
	ROUND_STEP(5, 0xd62f105d, 5, gG, a, b, c, d);
	ROUND_STEP(9, 0x02441453, 10, gG, d, a, b, c);
	ROUND_STEP(14, 0xd8a1e681, 15, gG, c, d, a, b);
	ROUND_STEP(20, 0xe7d3fbc8, 4, gG, b, c, d, a);
	ROUND_STEP(5, 0x21e1cde6, 9, gG, a, b, c, d);
	ROUND_STEP(9, 0xc33707d6, 14, gG, d, a, b, c);
	ROUND_STEP(14, 0xf4d50d87, 3, gG, c, d, a, b);
	ROUND_STEP(20, 0x455a14ed, 8, gG, b, c, d, a);
	ROUND_STEP(5, 0xa9e3e905, 13, gG, a, b, c, d);
	ROUND_STEP(9, 0xfcefa3f8, 2, gG, d, a, b, c);
	ROUND_STEP(14, 0x676f02d9, 7, gG, c, d, a, b);
	ROUND_STEP(20, 0x8d2a4c8a, 12, gG, b, c, d, a);

	// Round 3
	ROUND_STEP(4, 0xfffa3942, 5, gH, a, b, c, d);
	ROUND_STEP(11, 0x8771f681, 8, gH, d, a, b, c);
	ROUND_STEP(16, 0x6d9d6122, 11, gH, c, d, a, b);
	ROUND_STEP(23, 0xfde5380c, 14, gH, b, c, d, a);
	ROUND_STEP(4, 0xa4beea44, 1, gH, a, b, c, d);
	ROUND_STEP(11, 0x4bdecfa9, 4, gH, d, a, b, c);
	ROUND_STEP(16, 0xf6bb4b60, 7, gH, c, d, a, b);
	ROUND_STEP(23, 0xbebfbc70, 10, gH, b, c, d, a);
	ROUND_STEP(4, 0x289b7ec6, 13, gH, a, b, c, d);
	ROUND_STEP(11, 0xeaa127fa, 0, gH, d, a, b, c);
	ROUND_STEP(16, 0xd4ef3085, 3, gH, c, d, a, b);
	ROUND_STEP(23, 0x04881d05, 6, gH, b, c, d, a);
	ROUND_STEP(4, 0xd9d4d039, 9, gH, a, b, c, d);
	ROUND_STEP(11, 0xe6db99e5, 12, gH, d, a, b, c);
	ROUND_STEP(16, 0x1fa27cf8, 15, gH, c, d, a, b);
	ROUND_STEP(23, 0xc4ac5665, 2, gH, b, c, d, a);

	// Round 4
	ROUND_STEP(6, 0xf4292244, 0, gI, a, b, c, d);
	ROUND_STEP(10, 0x432aff97, 7, gI, d, a, b, c);
	ROUND_STEP(15, 0xab9423a7, 14, gI, c, d, a, b);
	ROUND_STEP(21, 0xfc93a039, 5, gI, b, c, d, a);
	ROUND_STEP(6, 0x655b59c3, 12, gI, a, b, c, d);
	ROUND_STEP(10, 0x8f0ccc92, 3, gI, d, a, b, c);
	ROUND_STEP(15, 0xffeff47d, 10, gI, c, d, a, b);
	ROUND_STEP(21, 0x85845dd1, 1, gI, b, c, d, a);
	ROUND_STEP(6, 0x6fa87e4f, 8, gI, a, b, c, d);
	ROUND_STEP(10, 0xfe2ce6e0, 15, gI, d, a, b, c);
	ROUND_STEP(15, 0xa3014314, 6, gI, c, d, a, b);
	ROUND_STEP(21, 0x4e0811a1, 13, gI, b, c, d, a);
	ROUND_STEP(6, 0xf7537e82, 4, gI, a, b, c, d);
	ROUND_STEP(10, 0xbd3af235, 11, gI, d, a, b, c);
	ROUND_STEP(15, 0x2ad7d2bb, 2, gI, c, d, a, b);
	ROUND_STEP(21, 0xeb86d391, 9, gI, b, c, d, a);

	// 加回去！
	this->A += a;
	this->B += b;
	this->C += c;
	this->D += d;

	return true;
}

void md5::md5_final(UI* cipher) {

	cipher[ 0] = (this->A >> 0) & 0xFF;
	cipher[ 1] = (this->A >> 8) & 0xFF;
	cipher[ 2] = (this->A >> 16) & 0xFF;
	cipher[ 3] = (this->A >> 24) & 0xFF;

	cipher[ 4] = (this->B >> 0) & 0xFF;
	cipher[ 5] = (this->B >> 8) & 0xFF;
	cipher[ 6] = (this->B >> 16) & 0xFF;
	cipher[ 7] = (this->B >> 24) & 0xFF;

	cipher[ 8] = (this->C >> 0) & 0xFF;
	cipher[ 9] = (this->C >> 8) & 0xFF;
	cipher[10] = (this->C >> 16) & 0xFF;
	cipher[11] = (this->C >> 24) & 0xFF;

	cipher[12] = (this->D >> 0) & 0xFF;
	cipher[13] = (this->D >> 8) & 0xFF;
	cipher[14] = (this->D >> 16) & 0xFF;
	cipher[15] = (this->D >> 24) & 0xFF;
	
}