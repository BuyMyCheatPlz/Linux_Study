#!/usr/bin/env bash
set -euo pipefail #如果遇到问题则退出，并且在使用未定义的变量时抛出错误

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)" #CD到脚本所在目录，并获取绝对路径
BUILD_DIR="$ROOT_DIR/build"

if [[ "$#" -eq 0 ]]; then #如果没有传递参数，则默认构建所有模块
	set -- all
fi

mkdir -p "$BUILD_DIR"

# Keep build directory in sync with current module sources.
cp "$ROOT_DIR/gpioled.c" "$BUILD_DIR/gpioled.c"
cp "$ROOT_DIR/Makefile" "$BUILD_DIR/Makefile"

# Build only inside build/ so generated files stay there.
make -C "$BUILD_DIR" "$@" #在build目录下执行make命令，传递所有参数
rm -f "$BUILD_DIR/gpioled.c" "$BUILD_DIR/Makefile"