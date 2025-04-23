#!/bin/sh
set -eu
if [ $# -ge 1 ] && [ "$1" = 'rebuild' ]; then
	cmake -B build
fi
cmake --build build --parallel
