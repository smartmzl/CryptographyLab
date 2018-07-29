/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#pragma once

class hash_test_tool
{
public:

	// ����ģʽ
	static hash_test_tool* create();
	void destroy();
	hash_test_tool();
	~hash_test_tool();

	// �����ٶȲ���
	void run_speed(char* engine, char* str_length, char* repeat_times);

	// ������ȷ�Բ���
	void run_validity(char* range_start, char* range_end);

private:

};

