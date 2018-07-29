/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

// ���ڴ洢��������Ϣ�Ľṹ��
typedef struct {
	unsigned int count[2]; // ���ȼ�������λ��
	unsigned int state[4]; // A,B,C,D�ĸ�������
	unsigned char buffer[64]; // һ��512bit�ķ���
}MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))  
#define G(x,y,z) ((x & z) | (y & ~z))  
#define H(x,y,z) (x^y^z)  
#define I(x,y,z) (y ^ (x | ~z)) 

// ѭ������
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n))) 

// FF,GG,HH,II ���ĸ������ǽ�һ��hmd5��������˵�
// ���ҷֱ����һ������4�ִ����е�1��
#define FF(a,b,c,d,x,s,ac) \
{ \
    a += F(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}

#define GG(a,b,c,d,x,s,ac) \
{ \
    a += G(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}

#define HH(a,b,c,d,x,s,ac) \
{ \
    a += H(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}

#define II(a,b,c,d,x,s,ac) \
{ \
    a += I(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}

class md5_standard
{
public:
	// ����ģʽ
	static md5_standard* create();
	void destroy();
	md5_standard();
	~md5_standard();

	// ���ַ������м���
	void md5_str(const char str[], char *cipher);

private:

	void MD5Init(MD5_CTX *context);
	void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
	void MD5Final(MD5_CTX *context, unsigned char digest[16]);
	void MD5Transform(unsigned int state[4], unsigned char block[64]);
	void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len);
	void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len);

};

