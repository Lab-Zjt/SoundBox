#ifndef SAMPLE_CLI_H
#define SAMPLE_CLI_H

#include <string>

class CommandLineInterface {
private:
  int _int = 0;
  std::string _string;
  double _double = 0.0;
public:
  CommandLineInterface() = default;
  void Clean();
  void ShowHomePage();
  void NoSuchOptionError();
  void SoundEffectsTransform();
  void SoundSpeedUp();
  void Cut();
  void Merge();
  void Wait();
  void Depart();
  void Mix();
  void Mix_background();
  void VolumeAdjust();
  int ReadInt();
  double ReadDouble();
  std::string ReadString();
  void StartLoop();
};

extern CommandLineInterface CommandLine;

#endif
