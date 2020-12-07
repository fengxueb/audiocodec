#include <stdlib.h>
#include <iostream>
#include "demo/testCase.h"
#include "audioCodec/speex/audioCodecSpeex.h"
#include "util/util.h"

const int READ_STEP = 1024;
using namespace cppBase;
int testAudioCodecSpeex() 
{
	int err = 0;
	std::string filePath = "";
	std::string outPath = " ";
	fileContent  fileRes;
	readFileResource(filePath.c_str(), fileRes);
	FILE* out = fopen(outPath.c_str(),"wb");

	audioCodec::audioCodecSpeex *codecPtr = audioCodec::audioCodecSpeex::create(16000,7,err);

	unsigned int remain = fileRes.uFileLen;
	unsigned int codecSize = 0;
	int encLen = 0;
	char outBuf[READ_STEP] = {0};
	unsigned int outLen;

	while (remain > 0)
	{
		if (remain < READ_STEP) 
		{
			encLen = remain;
		}
		else
		{
			encLen = READ_STEP;
		}
		codecPtr->codec(fileRes.pFile+ codecSize, encLen, outBuf, outLen);
		codecSize += encLen;
		fwrite(outBuf,1, outLen, out);
	}
	
	fclose(out);
	return 0;
}