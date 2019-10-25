
#! /bin/sh

set -ex

cd build
cmake -DSJ_COVERAGE=ON ..
make
make coverage
