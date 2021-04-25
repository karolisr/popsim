#!/usr/bin/env bash

cd "./src/main/python/popsimpy/ui" || exit
pyuic5 -o main_window.py main_window.ui
