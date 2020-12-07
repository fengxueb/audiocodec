#include "errorCode/errorcode.h"
#include "audioCodec/amr/audioCodecAmrNB.h"



namespace audioCodec
{
	static const int amrFrameRates[] = { 4750, 5150, 5900, 6700, 7400, 7950, 10200, 12200 };
	static const int amrFrameSizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };
	
	audioCodecAmrNB *audioCodecAmrNB::create()
	{
		return nullptr;
	}
	audioCodecAmrNB::audioCodecAmrNB():
		fileIn(nullptr),
		amrNBDec(nullptr)
	{
	}

	audioCodecAmrNB::~audioCodecAmrNB()
	{
	}
	
	int audioCodecAmrNB::amrFileOpen(std::string& filePath)
	{
		int n;
		char header[6];
		fileIn = fopen(filePath.c_str(), "rb");
		if(!fileIn)
		{
			return ERROR_AMR_OPEN_AMRFILE;
		}
		n = fread(header, 1, 6, fileIn);
		if (n != 6 || memcmp(header, "#!AMR\n", 6))
		{
			return ERROR_AMR_BAD_HEADER;
		}

		//initialize decoder interface
		int ret = amrNBDecoderInit();
		if (ret != AUDIO_CODEC_SUCCESS) return ret;

		return AUDIO_CODEC_SUCCESS;
	}

	int amrNBEncoderInit()
	{
		return 0;
	}

	int audioCodecAmrNB::amrNBDecoderInit()
	{
		amrNBDec = Decoder_Interface_init();
		if (amrNBDec != nullptr) 
		{
			return 	ERROR_AMR_INIT_CODECER;
		}
		return AUDIO_CODEC_SUCCESS;
	}

	
	int audioCodecAmrNB::getAMRFrameSize(Mode nMode)
	{
		return amrFrameSizes[(int)nMode];
	}

	void audioCodecAmrNB::codec(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)
	{

	}
	void audioCodecAmrNB::decode(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)
	{
		
	}
}
