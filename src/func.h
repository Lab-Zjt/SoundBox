#ifndef WAVPARSER_FUNC_H
#define WAVPARSER_FUNC_H

namespace audio {
  class s16PCMFrame;
}
//function format:
typedef void (*transform_func_t)(audio::s16PCMFrame *);
void sin_cos(audio::s16PCMFrame *);

#endif