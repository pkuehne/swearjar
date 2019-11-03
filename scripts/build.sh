#! /bin/sh

set -ex

cd build
cmake ..
make -j 4
ctest -V
