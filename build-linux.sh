#!/bin/bash

mkdir ~/.local/share/asciiclock/
mkdir ~/.local/share/asciiclock/dependencies/
cp -rf ./art ~/.local/share/asciiclock/dependencies/
mkdir ~/.config/asciiclock

cmake -S . -B build
make -C build
cp build/asciiclock ./
