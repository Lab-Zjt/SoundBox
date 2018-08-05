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
void roate(audio::s16PCMFrame *);
void dumb(audio::s16PCMFrame *);
void volume_adjust(audio::s16PCMFrame *frame);
void sound_mix(audio::s16PCMFrame *frame, audio::s16PCMFrame *another_frame);

void func_merage_complex(audio::s16PCMFrame *frame, audio::s16PCMFrame *frame_background);
void get_accompany(audio::s16PCMFrame *frame);
void get_vocal(audio::s16PCMFrame *frame);

#endif