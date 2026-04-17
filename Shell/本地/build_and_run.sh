#!/bin/bash
TARGET="myapp"
BUILD_DIR="build"   # Build directory

echo "Building $TARGET..."
mkdir -p $BUILD_DIR
cd $BUILD_DIR

echo "Compiling source files..." #Cmake
cmake ..
if [ $? -ne 0 ]; then #命令返回值检查， #?是上一个命令的返回值，0表示成功，非0表示失败
    echo "CMake configuration failed!"
    exit 1
fi

make


if [ -f "$TARGET" ]; then
    echo "运行$TARGET..."
    ./$TARGET
else
    echo "Error: $TARGET not found!"
    exit 1
fi

cd .. #返回上一级目录
echo "Done."