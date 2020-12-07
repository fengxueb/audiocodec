#include "audioCodec/audioCodecBase.h"
#include "speex/inc/speex/speex.h"

#define AUDIO_SAMPLE_RATE_NB    8000
#define AUDIO_SAMPLE_RATE_WB    16000
#define AUDIO_SAMPLE_RATE_UWB   32000

namespace audioCodec
{
    
    class audioCodecSpeex:public audioCodecBase
    {
    public:
        audioCodecSpeex(SpeexBits* bits, void* encState, int encSize, int sampleRate, int quality);
        ~audioCodecSpeex();
        static audioCodecSpeex* create(int sample, int quality, int& errorCode);
        void codec(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen);
        void decode(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen);
        void destory();
    private:
        void releaseResource();
    private:
        SpeexBits* mBitsEncode;
        SpeexBits* mBitsDecode;
        void* mEncState;
    };
}