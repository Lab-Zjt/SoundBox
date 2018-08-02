#include <transform.h>
#include <iostream>
#include "wav.h"
#include "func.h"

using namespace std;
void SoundEffectsTransform1(const std::string &input, const std::string &output) {
  const std::string bcmd = "ffmpeg -i ";
  cout << "Decoding..." << endl;
  fclose(stderr);
  const std::string tmp_file = "tmp_tarxvf.wav";
  //sprintf(cmd, "ffmpeg -i %s %s", input.c_str(), tmp_file);
  auto cmd = bcmd + input + ' ' + tmp_file;
  system(cmd.c_str());
  cout << "Transforming..." << endl;
  auto reader = audio::wavReader(tmp_file.c_str());
  reader.wavParse();
  while (!reader.isEnd()) {
    auto frame = reader.readDataFrame16();
    sin_cos(frame);
    reader.writeDataFrame16(frame);
    delete frame;
  }
  reader.writeToFile(tmp_file.c_str());
  cout << "Encoding..." << endl;
  cmd = bcmd + tmp_file + ' ' + output;
  system(cmd.c_str());
  cout << "Success!" << endl;
  remove(tmp_file.c_str());
}
void SoundCut(const std::string &input, const std::string &output, int from, int to) {
  const std::string bcmd = "ffmpeg -i ";
  cout << "Decoding..." << endl;
  fclose(stderr);
  const std::string tmp_file = "tmp_tarxvf.wav";
  auto cmd = bcmd + input + ' ' + tmp_file;
  system(cmd.c_str());
  cout << "Transforming..." << endl;
  auto reader = audio::wavReader(tmp_file.c_str());
  reader.wavParse();
  auto fmt = reader.getFormat();
  auto metadata = reader.getMetadata();
  auto begin = static_cast<std::int64_t>(fmt.byteRate / 4096.0 * from) * 4096;
  auto end = static_cast<std::int64_t >(fmt.byteRate / 4096.0 * to) * 4096;
  auto filesize = metadata.dataOffset + end - begin;
  reader.setFileSize(filesize);
  memmove(reader.getData() + metadata.dataOffset, reader.getData() + metadata.dataOffset + begin, filesize);
  reader.writeToFile(tmp_file.c_str());
  cout << "Encoding..." << endl;
  cmd = bcmd + tmp_file + ' ' + output;
  system(cmd.c_str());
  cout << "Success!" << endl;
  remove(tmp_file.c_str());
}