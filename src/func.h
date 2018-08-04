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
void consecutive(audio::s16PCMFrame *);
void switch_lr(audio::s16PCMFrame *);
[[gnu::unused]]void dumb(audio::s16PCMFrame *);
void volume_adjust(audio::s16PCMFrame *frame, double left_adjust, double right_adjust);
void sound_mix(audio::s16PCMFrame *frame, audio::s16PCMFrame *another_frame);
#endif