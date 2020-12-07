/**
 * @Description: this file contains some common audio codec algorithm
 * @Author: xbfeng
 * @Date: 2020-09-21 16:09:00
 * @LastEditTime: 2020-09-21 16:09:00
 * @LastEditors: xbfeng
 * @declaration: All right reserved
 */

#ifndef PCM2WAVE_H
#define PCM2WAVE_H

#include <iostream>
#include <string.h>

namespace audioCodec 
{
	struct pcmParams 
	{
		int sampleRate;
		int bitPerSample;
		int channels;
	};


	void pcmResample();

	/**
	* @method: pcm2wave,this function can transfer a pcm file to wave formate
	* @param  params type | parameter name | parameter statement
	* @param  pcmParams   | inputParams    | input pcm audio codec information,it's necessary to deal with pcm audio
	* @return void
	*/
	int pcm2wave(std::string pcmFileName, int pcmSampleRate,int pcmBitPerSample,int channels, std::string waveFileName);
	int wave2pcm(std::string pcmFileName, int &pcmSampleRate, int& pcmBitPerSample, int& channels, std::string waveFileName);
}


#endif // !PCM2WAVE_H



