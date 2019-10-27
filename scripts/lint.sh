#! /bin/sh

set -ex

cd build
cmake -DSJ_LINT_COMPILATION=ON ..
make
