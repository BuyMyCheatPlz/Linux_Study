#!/bin/bash
TARGET="myapp"
BUILD_DIR="build"   # Build directory

echo "Building $TARGET..."
mkdir -p $BUILD_DIR
cd $BUILD_DIR

echo "Compiling source files..." #Cmake
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
if [ $? -ne 0 ]; then #命令返回值检查， #?是上一个命令的返回值，0表示成功，非0表示失败
    echo "CMake configuration failed!"
    exit 1
fi

make
#！表示取反，将真变为假，在[]中是专门用来判断条件的，管道指令不能放在[]中

if ! file "$TARGET" | grep -q "ARM"; then  #grep输出值为0则检索成功，非0则失败，|表示管道，将前一个命令的输出作为后一个命令的输入,不显示在屏幕上，-q表示安静模式，不输出任何内容
    echo "Error: $TARGET is not an ARM executable!"
    exit 1
else
    echo "Successfully built $TARGET."
fi

cd .. #返回上一级目录
echo "Done."