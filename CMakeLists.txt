cmake_minimum_required(VERSION 3.9)
project(PatternMatching)

set(CMAKE_CXX_STANDARD 11)

add_executable(PatternMatching
        pattern-match-query/Datasets/SF
        pattern-match-query/Datasets/YeastS.net
        pattern-match-query/.gitignore
        pattern-match-query/graph.cpp
        pattern-match-query/graph.h
        pattern-match-query/main.cpp
        pattern-match-query/bitmap.h
        pattern-match-query/graphbitmap.h
        )
