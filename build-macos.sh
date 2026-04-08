#!/bin/bash

mkdir ~/Library/Application\ Support/asciiclock/
mkdir ~/Library/Application\ Support/asciiclock/dependencies
cp -rf ./art ~/Library/Application\ Support/asciiclock/dependencies 

cmake -S . -B build
make -C build
cp build/asciiclock ./
