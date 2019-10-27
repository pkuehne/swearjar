#! /bin/bash

clang-tidy -checks=*,-llvm-header-guard,-google-runtime-*,-hicpp-special-member-functions,-hicpp-signed-bitwise,-cppcoreguidelines-special-member-functions,-cppcoreguidelines-pro-type-union-access,-cert-err58-cpp,-fuchsia-* -warnings-as-errors=* -dump-config -header-filter=src > .clang-tidy
