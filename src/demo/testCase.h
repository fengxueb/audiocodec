
#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>

int testAudioCodecSpeex();
int testSpeexEncWb(int argc, char **argv);
int testAmr2Wave(std::string& amrFile, std::string& waveFile);

#endif // !TEST_CASE_H
