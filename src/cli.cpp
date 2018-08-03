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
  getchar();
  return _option;
}
void CommandLineInterface::ShowHomePage() {
  CommandLine.Clean();
  printf("Welcome to Use WavParser!\n"
         "\t1. Sound Effects Transform\n"
         "\t2. Cut\n"
         "\t3. Merge\n"
         "\t4. Depart\n"
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
  getchar();
  return _string;
}
void CommandLineInterface::Cut() {
  CommandLine.Clean();
  printf("Cut:\n"
         "Input File:");
  auto input = CommandLine.GetString();
  printf("Output File:");
  auto output = CommandLine.GetString();
  printf("Time of Begin:");
  auto begin = CommandLine.GetOption();
  printf("Time of End:");
  auto end = CommandLine.GetOption();
  SoundCut(input, output, begin, end);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::SoundEffectsTransform() {
  CommandLine.Clean();
  printf("Sound Effects Transform:\n"
         "\t1. Sin-Cos\n"
         "\t2. 8bit-style\n"
         "\t3. Block Left Sound Track\n"
         "\t4. Block Right Sound Track\n"
         "\t5. Depart\n"
         "Please Enter Your Choice:");
  auto op = CommandLine.GetOption();
  printf("Input File:");
  auto input = CommandLine.GetString();
  printf("Output File:");
  auto output = CommandLine.GetString();
  switch (op) {
    case 1: {
      //CommandLine.Clean();
      SoundEffectsTransform1(input, output, sin_cos);
      printf("Press Enter to Continue.");
      CommandLine.Wait();
      break;
    }
    case 2: {
      SoundEffectsTransform1(input, output, bit8);
      printf("Press Enter to Continue.");
      CommandLine.Wait();
      break;
    }
    case 3: {
      SoundEffectsTransform1(input, output, leftBlock);
      printf("Press Enter to Continue.");
      CommandLine.Wait();
      break;
    }
    case 4: {
      SoundEffectsTransform1(input, output, rightBlock);
      printf("Press Enter to Continue.");
      CommandLine.Wait();
      break;
    }
    case 5: {
      SoundEffectsTransform1(input, output, depart);
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
void CommandLineInterface::Depart() {
  CommandLine.Clean();
  printf("Depart:\n"
         "Input File:");
  auto input = CommandLine.GetString();
  printf("Left Sound Track Output File:");
  auto left = CommandLine.GetString();
  printf("Right Sound Track Output File:");
  auto right = CommandLine.GetString();
  SoundDepart(input, left, right);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::Merge() {
  CommandLine.Clean();
  printf("Merge:\n"
         "Input File1:");
  auto input1 = CommandLine.GetString();
  printf("Input File2:");
  auto input2 = CommandLine.GetString();
  printf("Output File:");
  auto output = CommandLine.GetString();
  SoundMerge(input1, input2, output);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
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
      case 2: {
        CommandLine.Cut();
        break;
      }
      case 3: {
        CommandLine.Merge();
        break;
      }
      case 4: {
        CommandLine.Depart();
        break;
      }
      default: {
        CommandLine.NoSuchOptionError();
        break;
      }
    }
  }
}