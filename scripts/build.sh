#! /usr/bin/env bash
set -ex

cd build
cmake ..
make
ctest -V
