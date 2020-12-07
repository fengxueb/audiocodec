#include "testCase.h"

#include <cstdio>
#include <stdio.h>
#include <string.h>
#define NSIZE  8

int main() 
{
	// test amr to wave
	std::string amrFile = "1_8k.amr";
	std::string waveFile = "1_8k.wave";
	testAmr2Wave(amrFile, waveFile);


	return 0;
}


