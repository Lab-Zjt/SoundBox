#include <func.h>
#include <wav.h>
#include <cmath>

void sin_cos(audio::s16PCMFrame *frame) {
  static int loop = 0;
  for (int i = 0; i < 1024; ++i) {
    auto sum = frame->getLeftSoundTrackAt(i) + frame->getRightSoundTrackAt(i);
    frame->setLeftSoundTrackAt(i, static_cast<int16_t>(std::sin(static_cast<double>(loop) / 512) * sum / 2));
    frame->setRightSoundTrackAt(i, static_cast<int16_t>(std::cos(static_cast<double>(loop) / 512) * sum / 2));
  }
  ++loop;
};

void cut(audio::s16PCMFrame *frame, int from, int to) {

}