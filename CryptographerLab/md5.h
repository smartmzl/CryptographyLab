/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

// 定义好一些类型，使用再所有平台都一致的数据类型
typedef unsigned long long ULL;	// 64bits
typedef unsigned int  UI;		// 32bits
typedef unsigned short US;		// 16bits

// 对一些方法进行宏定义
#define ROUND_STEP(NCLS, NTBL, SUB_GROUP_ID, GFUNC, A, B, C, D) { \
	memcpy(&SUB_GROUP, data + start_byte + SUB_GROUP_ID * 4, 4); \
	A += NTBL + SUB_GROUP + GFUNC(B, C, D); \
	A = (A >> (32 - NCLS)) | (A << NCLS); \
	A += B; \
};

#define gF(b, c, d) ((b & c) | (~b & d))
#define gG(b, c, d) ((b & d) | (c & ~d)) 
#define gH(b, c, d) (b ^ c ^ d)
#define gI(b, c, d) (c ^ (b | ~d)) 


// md5 类
class md5{
public:

	// 工厂模式
	static md5* create();
	void destroy();
	md5();
	~md5();
	
	// 对字符串进行加密
	void md5_str(const char str[], char *cipher);

private:

	// A,B,C,D 四个缓存区
	UI A, B, C, D;

	// 输出字典
	const char Toutput[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	// 压缩函数
	bool Hmd5(const char *data, ULL group_num);

	// 输出最后的结果
	void md5_final(UI* cipher);


};



