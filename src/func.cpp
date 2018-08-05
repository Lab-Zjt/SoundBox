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
void consecutive(audio::s16PCMFrame *frame) {
  auto lf = [](int16_t i) -> int16_t {
    static int16_t prev = 0;
    auto save = i;
    i = static_cast<int16_t >(i / 2 + prev / 2);
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
[[gnu::unused]]void dumb(audio::s16PCMFrame *frame) {
  static int loop = 0;
  for (int i = 0; i < 1024; ++i) {
    if (abs(frame->getLeftSoundTrackAt(i)) > INT16_MAX / 5)
      frame->setLeftSoundTrackAt(i, 0);
    if (abs(frame->getRightSoundTrackAt(i)) > INT16_MAX / 5)
      frame->setRightSoundTrackAt(i, 0);
  }
  ++loop;
}
/*void volume_adjust(audio::s16PCMFrame *frame, double left_adjust, double right_adjust) {
  for (int i = 0; i < 1024; i++) {
    int32_t adjust;
    adjust = static_cast<int32_t>(frame->getLeftSoundTrackAt(i) * left_adjust);
    if (adjust > INT16_MAX)
      adjust = INT16_MAX;
    if (adjust < INT16_MIN)
      adjust = INT16_MIN;
    frame->setLeftSoundTrackAt(i, static_cast<int16_t>(adjust));
    adjust = static_cast<int32_t>(frame->getRightSoundTrackAt(i) * right_adjust);
    if (adjust > INT16_MAX)
      adjust = INT16_MAX;
    if (adjust < INT16_MIN)
      adjust = INT16_MIN;
    frame->setRightSoundTrackAt(i, static_cast<int16_t>(adjust));
  }
}*/
void volume_adjust(audio::s16PCMFrame *frame,double left_adjust,double right_adjust)
{
    double factor = 1;
    for (int i = 0; i < 1024;i++)
    {
        int32_t adjust;
        adjust = static_cast<int32_t>( frame->getLeftSoundTrackAt(i)*left_adjust  * factor);
        if(adjust > INT16_MAX)
        {
            factor = INT16_MAX / static_cast<double>(adjust);
            adjust = INT16_MAX;
        }
        if(adjust < INT16_MIN)
        {
            factor = INT16_MIN / static_cast<double>(adjust);
            adjust = INT16_MIN;
        }
        frame->setLeftSoundTrackAt(i,static_cast<int16_t>(adjust));
        if(factor < 1)
            factor += (1 - factor) / static_cast<double>(8);
           
        adjust = static_cast<int32_t>( frame->getRightSoundTrackAt(i) * right_adjust * factor);
        if(adjust > INT16_MAX)
        {
            factor = INT16_MAX / static_cast<double>(adjust);
            adjust = INT16_MAX;
        }
        if(adjust < INT16_MIN)
        {
            factor = INT16_MIN / static_cast<double>(adjust);
            adjust = INT16_MIN;
        }
        frame->setRightSoundTrackAt(i,static_cast<int16_t>(adjust));
        if(factor < 1)
            factor += (1 - factor) / static_cast<double>(8);
    }
}

void sound_mix(audio::s16PCMFrame *frame, audio::s16PCMFrame *another_frame) {
  double factor = 1;
  for (int i = 0; i < 1024; i++) {
    int32_t adjust;
    adjust = static_cast<int32_t>((static_cast<int32_t>(frame->getLeftSoundTrackAt(i)) +
                                   static_cast<int32_t>(another_frame->getLeftSoundTrackAt(i))) * factor);
    if (adjust > INT16_MAX) {
      factor = INT16_MAX / static_cast<double>(adjust);
      adjust = INT16_MAX;
    }
    if (adjust < INT16_MIN) {
      factor = INT16_MIN / static_cast<double>(adjust);
      adjust = INT16_MIN;
    }
    frame->setLeftSoundTrackAt(i, static_cast<int16_t>(adjust));
    if (factor < 1)
      factor += (1 - factor) / static_cast<double>(8);
    
    adjust = static_cast<int32_t>((static_cast<int32_t>(frame->getRightSoundTrackAt(i)) +
                                   static_cast<int32_t>(another_frame->getRightSoundTrackAt(i))) * factor);
    if (adjust > INT16_MAX) {
      factor = INT16_MAX / static_cast<double>(adjust);
      adjust = INT16_MAX;
    }
    if (adjust < INT16_MIN) {
      factor = INT16_MIN / static_cast<double>(adjust);
      adjust = INT16_MIN;
    }
    frame->setRightSoundTrackAt(i, static_cast<int16_t>(adjust));
    if (factor < 1)
      factor += (1 - factor) / static_cast<double>(8);
  }
}
/*void sound_mix(audio::s16PCMFrame *frame ,audio::s16PCMFrame *another_frame)
{
    double factor = 1;
    for (int i = 0; i < 1024;i++)
    {
        int32_t adjust;
        adjust = static_cast<int32_t>( (frame->getLeftSoundTrackAt(i) + another_frame->getLeftSoundTrackAt(i)) / 2);
        frame->setLeftSoundTrackAt(i,static_cast<int16_t>(adjust));
        adjust = static_cast<int32_t>( (frame->getRightSoundTrackAt(i) + another_frame->getRightSoundTrackAt(i)) / 2);
        frame->setRightSoundTrackAt(i,static_cast<int16_t>(adjust));
    }
}*/

[[gnu::unused]]double average(audio::s16PCMFrame *frame) {
  double aver = 0;
  for (int i = 0; i < 1024; i++) {
    aver += (abs(frame->getLeftSoundTrackAt(i)) + abs(frame->getRightSoundTrackAt(i))) / static_cast<double>(1024);
  }
  
  return aver;
}
void switch_lr(audio::s16PCMFrame *frame) {
  for (int i = 0; i < 1024; i++) {
    int16_t tem = frame->getLeftSoundTrackAt(i);
    frame->setLeftSoundTrackAt(i, frame->getRightSoundTrackAt(i));
    frame->setRightSoundTrackAt(i, tem);
  }
}

void func_merage_complex(audio::s16PCMFrame *frame, audio::s16PCMFrame *frame_background)
{
  double frame_aver = 0;
  double frame_background_aver = 0;
  for(int i = 0; i < 1024; i++)
  {
    frame_aver += (abs(frame->getLeftSoundTrackAt(i)) + abs(frame->getRightSoundTrackAt(i))) / static_cast<double>(1024);
    frame_background_aver += (abs(frame_background->getLeftSoundTrackAt(i)) + abs(frame_background->getRightSoundTrackAt(i))) / static_cast<double>(1024);
  }

  double adjust_coefficient;
  if(fabs(frame_background_aver) < 1e-5)
    return;
  adjust_coefficient = frame_aver / frame_background_aver * 0.8;
  if(fabs(frame_background_aver) < 1e-5)
    adjust_coefficient = 1;
  
  for(int i = 0; i < 1024; i++)
  {
    frame_background->setLeftSoundTrackAt(i,static_cast<int16_t>(frame_background->getLeftSoundTrackAt(i) * adjust_coefficient));
    frame_background->setRightSoundTrackAt(i,static_cast<int16_t>(frame_background->getRightSoundTrackAt(i) * adjust_coefficient));
  }
}

void get_accompany(audio::s16PCMFrame *frame)
{
  double factor = 1;
  for (int i = 0; i < 1024; i++) {
    int32_t adjust;
    int16_t left = frame->getLeftSoundTrackAt(i);
    adjust = static_cast<int32_t>((frame->getLeftSoundTrackAt(i) -frame->getRightSoundTrackAt(i)) * factor);
    if (adjust > INT16_MAX) {
      factor = INT16_MAX / static_cast<double>(adjust);
      adjust = INT16_MAX;
    }
    if (adjust < INT16_MIN) {
      factor = INT16_MIN / static_cast<double>(adjust);
      adjust = INT16_MIN;
    }
    frame->setLeftSoundTrackAt(i, static_cast<int16_t>(adjust));
    if (factor < 1)
      factor += (1 - factor) / static_cast<double>(8);
    
    adjust = static_cast<int32_t>((frame->getRightSoundTrackAt(i) - left) * factor);
    if (adjust > INT16_MAX) {
      factor = INT16_MAX / static_cast<double>(adjust);
      adjust = INT16_MAX;
    }
    if (adjust < INT16_MIN) {
      factor = INT16_MIN / static_cast<double>(adjust);
      adjust = INT16_MIN;
    }
    frame->setRightSoundTrackAt(i, static_cast<int16_t>(adjust));
    if (factor < 1)
      factor += (1 - factor) / static_cast<double>(8);
  }
}