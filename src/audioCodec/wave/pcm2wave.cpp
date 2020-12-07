#include <stdio.h>
#include "util/util.h"
#include "errorCode/errorcode.h"
#include "audioCodec/wave/wavreader.h"
#include "audioCodec/wave/wavwriter.h"
#include "audioCodec/wave/pcm2wave.h"

namespace audioCodec 
{
	int pcm2wave(std::string pcmFileName, int pcmSampleRate, int pcmBitPerSample, int channels,std::string waveFileName)
	{
		int fileLen = 0;
		const int writeStep = 1024;
		int leftSize = 0;
		unsigned char buf[1024] = {0};
		if (pcmFileName == "" || pcmFileName.c_str() == nullptr
			|| waveFileName == "" || waveFileName.c_str() == nullptr)
		{
			return ERROR_INPUT_RESOURCE_PATH;
		} 
		FILE *fp = fopen(pcmFileName.c_str(),"rb");
		if (fp == nullptr)
		{
			return ERROR_OPEN_RESOURCE;
		}
		fseek(fp,0,SEEK_END);
		fileLen = ftell(fp);
		rewind(fp);

		void* wav = wav_write_open(waveFileName.c_str(), pcmSampleRate, pcmBitPerSample, channels);

		leftSize = fileLen;
		while (leftSize > 0)
		{
			int readSize = 0;
			readSize = fread(buf, writeStep,1, fp);
			wav_write_data(wav, buf, readSize);
			leftSize -= readSize;
		}

		fclose(fp);
		wav_write_close(wav);
	}

	int wave2pcm(std::string pcmFileName, int &pcmSampleRate, int& pcmBitPerSample, int& channels, std::string waveFileName) 
	{
		int formate;
		unsigned int waveDataLength;
		const int readStep = 1024;
		unsigned char buf[1024] = { 0 };
		if (pcmFileName == "" || pcmFileName.c_str() == nullptr
			|| waveFileName == "" || waveFileName.c_str() == nullptr)
		{
			return ERROR_INPUT_RESOURCE_PATH;
		}
		FILE *fp = fopen(pcmFileName.c_str(), "rb");
		if (fp == nullptr)
		{
			return ERROR_OPEN_RESOURCE;
		}

		void* wav = wav_read_open(waveFileName.c_str());
		wav_get_header(wav,&formate, &channels, &pcmSampleRate, &pcmBitPerSample,&waveDataLength);

		while (waveDataLength >0)
		{
			int readSize = 0;
			readSize = wav_read_data(wav, buf, readStep);
			fwrite(buf, readSize,1, fp);
			waveDataLength -= readSize;
		}
		wav_read_close(wav);
		fclose(fp);
	}
}
