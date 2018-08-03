#ifndef SAMPLE_TRANSFORM_H
#define SAMPLE_TRANSFORM_H

#include <string>

void SoundEffectsTransform1(const std::string &input, const std::string &output);
void SoundCut(const std::string &input, const std::string &output, int from, int to);
void SoundMerge(const std::string &input1, const std::string &input2, const std::string &output);

#endif
