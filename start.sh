# Little script for MacOS

echo "Updating brew"
brew update

echo "Installing googletest"
brew install googletest

echo "Installing cmake"
brew install cmake

mkdir -p build && cd build
cmake .. && make

cd ../bin
chmod u+x test_bank_system bank_system
