#include <transform.h>
#include <iostream>
#include <vector>
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
void SoundCut(const std::string &input, const std::string &output, double from, double to) {
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
  fclose(stderr);
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
  remove(tmp_file.c_str());
  remove(tmp_file_1.c_str());
  cout << "Success!" << endl;
}
void SoundMix(const std::string &input1, const std::string &input2, const std::string &output) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file1("teafmpe.wav");
  const string tmp_file2("teadacvewsvw.wav");
  auto cmd = ffmpeg + input1 + ' ' + tmp_file1;
  fclose(stderr);
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
  remove(tmp_file1.c_str());
  remove(tmp_file2.c_str());
  cout << "Success!" << endl;
}
void SoundVolumeAdjust(const std::string &input, const std::string &output, double la, double ra) {
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file("geioran.wav");
  auto cmd = ffmpeg + input + ' ' + tmp_file;
  fclose(stderr);
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
  remove(tmp_file.c_str());
  cout << "Success!" << endl;
}
void SoundSpeedUp(const std::string &input, const std::string &output, int rate) {
  double Rate7[8] = {1};
  for (int i = 1; i < 8; ++i) {
    Rate7[i] = Rate7[i - 1] * 1.10409;
  }
  const string ffmpeg("ffmpeg -i ");
  const string tmp_file("geioran.wav");
  auto cmd = ffmpeg + input + ' ' + tmp_file;
  fclose(stderr);
  cout << "Decoding..." << endl;
  system(cmd.c_str());
  cout << "Transforming..." << endl;
  audio::wavReader reader(tmp_file.c_str());
  reader.wavParse();
  auto should_not_delete = [&Rate7, &rate]() -> bool {
    static double vir = 0;
    static double real = 0;
    vir += 1;
    real += 1 / Rate7[rate];
    if (vir - real >= 1) {
      real += 1;
      return false;
    }
    return true;
  };
  vector<audio::s16PCMFrame *> framelist;
  audio::s16PCMFrame *cur = nullptr;
  int j = 0;
  while (!reader.isEnd()) {
    auto frame = reader.readDataFrame16();
    if (cur == nullptr) {
      cur = new audio::s16PCMFrame;
      cur->offset = frame->offset;
    }
    for (int i = 0; i < 1024; ++i) {
      if (should_not_delete()) {
        cur->setLeftSoundTrackAt(j, frame->getLeftSoundTrackAt(i));
        cur->setRightSoundTrackAt(j, frame->getRightSoundTrackAt(i));
        j++;
        if (j >= 1024) {
          j = 0;
          framelist.push_back(cur);
          cur = new audio::s16PCMFrame;
        }
      }
    }
    delete frame;
  }
  for (int i = 1; i < framelist.size(); ++i) {
    framelist[i]->offset = framelist[i - 1]->offset + 4096;
  }
  auto begin = framelist[0]->offset;
  for (auto &fr:framelist) {
    reader.writeDataFrame16(fr);
    delete fr;
  }
  reader.setFileSize(framelist.size() * 4096 + begin);
  reader.writeToFile(tmp_file.c_str());
  cmd = ffmpeg + tmp_file + ' ' + output;
  cout << "Encoding..." << endl;
  system(cmd.c_str());
  remove(tmp_file.c_str());
  cout << "Success!" << endl;
}

void SoundMerge_Complex(const std::string &input1, const std::string &input2, const std::string &output) {
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
  audio::wavReader reader(tmp_file1.c_str());
  reader.wavParse();
  audio::wavReader reader_background(tmp_file2.c_str());
  reader_background.wavParse();
  while (!reader.isEnd()) {
    auto frame = reader.readDataFrame16();
    
    if(reader_background.isEnd())
    {
      reader_background.offset_zero();
      
    }
    auto frame_background = reader_background.readDataFrame16();
    func_merage_complex(frame,frame_background);
    sound_mix(frame,frame_background);
    reader.writeDataFrame16(frame);
    delete frame;
    delete frame_background;
  }
  reader.writeToFile(tmp_file1.c_str());
  cout << "Encoding..." << endl;
  cmd = ffmpeg + tmp_file1 + ' ' + output;
  system(cmd.c_str());
  remove(tmp_file1.c_str());
  remove(tmp_file2.c_str());
  cout << "Success!" << endl;
}