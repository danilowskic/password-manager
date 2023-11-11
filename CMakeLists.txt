cmake_minimum_required(VERSION 3.22)
project(password_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(password_manager main.cpp PasswordManager.cpp PasswordManager.h Password.cpp Password.h Category.cpp Category.h Options.cpp)
