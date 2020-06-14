#!/usr/bin/env bash
python -m cpplint --linelength=120 --filter=-build/include_subdir demo.cpp include/*.h src/*.cpp tests/*.cpp
