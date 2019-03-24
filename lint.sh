#!/usr/bin/env bash
result=$(pip freeze | grep cpplint)
if [[ ${#result} -eq 0 ]]; then
	pip install cpplint
fi
cpplint --linelength=120 --filter=-build/include_subdir demo.cpp include/*.h src/*.cpp tests/*.cpp
