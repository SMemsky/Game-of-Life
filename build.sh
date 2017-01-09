#! /bin/bash

# Ensure that build directory exists
mkdir -p build

if [ -f source/Makefile ];
then
	cd source

	make all

	cd ..
fi
