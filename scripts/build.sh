#! /bin/sh

set -ex

cd build
cmake ..
make
ctest -V
