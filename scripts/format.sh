#! /bin/sh

set -ex

CHANGES=$(clang-format -style=file -output-replacements-xml src/*.cpp src/*.h | grep "replacement " | wc -l)
if [ "$CHANGES" -ne "0" ]
then
    exit 1
fi
