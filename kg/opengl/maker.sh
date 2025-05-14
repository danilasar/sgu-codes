#!/bin/sh

debug() {
    set -o xtrace
    cmake -S . -B ./Build \
          -Wno-dev \
          -D CMAKE_BUILD_TYPE=Debug \
    && make -j -C ./Build
}

build() {
    set -o xtrace
    cmake -S . -B ./Build \
          -Wno-dev \
          -D CMAKE_BUILD_TYPE=Release \
    && make -j -C ./Build
}

format() {
    set -o xtrace
    find Projects -type f \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format -i {} \;
}

clean() {
    set -o xtrace
    rm -rf ./Build
}

help() {
    echo "Использование:"
    echo "./maker.sh build -> Собрать проект с помощью CMake и make -C ./Build/"
    echo "./maker.sh debug -> Собрать проект с сохранением информации для отладки"
    echo "./maker.sh clean -> Удалить содержимое директории ./Build/"
}

case "$1" in
    b|build) build ;;
    d|debug) debug ;;
    f|format) format ;;
    c|clean) clean ;;
    *) help ;;
esac

