cmake_minimum_required(VERSION 3.10)
#指定cmake最低版本要求
project(HelloCmake LANGUAGES C)
#定义项目名称和使用的语言
add_executable(hello hello.c)
#添加要生成的可执行文件
