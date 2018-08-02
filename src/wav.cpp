#include <wav.h>

#include <cmath>

namespace audio {
  double getSin(double off, int cycle) {
    return (std::sin(off / cycle * pi));
  }
  double getCos(double off, int cycle) {
    return (std::cos(off / cycle * pi));
  }
  void wavPCMs16FrameTransform(s16PCMFrame *frame, int off) {
    int cycle = 640;
    for (int i = 0; i < 1024; i++) {
      int32_t sum = frame->getLeftSoundTrackAt(i) + frame->getRightSoundTrackAt(i);
      frame->setLeftSoundTrackAt(i, int16_t(double(sum) * getSin(off, cycle) / 2));
      frame->setRightSoundTrackAt(i, int16_t(double(sum) * getCos(off, cycle) / 2));
    }
  }
}
