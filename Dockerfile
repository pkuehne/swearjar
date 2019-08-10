FROM build-base:latest

# Usage: 
#   Build the project: 
#       docker run --rm -v "$PWD:/buildarea" swearjar make -C build
#   Run the tests:
#       docker run --rm -v "$PWD:/buildarea" swearjar make -C build test

RUN apt update -qq && apt install --no-install-recommends -qq -y \
    libncurses-dev

WORKDIR /buildarea
RUN mkdir -p build

ARG UID=1000
ARG GID=1000
USER $UID:$GID

CMD cmake . -Bbuild