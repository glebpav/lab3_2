cmake_minimum_required(VERSION 3.24)
project(lab3_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab3_2 main.c localeTable/TableHelper.c localeTable/TableHelper.h DialogHelper.c DialogHelper.h ConsoleCommandsHelper.c ConsoleCommandsHelper.h ExceptionsHandler.c ExceptionsHandler.h FileHelper.c FileHelper.h)
