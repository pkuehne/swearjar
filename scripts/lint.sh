#! /bin/sh

set -ex

cd build
cmake -DSJ_LINT_COMPILATION=ON -DSJ_BUILD_EXAMPLES=OFF -DSJ_BUILD_TESTS=OFF ..
make -j 4
