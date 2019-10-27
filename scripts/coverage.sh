#! /bin/sh

set -ex

cd build
cmake -DSJ_COVERAGE=ON -DSJ_BUILD_EXAMPLES=OFF ..
make
make coverage
