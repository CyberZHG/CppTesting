#!/usr/bin/env bash
result=$(pip freeze | grep cpplint)
if [ ${#result} -eq 0 ]; then
	pip install cpplint
fi
cpplint --filter=-legal/copyright main.cpp
cpplint --filter=-legal/copyright include/*.h
cpplint --filter=-legal/copyright src/*.cpp
cpplint --filter=-legal/copyright test/*.cpp
