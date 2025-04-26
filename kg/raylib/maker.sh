#!/bin/sh

debug() {
    set -o xtrace
    cmake -S . -B ./Build \
          -Wno-dev \
          -D CMAKE_BUILD_TYPE=Debug \
    && cmake --build Build --parallel
}

build() {
    set -o xtrace
    cmake -S . -B ./Build \
          -Wno-dev \
          -D CMAKE_BUILD_TYPE=Release \
    && cmake --build Build --parallel
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
    echo "./maker.sh altinstall -> Установить необходимые для сборки на ALT Linux пакеты"
}

altinstall() {
    sudo apt-get update
    sudo apt-get install \
        cmake make gcc-c++ \
        wayland-devel \
        libwayland-client-devel \
        libwayland-cursor-devel \
        libwayland-egl-devel \
        libxkbcommon-devel \
        libX11-devel \
        libXrandr-devel \
        libXinerama-devel \
        libXcursor-devel \
        libXi-devel \
        libgtk+3-devel \
        libGL-devel
}

case "$1" in
    b|build) build ;;
    d|debug) debug ;;
    f|format) format ;;
    c|clean) clean ;;
    altinstall) altinstall ;;
    *) help ;;
esac

