#! /bin/bash

if [ -f build/life ];
then
	cd build

	valgrind --leak-check=full ./life

	cd ..
fi
