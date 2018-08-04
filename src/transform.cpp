#include <transform.h>
#include <iostream>
#include "wav.h"
#include "func.h"

using namespace std;
void SoundEffectsTransform1(const std::string &input, const std::string &output, transform_func_t func) {
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
    func(frame);
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
void SoundMerge(const string &input1, const string &input2, const string &output) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file1("tmpweasdfw.wav");
  const string tmp_file2("tmpwaefwcd.wav");
  fclose(stderr);
  cout << "Decoding..." << endl;
  auto cmd = ffmpeg + input1 + ' ' + tmp_file1;
  system(cmd.c_str());
  cmd = ffmpeg + input2 + ' ' + tmp_file2;
  system(cmd.c_str());
  cout << "Merging..." << endl;
  audio::wavReader i1(tmp_file1.c_str());
  i1.wavParse();
  audio::wavReader i2(tmp_file2.c_str());
  i2.wavParse();
  auto o = i1 + i2;
  o.writeToFile(tmp_file1.c_str());
  cout << "Encoding..." << endl;
  cmd = ffmpeg + tmp_file1 + ' ' + output;
  system(cmd.c_str());
  remove(tmp_file1.c_str());
  remove(tmp_file2.c_str());
  cout << "Success!" << endl;
}
void SoundDepart(const std::string &input, const std::string &left, const std::string &right) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file("sdafwe.wav");
  const string tmp_file_1("safewfwefe.wav");
  auto cmd = ffmpeg + input + ' ' + tmp_file;
  cout << "Decoding..." << endl;
  system(cmd.c_str());
  cout << "Departing..." << endl;
  audio::wavReader reader(tmp_file.c_str());
  audio::wavReader reader1(reader);
  reader.wavParse();
  reader1.wavParse();
  while (!reader.isEnd()) {
    auto frame = reader.readDataFrame16();
    auto frame1 = reader1.readDataFrame16();
    rightBlock(frame);
    leftBlock(frame1);
    reader.writeDataFrame16(frame);
    reader1.writeDataFrame16(frame1);
    delete frame;
    delete frame1;
  }
  reader.writeToFile(tmp_file.c_str());
  reader1.writeToFile(tmp_file_1.c_str());
  cout << "Encoding..." << endl;
  cmd = ffmpeg + tmp_file + ' ' + left;
  system(cmd.c_str());
  cmd = ffmpeg + tmp_file_1 + ' ' + right;
  system(cmd.c_str());
  cout << "Success!" << endl;
}
void SoundMix(const std::string &input1, const std::string &input2, const std::string &output) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file1("teafmpe.wav");
  const string tmp_file2("teadacvewsvw.wav");
  auto cmd = ffmpeg + input1 + ' ' + tmp_file1;
  cout << "Decoding..." << endl;
  system(cmd.c_str());
  cmd = ffmpeg + input2 + ' ' + tmp_file2;
  system(cmd.c_str());
  cout << "Transforming..." << endl;
  audio::wavReader r1(tmp_file1.c_str());
  audio::wavReader r2(tmp_file2.c_str());
  r1.wavParse();
  r2.wavParse();
  while (!r1.isEnd() && !r2.isEnd()) {
    auto frame1 = r1.readDataFrame16();
    auto frame2 = r2.readDataFrame16();
    sound_mix(frame1, frame2);
    r1.writeDataFrame16(frame1);
    delete frame1;
    delete frame2;
  }
  r1.writeToFile(tmp_file1.c_str());
  cmd = ffmpeg + tmp_file1 + ' ' + output;
  cout << "Encoding..." << endl;
  system(cmd.c_str());
  cout << "Success!" << endl;
}
void SoundVolumeAdjust(const std::string &input, const std::string &output, double la, double ra) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file("geioran.wav");
  auto cmd = ffmpeg + input + ' ' + tmp_file;
  cout << "Decoding..." << endl;
  system(cmd.c_str());
  cout << "Transforming..." << endl;
  audio::wavReader reader(tmp_file.c_str());
  while (!reader.isEnd()) {
    auto frame = reader.readDataFrame16();
    volume_adjust(frame, la, ra);
    reader.writeDataFrame16(frame);
    delete frame;
  }
  reader.writeToFile(tmp_file.c_str());
  cmd = ffmpeg + tmp_file + ' ' + output;
  cout << "Encoding..." << endl;
  system(cmd.c_str());
  cout << "Success!" << endl;
}