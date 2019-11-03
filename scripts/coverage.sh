#! /bin/sh

set -ex

cd build
cmake -DSJ_COVERAGE=ON -DSJ_BUILD_EXAMPLES=OFF ..
make -j 4
make coverage
