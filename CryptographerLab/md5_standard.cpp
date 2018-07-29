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

// ����md5����
md5_standard* md5_standard::create() {
	// ��������
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

// ���ַ������м���
void md5_standard::md5_str(const char cstr[], char *cipher) {
	// ��ʼ�������Ľṹ�壬���ڴ洢״̬��Ϣ
	// CTX = context
	MD5_CTX md5;
	this->MD5Init(&md5);

	// ��������
	unsigned char *plain_text  = (unsigned char*)cstr;
	unsigned char cipher_[16];

	// �������ģ���Ϊ�������
	// 1. ������������ٿ������һ��������512bit���飺
	//    ��ǰ�������ķ������Hmd5�������ʣ�������������MD5Final�д���
	// 2. ��������ĳ��Ȳ��������һ��������512bit���飺
	//    ��������������MD5Final�д���
	this->MD5Update(&md5, plain_text, strlen((char *)plain_text));
	// ����������ʣ��Ĳ���
	// ����padding
	this->MD5Final(&md5, cipher_);
	// �������
	for (int i = 0; i<16; i++)
	{
		sprintf_s(cipher + i * 2, 4, "%02x", cipher_[i]);
	}
	
}

void md5_standard::MD5Init(MD5_CTX *context)
{
	// ���������������int������ϳ�64bit
	// count[0]�����32λ��count[1]�����32λ
	context->count[0] = 0;
	context->count[1] = 0;
	// �ĸ��������ĳ�ʼֵ
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
}

void md5_standard::MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen)
{

	// index��
	unsigned int i = 0, index = 0, partlen = 0;

	// ��count[0]����3λ�൱������8���൱�ڰ�λת�����ֽڡ�
	// ��0x3F = bin(0011,1111)��λ�룬�൱��ֻ������6λ����˷�Χ��0~63֮�䡣
	// ����Ч������count[0]�ĵ�λת�����ֽڣ��ٰ������ֽڴ�С64ȡ�ࡣ
	// һ������£���ʼ��ֵΪ0��
	// �������һ�£�index��Ϊ��ǰ���е�����һ���ֽڣ�������ֽ����ڵķ����е�����ֵ��
	index = (context->count[0] >> 3) & 0x3F;

	// ���㻹Ӧ�ò�����ٸ��ֽ�
	// �������ָ���Ǵ�input��*����*ȡ���ٸ��ֽڽ�����䣬
	// ����ɵ�ǰ������顣
	partlen = 64 - index;

	// inputlen��������ֽڳ��ȣ�������ת����λ���ȣ�����count[0]��
	context->count[0] += inputlen << 3;
	// �����if�������ж�����ģ������ж������ͨʽ��
	// ���ң����������ڸ�λ+1���൱�ڽ�λ
	if (context->count[0] < (inputlen << 3)) {
		context->count[1]++;
	}

	// ����Ϊʲô������29λ�أ�
	// ��Ϊ����32λת�������ֽ��Ժ󣬻���Ҫ������λת��λbit
	context->count[1] += inputlen >> 29;

	// ���������������ݣ��㹻�����һ�����飬
	// ǰ���Ѿ�˵�ˣ�partlen�ĺ��塣
	if (inputlen >= partlen) {
		// �����������ݣ����Ƶ�����ĺ��棬��Ϊ���
		// �����ǰ������һ��ʣ�µ�
		memcpy(&context->buffer[index], input, partlen);
		// �����ɺ󣬴���ǰ�������պ���64�ֽڣ�����ʹ��ѹ������������������ѹ����
		this->MD5Transform(context->state, context->buffer);
		// �������ĵط���partlen��ʼ��Ϊʲô�أ�
		// ��Ϊ��ǰ�����input�У�partlen֮ǰ�������Ѿ���ʹ�ù��ˡ�
		for (i = partlen; i + 64 <= inputlen; i += 64) {
			// ��һ������Ĵ���input������Ǵ�i֮������ݿ�ʼ�ˡ�
			this->MD5Transform(context->state, &input[i]);
		}
		// ����������ô�����һ������
		index = 0;
	}
	else {
		// ��������input����ʣ�������Ѿ�����һ�������ˣ�
		// ��˻����ܽ��д���
		i = 0;
	}

	// ��input���治��һ����������ݸ��Ƶ�buffer��������������
	// �����Ժ���
	memcpy(&context->buffer[index], &input[i], inputlen - i);
}

void md5_standard::MD5Final(MD5_CTX *context, unsigned char digest[16])
{
	unsigned int index = 0, padlen = 0;
	unsigned char bits[8];

	// �����index����������
	// ��Ϊ��ǰ���е�����һ���ֽڣ�������ֽ����ڵķ����е�����ֵ��
	index = (context->count[0] >> 3) & 0x3F;

	// �����������ĳ��ȣ������Ϊ���������
	// 1. index <  56������ǰ�����л���8�����ϵ��ֽڿ������ڼ��㡣
	// 2. index >= 56��ʣ��ռ�С�ڵ���8������Ҫ����һ�����飬
	//    ���padlen = 56+64-index = 120-index
	padlen = (index < 56) ? (56 - index) : (120 - index);

	// ������������ݵĳ��ȣ����浽bits�У���Ϊ�����������ݡ�
	// ע�⣬����ĳ����ǲ������κ��������ĳ��ȡ�
	this->MD5Encode(bits, context->count, 8);

	// ����������
	this->MD5Update(context, PADDING, padlen);

	// �������
	this->MD5Update(context, bits, 8);

	// ��ʼ����
	this->MD5Encode(digest, context->state, 16);
}

// output���ַ��ͣ�input������
// �����ǽ�������ֵת��Ϊ�ַ��͡�
// �����len�ĵ�λΪ�ֽڡ�
void md5_standard::MD5Encode(unsigned char *output, unsigned int *input, unsigned int len) {
	// inputΪһ�����飬����ĳ���Ϊ8���ֽ�
	unsigned int i = 0, j = 0;
	// ���Կ���ÿ�β���4���ֽڣ�32bit
	while (j < len) {
		// ����ֱ��Ǵ���input�еĵ�4����1���ֽ�
		// ��0xFF�൱�ڱ���input[i]�е�ǰ8��bit�������������
		// Ȼ�����8Ϊ�洢��output��һ��Ԫ���У�ÿ��Ԫ��8bit
		// �����ǵ�λ���޻��Ǹ�λ�����أ�
		output[j] = input[i] & 0xFF;
		output[j + 1] = (input[i] >> 8) & 0xFF;
		output[j + 2] = (input[i] >> 16) & 0xFF;
		output[j + 3] = (input[i] >> 24) & 0xFF;
		i++;
		j += 4;
	}
}

// ���ַ��͵�input��ת�������͵�output
// ���ú�MD5Encode�෴�
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

// �����block����Ҫ�����512bit�ķ���
void md5_standard::MD5Transform(unsigned int state[4], unsigned char block[64])
{
	// �����a,b,c,d�ֱ��ǻ�����A,B,C,D�е�ֵ��
	// ��������Ϊ��ʱ�����ȴ�����
	unsigned int a = state[0];
	unsigned int b = state[1];
	unsigned int c = state[2];
	unsigned int d = state[3];

	// �����x���ӷ��飬
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

										  // �ӻ�ȥ
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}