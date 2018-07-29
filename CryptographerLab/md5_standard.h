/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

// 用于存储上下文信息的结构体
typedef struct {
	unsigned int count[2]; // 长度计数（按位）
	unsigned int state[4]; // A,B,C,D四个缓存器
	unsigned char buffer[64]; // 一个512bit的分组
}MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))  
#define G(x,y,z) ((x & z) | (y & ~z))  
#define H(x,y,z) (x^y^z)  
#define I(x,y,z) (y ^ (x | ~z)) 

// 循环左移
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n))) 

// FF,GG,HH,II 这四个函数是将一个hmd5函数打包了的
// 并且分别代表一个分组4轮处理中的1轮
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
	// 工厂模式
	static md5_standard* create();
	void destroy();
	md5_standard();
	~md5_standard();

	// 对字符串进行加密
	void md5_str(const char str[], char *cipher);

private:

	void MD5Init(MD5_CTX *context);
	void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
	void MD5Final(MD5_CTX *context, unsigned char digest[16]);
	void MD5Transform(unsigned int state[4], unsigned char block[64]);
	void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len);
	void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len);

};

