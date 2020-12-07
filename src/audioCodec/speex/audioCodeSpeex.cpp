#include <new>
#include <string.h>
#include "audioCodecSpeex.h"
#include "errorCode\errorcode.h"

namespace audioCodec
{
    audioCodecSpeex::audioCodecSpeex(SpeexBits* bits, void* encState, int encSize, int sampleRate, int quality)
    {

    }

	audioCodecSpeex::~audioCodecSpeex() {}
    
    audioCodecSpeex* audioCodecSpeex::create(int sampleRate, int quality, int& errorCode)
    {
        SpeexBits* bits;
        audioCodecSpeex* pSpeex =nullptr;
        void* encState = nullptr;
        int modeID;
        int encFrameSize;
        int ret =AUDIO_CODEC_SUCCESS;

        do{
            switch (sampleRate)
            {
            case AUDIO_SAMPLE_RATE_NB:
            modeID = SPEEX_MODEID_NB;
                break;

            case AUDIO_SAMPLE_RATE_WB:
            modeID = SPEEX_MODEID_WB;
                break;

            case AUDIO_SAMPLE_RATE_UWB:
            modeID = SPEEX_MODEID_UWB;
                break;
            
            default:
                ret = ERROR_SPEEX_SAMPLETARE;
                break;
            }

            if(ret != AUDIO_CODEC_SUCCESS)  
                break;
            
            bits = (SpeexBits*)malloc(sizeof(SpeexBits));
            if(bits == nullptr){ret = ERROR_SPEEX_MALLOC_MEM;break;}
            speex_bits_init(bits);
            //initialize encoder
            encState = speex_encoder_init(speex_lib_get_mode(modeID));
            if(encState == nullptr)
            {
                ret = ERROR_SPEEX_ENCODER_INIT;
                break;
            }

            //set encoder quality
            speex_encoder_ctl(encState, SPEEX_SET_QUALITY, &quality);
            speex_encoder_ctl(encState, SPEEX_GET_FRAME_SIZE, &encFrameSize);
            encFrameSize *= sizeof(spx_int16_t);

            pSpeex = new (std::nothrow) audioCodecSpeex(bits, encState, encFrameSize, sampleRate, quality);
            if(pSpeex == nullptr)
            {
                ret = ERROR_SPEEX_NEW_ENCODER;
                break;
            }

        }while (0);

        if(ret != AUDIO_CODEC_SUCCESS)
        {
            //releaseResource();
            if(pSpeex != nullptr)
            {
                delete pSpeex;
                pSpeex = nullptr;
            }
        }
		return pSpeex;

    }

    void audioCodecSpeex::releaseResource()
    {
       if (mBitsEncode != nullptr)
        {
            speex_bits_destroy(mBitsEncode);
            mBitsEncode = nullptr;
        }
        if (mEncState != nullptr)
        {
            speex_encoder_destroy(mEncState);
            mEncState = nullptr;
        }
    }


    void audioCodecSpeex::codec(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)
    {
        int ret =0;
        int unEncodeLen = audioDataLen;
        int encodeWritenLen = 0;
        int writenLen = 0;
        char *writenLocation = outAudio;
        const int stepSize = 1024;
        char dataCash[stepSize] = {0};
        char writeCash[stepSize] = {0};

        while (encodeWritenLen >= unEncodeLen)
        {
            /* code */
            int writeBytes =0;
            speex_bits_reset(mBitsEncode);
            memcpy(dataCash,audioData+encodeWritenLen,stepSize);
            encodeWritenLen+=stepSize;

            speex_encode_int(mEncState, (spx_int16_t *)dataCash, mBitsEncode);
            writeBytes = speex_bits_write(mBitsEncode, writeCash, stepSize);
            memcpy(outAudio+writenLen,writeCash,writeBytes);
            writenLen +=writeBytes;
        }
    }

    void audioCodecSpeex::decode(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)
    {
        const int decodeStypeLen = 200;
    //    int unDecodeLen = audioDataLen;
    //    int outBuffer[160] = {0};
    //    int decodeLen = 0;
    //    while (unDecodeLen)
    //    {
    //        /* code */
    //        speex_bits_reset(mBitsDecode);
    //        speex_decoder_init(mEncState);
    //        if(unDecodeLen >decodeStypeLen){
    //            speex_bits_read_from(mBitsDecode, mBitsDecode+(audioDataLen-unDecodeLen), decodeStypeLen);
    //        }else{
    //            speex_bits_read_from(mBitsDecode,  mBitsDecode+(audioDataLen-unDecodeLen), unDecodeLen);
    //        }
    //        ret = speex_decode(mEncState,mBitsDecode,outBuffer);
    //        decodeLen+= ret;
    //        memcpy(outAudio+decodeLen,outBuffer,ret);  
    //    }
    //    outAudioLen = decodeLen;
    }

}
