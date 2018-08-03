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

void bit8(audio::s16PCMFrame *frame) {
  auto f = [](int16_t i) -> int16_t {
    auto r = static_cast<double >(i);
    r = std::abs(r);
    r = std::sqrt(r);
    r *= 128;
    return static_cast<int16_t>(r);
  };
  for (int i = 0; i < 1024; ++i) {
    frame->setLeftSoundTrackAt(i, f(frame->getLeftSoundTrackAt(i)));
    frame->setRightSoundTrackAt(i, f(frame->getRightSoundTrackAt(i)));
  }
}
void leftBlock(audio::s16PCMFrame *frame) {
  for (int i = 0; i < 1024; ++i) {
    frame->setLeftSoundTrackAt(i, 0);
  }
}
void rightBlock(audio::s16PCMFrame *frame) {
  for (int i = 0; i < 1024; ++i) {
    frame->setRightSoundTrackAt(i, 0);
  }
}
void depart(audio::s16PCMFrame *frame) {
  auto lf = [](int16_t i) -> int16_t {
    static int16_t prev = 0;
    auto save = i;
    i = i / 2 + prev / 2;
    prev = save;
    return i;
  };
  auto rf = [](int16_t i) -> int16_t {
    static int16_t prev = 0;
    auto save = i;
    i = i / 2 + prev / 2;
    prev = save;
    return i;
  };
  for (int i = 0; i < 1024; ++i) {
    auto l = frame->getLeftSoundTrackAt(i);
    auto r = frame->getRightSoundTrackAt(i);
    frame->setLeftSoundTrackAt(i, lf(l));
    frame->setRightSoundTrackAt(i, lf(r));
  }
}