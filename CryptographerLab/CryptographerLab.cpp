/*
CryptographerLab
Created by Mengzelin 2018
For the purpose of practical learning & practical using.
Please visit https://smartmzl.github.io/
*/
#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#include "large_number_calculation.h"

int main(int argc, char *argv[])
{

	auto lnc = large_number_calculation::create();
	lnc->inputHex(0, "DFFAD52156156415‬4D5DB785DDBC20C3");

    return 0;
	
}