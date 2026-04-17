cmake_minimum_required(VERSION 3.10)

project(MyApp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(myapp
	main.c
	utils.c
)
