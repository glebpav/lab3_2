cmake_minimum_required(VERSION 3.24)
project(lab3_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab3_2 main.c DialogHelper.c DialogHelper.h ConsoleCommandsHelper.c ConsoleCommandsHelper.h ResponsesHandler.c ResponsesHandler.h FileHelper.c FileHelper.h externalTable/TableHelper.c externalTable/TableHelper.h utils.c utils.h)
