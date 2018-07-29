/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

// �����һЩ���ͣ�ʹ��������ƽ̨��һ�µ���������
typedef unsigned long long ULL;	// 64bits
typedef unsigned int  UI;		// 32bits
typedef unsigned short US;		// 16bits

// ��һЩ�������к궨��
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


// md5 ��
class md5{
public:

	// ����ģʽ
	static md5* create();
	void destroy();
	md5();
	~md5();
	
	// ���ַ������м���
	void md5_str(const char str[], char *cipher);

private:

	// A,B,C,D �ĸ�������
	UI A, B, C, D;

	// ����ֵ�
	const char Toutput[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	// ѹ������
	bool Hmd5(const char *data, ULL group_num);

	// ������Ľ��
	void md5_final(UI* cipher);


};



