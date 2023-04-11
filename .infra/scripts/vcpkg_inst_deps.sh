#!/bin/sh
function clone() { # vcpkg install dependencies
    git clone "https://github.com/Microsoft/vcpkg.git"
}

function boot() {
    ./vcpkg/bootstrap-vcpkg.sh
}

function install() {
    ./vcpkg install raylib
}

function make() {
    input_toolchain_filepath=$1 # script argument 1
    toolchain_file_expected = find / -name $input_toolchain_filepath -print | grep $input_toolchain_filepath
    cmake -B /build -S . -DCMAKE_TOOLCHAIN_FILE=/$toolchain_file_expected/scripts/buildsystems/vcpkg.cmake
}

function build() {
    cmake --build /build
}

function init() {
    clone
    boot
    install
    make $1
    build
}