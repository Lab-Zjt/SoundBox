#ifndef SAMPLE_CLI_H
#define SAMPLE_CLI_H

#include <string>

class CommandLineInterface {
private:
  int _option;
  std::string _string;
public:
  CommandLineInterface() = default;
  void Clean();
  void ShowHomePage();
  void NoSuchOptionError();
  void SoundEffectsTransform();
  void Wait();
  int GetOption();
  std::string GetString();
  void StartLoop();
};

extern CommandLineInterface CommandLine;

#endif
