#!/usr/bin/env bash
result=$(pip freeze | grep cpplint)
if [ ${#result} -eq 0 ]; then
    sudo pip install cpplint
fi
cpplint main.cpp
cpplint include/*.h
cpplint src/*.cpp
