namespace audioCodec
{
    enum audioCodecType
    {
        CODEC_TYPE_OPUS,
        CODEC_TYPE_OPUS_WEB,
        CODEC_TYPE_SPEEX,
        CODEC_TYPE_SPEEX_WEB,
		CODEC_TYPE_AMR_NB,
		CODEC_TYPE_AMR_WB
    };

    class audioCodecBase
    {
    public:
        audioCodecBase(/* args */);
        ~audioCodecBase();
        void createEncoder();
        void destoryEncoder();

        virtual void codec(const char* audioData, unsigned int audioDataLen, char* outAudio, unsigned int& outAudioLen)=0;
        //virtual void decode(char *input,int inlen,char *output,int* outlen)=0;
    private:
        /* data */


    protected:
        audioCodecType mCodecType;

    };
    
}