#include "Executable/Executable.h"
#include "Filesystem/Filesystem.h"

int main() {
  Filesystem::CheckDirectory("Data");
  Executable exe = Executable();
  exe.Start();
}
