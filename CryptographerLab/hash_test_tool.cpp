/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "stdafx.h"
#include "string.h"
#include <time.h>
#include <cstdlib> 
#include <string>

#include "md5.h"
#include "md5_standard.h"
#include "hash_test_tool.h"

// 创建md5对象
hash_test_tool* hash_test_tool::create() {
	// 创建对象
	hash_test_tool *obj = new hash_test_tool();
	return obj;
}
void hash_test_tool::destroy() {
	delete this;
}

hash_test_tool::hash_test_tool()
{
}


hash_test_tool::~hash_test_tool()
{
}

void hash_test_tool::run_speed(char* engine, char* str_length, char* repeat_times) {

	int str_length_ = std::atoi(str_length);
	int repeat_times_ = std::atoi(repeat_times);

	float start, time_spent;
	char* plain_text = new char[str_length_];
	memset(plain_text, 65, str_length_);

	char *cipher = new char[32];

	// 开始计数
	start = (float)clock();

	// 根据引擎选择创建对象
	int engine_ = 1;
	if (strncmp(engine, "self", 4) == 0) {
		// 自主开发的md5算法
		md5* obj = md5::create();
		for (int i = 0; i < repeat_times_; i++)
		{
			obj->md5_str(plain_text, cipher);
		}
		obj->destroy();
		engine_ = 1;
	}
	else if (strncmp(engine, "std", 3) == 0) {
		// 标准md5算法
		md5_standard* obj = md5_standard::create();
		for (int i = 0; i < repeat_times_; i++)
		{
			obj->md5_str(plain_text, cipher);
		}
		obj->destroy();
		engine_ = 2;
	}

	time_spent = ((float)clock() - start) / 1000;
	printf("Spent %f s for %u times, %.02f times per second, length: %d, use %d engine.\n", time_spent, repeat_times_, (float)repeat_times_ / time_spent, str_length_, engine_);

}

void hash_test_tool::run_validity(char* range_start, char* range_end) {

	int range_start_ = std::atoi(range_start);
	int range_end_ = std::atoi(range_end);

	char *cipher_self = new char[32];
	char *cipher_std  = new char[32];
	
	int correct_count = 0;
	int wrong_count = 0;

	std::string plain_text;
	plain_text = "";
	for (int i = range_start_; i <= range_end_; ++i) {


		// 自主开发的md5算法
		md5* obj_self = md5::create();
		obj_self->md5_str(plain_text.c_str(), cipher_self);

		// 标准md5算法
		md5_standard* obj_stand = md5_standard::create();
		obj_stand->md5_str(plain_text.c_str(), cipher_std);

		// 比较
		if (strncmp(cipher_self, cipher_std, 32) != 0) {
			printf("Mismatching: %s, %s (%u).\n", cipher_self, cipher_std, plain_text.length());
			++wrong_count;
		}
		else {
			printf("Matching: %s, %s (%u).\n", cipher_self, cipher_std, plain_text.length());
			++correct_count;
		}
		
		obj_self->destroy();
		obj_stand->destroy();

		plain_text = plain_text + "A";

	}
	printf("Processing finished, correct: %u, wrong: %u.\n", correct_count, wrong_count);
}