cmake_minimum_required(VERSION 3.10)

project(BankingSystem VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable
add_executable(BankingSystem
    taskcode.cpp
)

# Windows specific settings
if(WIN32)
    target_compile_definitions(BankingSystem PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()