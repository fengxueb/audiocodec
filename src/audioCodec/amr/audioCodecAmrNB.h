#ifndef AUDIOCODECAMRNB_H
#define AUDIOCODECAMRNB_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "audioCodec/audioCodecBase.h"
#include "amr/include/opencore-amrnb/interf_enc.h"
#include "amr/include/opencore-amrnb/interf_dec.h"
namespace audioCodec
{

	class audioCodecAmrNB :public audioCodecBase
	{
	public:
		audioCodecAmrNB();
		~audioCodecAmrNB();

		audioCodecAmrNB* create();
		void codec(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen);
		void decode(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen);

	private:
		int amrFileOpen(std::string& filePath);
		int amrNBEncoderInit();
		int amrNBEncoderUninit();
		int getAMRFrameSize(Mode nMode);

		int amrNBDecoderInit();
		int amrNBDecoderUninit();


	private:
		FILE* fileIn;
		Mode fileMode;
		void *amrNBDec;
		void *amrNBCodec;
		

	};


}
#endif // !AUDIOCODECAMRNB_H
