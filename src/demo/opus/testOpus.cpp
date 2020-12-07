//
#include <string>
#include <iostream>
#include "opus\include\opus.h"
#include "errorCode\errorcode.h"


#pragma comment(lib, "libopus.dll.a")
#define MAX_COM_FRAME_BYTES 1500

int opusEncode(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)
{
	int ret = 0;
	const char* pAudio = audioData;
	char* pOpusAudio = outAudio;
	unsigned int opusBufLen = outAudioLen;
	unsigned int audioRemaining = audioDataLen;
	unsigned int opusDataLen = 0;
	char tmpOutAudioData[MAX_COM_FRAME_BYTES] = { 0 };

	while (audioRemaining + mDataCacheLen >= mFrameSize)
	{
		char ch1, ch2;
		int encodedBytes = 0;
		unsigned int copyLen = mFrameSize - mDataCacheLen;

		std::memcpy(mDataCache + mDataCacheLen, pAudio, copyLen);
		mDataCacheLen += copyLen;
		pAudio += copyLen;
		audioRemaining -= copyLen;

		opus_encoder_ctl(mpEncoder, OPUS_SET_BITRATE(mBitRate));
		encodedBytes = opus_encode(mpEncoder, (const opus_int16*)mDataCache, mFrameSize / 2, (unsigned char*)tmpOutAudioData, MAX_COM_FRAME_BYTES);
		if (encodedBytes <= 0)
		{
			ret = AIKIT_FAILED;
			break;
		}

		ch1 = (encodedBytes & 0xFF00) >> 8;
		ch2 = encodedBytes & 0x00FF;
		if ((opusDataLen + encodedBytes + 2) <= opusBufLen)
		{
			std::memcpy(pOpusAudio + 2, tmpOutAudioData, encodedBytes);
			pOpusAudio[0] = ch1;
			pOpusAudio[1] = ch2;
			pOpusAudio += (encodedBytes + 2);
			opusDataLen += (encodedBytes + 2);
			mDataCacheLen = 0;
		}
		else
		{
			ret = AIKIT_ERROR_NO_ENOUGH_BUFFER;
			break;
		}
	}

	if (ret == 0 && audioRemaining != 0)
	{
		std::memcpy(mDataCache + mDataCacheLen, pAudio, audioRemaining);
		mDataCacheLen += audioRemaining;
	}

	outAudioLen = opusDataLen;

	return ret;
}



int testOpusCodec(int sampleRate,int channels,int quanity,int bitrate)
{
	int err;
	OpusEncoder *enc = NULL;
	int encFrameSize = 0;
	int application = OPUS_APPLICATION_VOIP;

	if (sampleRate != 8000 && sampleRate != 12000
		&& sampleRate != 16000 && sampleRate != 24000
		&& sampleRate != 48000) 
	{
		return ERROR_OPUS_SAMPLERATE;
	}

	if (channels < 1 || channels > 2)
	{
		return ERROR_OPUS_CHANNELS;
	}

	enc = opus_encoder_create(sampleRate, channels, application, &err);
	if (err != OPUS_OK) 
	{
		std::cout << "Cannot create encoder:" << opus_strerror(err) << std::endl;
		return ERROR_OPUS_CREATE_ENCODER;
	}

	// set opus parameters
	opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(quanity));
	opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
	opus_encoder_ctl(enc, OPUS_SET_VBR(0));
	opus_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));

	// 20ms 16bit(2Byte) samplete
	encFrameSize = 20 * 2 * sampleRate / 1000;

}

int testOpusDecode() 
{
	return false;
}

