/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#include "stdafx.h"
#include <string.h>
#include "md5_standard.h"

unsigned char PADDING[] = {
	0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

// 创建md5对象
md5_standard* md5_standard::create() {
	// 创建对象
	md5_standard *obj = new md5_standard();
	return obj;
}
void md5_standard::destroy() {
	delete this;
}
md5_standard::md5_standard() {

}
md5_standard::~md5_standard() {

}

// 对字符串进行加密
void md5_standard::md5_str(const char cstr[], char *cipher) {
	// 初始化上下文结构体，用于存储状态信息
	// CTX = context
	MD5_CTX md5;
	this->MD5Init(&md5);

	// 加密内容
	unsigned char *plain_text  = (unsigned char*)cstr;
	unsigned char cipher_[16];

	// 处理明文，分为两种情况
	// 1. 输入的明文至少可以组成一个完整的512bit分组：
	//    把前面完整的分组进行Hmd5处理，最后剩余的数据项留在MD5Final中处理。
	// 2. 输入的明文长度不足以组成一个完整的512bit分组：
	//    把整个明文留在MD5Final中处理。
	this->MD5Update(&md5, plain_text, strlen((char *)plain_text));
	// 处理明文中剩余的部分
	// 增加padding
	this->MD5Final(&md5, cipher_);
	// 加密完成
	for (int i = 0; i<16; i++)
	{
		sprintf_s(cipher + i * 2, 4, "%02x", cipher_[i]);
	}
	
}

void md5_standard::MD5Init(MD5_CTX *context)
{
	// 分组计数器，两个int可以组合成64bit
	// count[0]代表低32位，count[1]代表高32位
	context->count[0] = 0;
	context->count[1] = 0;
	// 四个缓存器的初始值
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
}

void md5_standard::MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen)
{

	// index是
	unsigned int i = 0, index = 0, partlen = 0;

	// 把count[0]右移3位相当于整除8，相当于把位转换成字节。
	// 与0x3F = bin(0011,1111)求按位与，相当于只保留低6位，因此范围在0~63之间。
	// 最终效果：把count[0]的单位转换成字节，再按分组字节大小64取余。
	// 一般情况下，初始化值为0。
	// 具体解释一下，index即为当前进行到的那一个字节，在这个字节所在的分组中的索引值。
	index = (context->count[0] >> 3) & 0x3F;

	// 计算还应该补充多少个字节
	// 这里填充指的是从input中*继续*取多少个字节进行填充，
	// 以完成当前这个分组。
	partlen = 64 - index;

	// inputlen是输入的字节长度，在这里转换成位长度，加至count[0]中
	context->count[0] += inputlen << 3;
	// 下面的if是用来判断溢出的，这是判断溢出的通式，
	// 并且，如果溢出则在高位+1，相当于进位
	if (context->count[0] < (inputlen << 3)) {
		context->count[1]++;
	}

	// 这里为什么是右移29位呢？
	// 因为右移32位转换到高字节以后，还需要左移三位转换位bit
	context->count[1] += inputlen >> 29;

	// 如果现在输入的数据，足够填充完一个分组，
	// 前面已经说了，partlen的含义。
	if (inputlen >= partlen) {
		// 解区输入数据，复制到缓存的后面，作为填充
		// 缓存的前面是上一次剩下的
		memcpy(&context->buffer[index], input, partlen);
		// 填充完成后，代表当前这个分组刚好有64字节，可以使用压缩函数对这个分组进行压缩了
		this->MD5Transform(context->state, context->buffer);
		// 从最后处理的地方从partlen开始，为什么呢？
		// 因为当前输入的input中，partlen之前的数据已经被使用过了。
		for (i = partlen; i + 64 <= inputlen; i += 64) {
			// 下一个分组的处理，input输入就是从i之后的数据开始了。
			this->MD5Transform(context->state, &input[i]);
		}
		// 因此现在正好处理完一个分组
		index = 0;
	}
	else {
		// 由于现在input中所剩的数据已经不够一个分组了，
		// 因此还不能进行处理。
		i = 0;
	}

	// 把input后面不够一个分组的数据复制到buffer后面链接起来，
	// 用于以后处理。
	memcpy(&context->buffer[index], &input[i], inputlen - i);
}

void md5_standard::MD5Final(MD5_CTX *context, unsigned char digest[16])
{
	unsigned int index = 0, padlen = 0;
	unsigned char bits[8];

	// 这里的index与上面意义
	// 即为当前进行到的那一个字节，在这个字节所在的分组中的索引值。
	index = (context->count[0] >> 3) & 0x3F;

	// 计算内容填充的长度，这里分为两种情况：
	// 1. index <  56，即当前分组中还有8个以上的字节可以用于计算。
	// 2. index >= 56，剩余空间小于等于8，则还需要增加一个分组，
	//    因此padlen = 56+64-index = 120-index
	padlen = (index < 56) ? (56 - index) : (120 - index);

	// 计算带明文数据的长度，保存到bits中，作为长度填充的数据。
	// 注意，这里的长度是不包括任何填充的明文长度。
	this->MD5Encode(bits, context->count, 8);

	// 添加内容填充
	this->MD5Update(context, PADDING, padlen);

	// 长度填充
	this->MD5Update(context, bits, 8);

	// 开始加密
	this->MD5Encode(digest, context->state, 16);
}

// output是字符型，input是整型
// 含义是将整形数值转换为字符型。
// 这里的len的单位为字节。
void md5_standard::MD5Encode(unsigned char *output, unsigned int *input, unsigned int len) {
	// input为一个数组，这里的长度为8个字节
	unsigned int i = 0, j = 0;
	// 可以看出每次操作4个字节，32bit
	while (j < len) {
		// 下面分别是处理input中的第4到第1个字节
		// 和0xFF相当于保留input[i]中的前8个bit，而后面的置零
		// 然后把这8为存储到output的一个元素中，每个元素8bit
		// 这里是低位有限还是高位优先呢？
		output[j] = input[i] & 0xFF;
		output[j + 1] = (input[i] >> 8) & 0xFF;
		output[j + 2] = (input[i] >> 16) & 0xFF;
		output[j + 3] = (input[i] >> 24) & 0xFF;
		i++;
		j += 4;
	}
}

// 将字符型的input，转换成整型的output
// 正好和MD5Encode相反嘛。
void md5_standard::MD5Decode(unsigned int *output, unsigned char *input, unsigned int len) {
	unsigned int i = 0, j = 0;
	while (j < len) {
		output[i] =
			(input[j]) |
			(input[j + 1] << 8) |
			(input[j + 2] << 16) |
			(input[j + 3] << 24);
		i++;
		j += 4;
	}
}

// 这里的block是需要处理的512bit的分组
void md5_standard::MD5Transform(unsigned int state[4], unsigned char block[64])
{
	// 这里的a,b,c,d分别是缓存器A,B,C,D中的值，
	// 在这里作为临时变量等待处理。
	unsigned int a = state[0];
	unsigned int b = state[1];
	unsigned int c = state[2];
	unsigned int d = state[3];

	// 这里的x是子分组，
	unsigned int x[64];

	this->MD5Decode(x, block, 64);

	/* Round 1 */
	FF(a, b, c, d, x[0], 7, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[1], 12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[2], 17, 0x242070db); /* 3 */
	FF(b, c, d, a, x[3], 22, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[4], 7, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[5], 12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[6], 17, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[7], 22, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[8], 7, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[9], 12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

										   /* Round 2 */
	GG(a, b, c, d, x[1], 5, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[6], 9, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[5], 5, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], 9, 0x02441453); /* 22 */
	GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[4], 20, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[9], 5, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[3], 14, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[8], 20, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[2], 9, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[7], 14, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

										   /* Round 3 */
	HH(a, b, c, d, x[5], 4, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[8], 11, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[1], 4, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[4], 11, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[7], 16, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[0], 11, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[3], 16, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[6], 23, 0x04881d05); /* 44 */
	HH(a, b, c, d, x[9], 4, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[2], 23, 0xc4ac5665); /* 48 */

										  /* Round 4 */
	II(a, b, c, d, x[0], 6, 0xf4292244); /* 49 */
	II(d, a, b, c, x[7], 10, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[5], 21, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[3], 10, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[1], 21, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[8], 6, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[6], 15, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[4], 6, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[2], 15, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[9], 21, 0xeb86d391); /* 64 */

										  // 加回去
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}