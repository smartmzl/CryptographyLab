/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>

#include "large_number_calculation.h"

int main(int argc, char *argv[])
{

	auto lnc = large_number_calculation::create();
	lnc->inputHex(0, "A1B2C3D4");
	lnc->inputHex(1, "A1B2C3D4");
	lnc->runAdd();
	lnc->getValue(2);

	system("pause");

    return 0;
	
}