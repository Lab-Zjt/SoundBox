#include <cli.h>
#include <cstdio>
#include <iostream>
#include <transform.h>

CommandLineInterface CommandLine;
void CommandLineInterface::Clean() {
  printf("\033[H\033[J");
}
int CommandLineInterface::GetOption() {
  std::cin >> _option;
  return _option;
}
void CommandLineInterface::ShowHomePage() {
  CommandLine.Clean();
  printf("Welcome to Use WavParser!\n"
         "\t1. Sound Effects Transform\n"
         "Please Enter Your Choice:");
}
void CommandLineInterface::Wait() {
  getchar();
}
void CommandLineInterface::NoSuchOptionError() {
  printf("No Such OptionQAQ, Press Any Key to Continue.\n");
  CommandLine.Wait();
}
std::string CommandLineInterface::GetString() {
  std::cin >> _string;
  return _string;
}
void CommandLineInterface::SoundEffectsTransform() {
  CommandLine.Clean();
  printf("Sound Effects Transform:\n"
         "\t1. Sin-Cos\n"
         "Please Enter Your Choice:");
  auto op = CommandLine.GetOption();
  switch (op) {
    case 1: {
      //CommandLine.Clean();
      printf("Input File:");
      auto input = CommandLine.GetString();
      printf("Output File:");
      auto output = CommandLine.GetString();
      SoundEffectsTransform1(input, output);
      printf("Press Any Key to Continue.");
      CommandLine.Wait();
      break;
    }
    default: {
      CommandLine.NoSuchOptionError();
      break;
    }
  }
}
void CommandLineInterface::StartLoop() {
  while (true) {
    CommandLine.ShowHomePage();
    auto op = CommandLine.GetOption();
    switch (op) {
      case 1: {
        CommandLine.SoundEffectsTransform();
        break;
      }
      default: {
        CommandLine.NoSuchOptionError();
        break;
      }
    }
  }
}