cmake_minimum_required(VERSION 4.3)
project(Lab_3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab_3 main.c st.c pif.c tokens.c lex.yy.c)
