cmake_minimum_required(VERSION 3.9)
project(PatternMatching)

set(CMAKE_CXX_STANDARD 11)

add_executable(PatternMatching
        pattern-match-query/bitmap.cpp
        pattern-match-query/bitmap.h
        pattern-match-query/common.h
        pattern-match-query/graph.cpp
        pattern-match-query/graph.h
        pattern-match-query/graphbitmap.cpp
        pattern-match-query/graphbitmap.h
        pattern-match-query/main.cpp
        pattern-match-query/vertex.h
        pattern-match-query/vertex.cpp
        )
