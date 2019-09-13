#! /bin/bash

set -ex

docker run --rm -it -v "$PWD:/buildarea" swearjar /bin/bash
