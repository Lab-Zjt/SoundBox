#include <cli.h>
#include <cstdio>
#include <iostream>
#include <transform.h>

CommandLineInterface CommandLine;
void CommandLineInterface::Clean() {
  printf("\033[H\033[J");
}
int CommandLineInterface::ReadInt() {
  std::cin >> _int;
  getchar();
  return _int;
}
double CommandLineInterface::ReadDouble() {
  std::cin >> _double;
  getchar();
  return _double;
}
void CommandLineInterface::ShowHomePage() {
  CommandLine.Clean();
  printf("Welcome to Use WavParser!\n"
         "\t1. Sound Effects Transform\n"
         "\t2. Cut\n"
         "\t3. Merge\n"
         "\t4. Depart\n"
         "\t5. Mix 2 Music Files\n"
         "\t6. Volume Adjust\n"
         "\t7. Speed Up\n"
         "Please Enter Your Choice:");
}
void CommandLineInterface::Wait() {
  getchar();
}
void CommandLineInterface::NoSuchOptionError() {
  printf("No Such OptionQAQ, Press Enter to Continue.\n");
  CommandLine.Wait();
}
std::string CommandLineInterface::ReadString() {
  std::cin >> _string;
  getchar();
  return _string;
}
void CommandLineInterface::Cut() {
  CommandLine.Clean();
  printf("Cut:\n"
         "Input File:");
  auto input = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
  printf("Time of Begin:");
  auto begin = CommandLine.ReadDouble();
  printf("Time of End:");
  auto end = CommandLine.ReadDouble();
  SoundCut(input, output, begin, end);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::VolumeAdjust() {
  printf("Volume Adjust:\n"
         "Input File:");
  auto input = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
  printf("Left Sound Track Adjust Factor:");
  auto la = CommandLine.ReadDouble();
  printf("Right Sound Track Adjust Factor:");
  auto ra = CommandLine.ReadDouble();
  SoundVolumeAdjust(input, output, la, ra);
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
         "\t5. Make Sound More Consecutive\n"
         "\t6. Switch Left and Right Sound Track.\n"
         "Please Enter Your Choice:");
  auto op = CommandLine.ReadInt();
  printf("Input File:");
  auto input = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
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
      SoundEffectsTransform1(input, output, consecutive);
      printf("Press Enter to Continue.");
      CommandLine.Wait();
      break;
    }
    case 6: {
      SoundEffectsTransform1(input, output, switch_lr);
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
void CommandLineInterface::SoundSpeedUp() {
  CommandLine.Clean();
  printf("Sound Speed Up:\n"
         "Input File:");
  auto input = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
  printf("Speed Up Rate(0-7):");
  auto rate = CommandLine.ReadInt();
  if (rate < 0 || rate > 7) {
    printf("Invalid Rate! Press Enter to Continue.\n");
    CommandLine.Wait();
    return;
  }
  ::SoundSpeedUp(input, output, rate);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::Depart() {
  CommandLine.Clean();
  printf("Depart:\n"
         "Input File:");
  auto input = CommandLine.ReadString();
  printf("Left Sound Track Output File:");
  auto left = CommandLine.ReadString();
  printf("Right Sound Track Output File:");
  auto right = CommandLine.ReadString();
  SoundDepart(input, left, right);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::Merge() {
  CommandLine.Clean();
  printf("Merge:\n"
         "Input File1:");
  auto input1 = CommandLine.ReadString();
  printf("Input File2:");
  auto input2 = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
  SoundMerge(input1, input2, output);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::Mix() {
  CommandLine.Clean();
  printf("Mix:\n"
         "Input File1:");
  auto input1 = CommandLine.ReadString();
  printf("Input File2:");
  auto input2 = CommandLine.ReadString();
  printf("Output File:");
  auto output = CommandLine.ReadString();
  SoundMix(input1, input2, output);
  printf("Press Enter to Continue.\n");
  CommandLine.Wait();
}
void CommandLineInterface::StartLoop() {
  while (true) {
    CommandLine.ShowHomePage();
    auto op = CommandLine.ReadInt();
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
      case 5: {
        CommandLine.Mix();
        break;
      }
      case 6: {
        CommandLine.VolumeAdjust();
        break;
      }
      case 7: {
        CommandLine.SoundSpeedUp();
        break;
      }
      default: {
        CommandLine.NoSuchOptionError();
        break;
      }
    }
  }
}