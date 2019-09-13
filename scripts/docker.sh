#! /usr/bin/env bash

set -ex
docker run --rm -e"UID=$UID" -e"GID=$UID" -v"$PWD:/buildarea" swearjar \
    /bin/sh -c ./scripts/build.sh
