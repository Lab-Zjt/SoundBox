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
         "\t2. Cut"
         "Please Enter Your Choice:");
}
void CommandLineInterface::Wait() {
  getchar();
}
void CommandLineInterface::NoSuchOptionError() {
  printf("No Such OptionQAQ, Press Enter to Continue.\n");
  CommandLine.Wait();
}
std::string CommandLineInterface::GetString() {
  std::cin >> _string;
  return _string;
}
void CommandLineInterface::Cut() {
  CommandLine.Clean();
  printf("Cut:\n"
         "Input File:\n");
  auto input = CommandLine.GetString();
  printf("Output File:\n");
  auto output = CommandLine.GetString();
  printf("Time of Begin:\n");
  auto begin = CommandLine.GetOption();
  printf("Time of End:\n");
  auto end = CommandLine.GetOption();
  CommandLine.Wait();
  SoundCut(input, output, begin, end);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::SoundEffectsTransform() {
  CommandLine.Clean();
  printf("Sound Effects Transform:\n"
         "\t1. Sin-Cos\n"
         "Please Enter Your Choice:");
  auto op = CommandLine.GetOption();
  CommandLine.Wait();
  switch (op) {
    case 1: {
      //CommandLine.Clean();
      printf("Input File:");
      auto input = CommandLine.GetString();
      printf("Output File:");
      auto output = CommandLine.GetString();
      CommandLine.Wait();
      SoundEffectsTransform1(input, output);
      printf("Press Enter to Continue.");
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
    CommandLine.Wait();
    switch (op) {
      case 1: {
        CommandLine.SoundEffectsTransform();
        break;
      }
      case 2: {
        CommandLine.Cut();
      }
      default: {
        CommandLine.NoSuchOptionError();
        break;
      }
    }
  }
}