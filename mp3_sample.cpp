#include <iostream>
#include <unistd.h>
#include <func.h>
#include <wav.h>
#include <cmath>
#include <random>

using namespace std;

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
    sin_cos(frame);
    reader.writeDataFrame16(frame);
    delete frame;
  }
  reader.writeToFile(tmp_file);
  cout << "Encoding..." << endl;
  sprintf(cmd, "ffmpeg -i %s %s", tmp_file, argv[2]);
  system(cmd);
  cout << "Success!" << endl;
  remove(tmp_file);
  return 0;
}