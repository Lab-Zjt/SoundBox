#include <iostream>
#include <unistd.h>
#include <wav.hpp>
#include <cmath>
#include <random>

using namespace std;
auto func1 = [](audio::s16PCMFrame *frame) {
  static int loop = 0;
  for (int i = 0; i < 1024; ++i)
  {
    auto sum = frame->getLeftSoundTrackAt(i) + frame->getRightSoundTrackAt(i);
    frame->setLeftSoundTrackAt(i, static_cast<int16_t>(std::sin(static_cast<double>(loop) / 512) * sum / 2));
    frame->setRightSoundTrackAt(i, static_cast<int16_t>(std::cos(static_cast<double>(loop) / 512) * sum / 2));
  }
  ++loop;
};
std::random_device rd{};
std::mt19937 gen{rd()};
std::normal_distribution<> d(2, 0.001);
auto func2 = [](audio::s16PCMFrame *frame) {
  auto loop = 0;
  auto sum = 0;
  for (int i = 0; i < 1024; ++i)
  {
    frame->setLeftSoundTrackAt(i, frame->getLeftSoundTrackAt(i) / d(gen));
    frame->setRightSoundTrackAt(i, frame->getRightSoundTrackAt(i) / d(gen));
  }
};
int main(int argc, char *argv[])
{
  char cmd[1024];
  cout << "Decoding..." << endl;
  const char *tmp_file = "tmp_tarxvf.wav";
  sprintf(cmd, "ffmpeg -i %s %s", argv[1], tmp_file);
  system(cmd);
  cout << "Transforming..." << endl;
  auto reader = audio::wavReader(tmp_file);
  reader.wavParse();
  while (!reader.isEnd())
  {
    auto frame = reader.readDataFrame16();
    func1(frame);
    reader.writeDataFrame16(frame);
    delete frame;
  }
  reader.writeToFile(tmp_file);
  cout << "Encoding..." << endl;
  sprintf(cmd,"ffmpeg -i %s %s",tmp_file,argv[2]);
  system(cmd);
  cout << "Success!" << endl;
  remove(tmp_file);
  return 0;
}