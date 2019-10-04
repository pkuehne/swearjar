FROM pkuehne/cpp-build-base:latest

# Usage:
#   Build the project:
#       docker run --rm -v "$PWD:/buildarea" swearjar make -C build
#   Run the tests:
#       docker run --rm -v "$PWD:/buildarea" swearjar make -C build test

RUN apt update -qq && apt install --no-install-recommends -qq -y \
    libncursesw5-dev

WORKDIR /buildarea
COPY . /buildarea
RUN mkdir -p build

CMD ./scripts/build.sh
