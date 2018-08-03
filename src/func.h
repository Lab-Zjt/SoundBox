#ifndef WAVPARSER_FUNC_H
#define WAVPARSER_FUNC_H

namespace audio {
  class s16PCMFrame;
}
//function format:
typedef void (*transform_func_t)(audio::s16PCMFrame *);
void sin_cos(audio::s16PCMFrame *);
void bit8(audio::s16PCMFrame *);
void leftBlock(audio::s16PCMFrame *);
void rightBlock(audio::s16PCMFrame *);
void depart(audio::s16PCMFrame *);
#endif