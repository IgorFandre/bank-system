#include "IOIostream.h"

void ConsoleGet::ClearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int64_t ConsoleGet::InputNumber() {
  int64_t number;
  std::cin >> number;
  ClearInput();
  return number;
}

std::string ConsoleGet::InputString() {
  std::string string;
  std::cin >> string;
  ClearInput();
  return string;
}

void ConsoleShow::Output(int64_t number) { std::cout << number << std::endl; }

void ConsoleShow::Output(const std::string &string) {
  std::cout << string << std::endl;
}