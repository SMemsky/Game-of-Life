#! /bin/bash

if [ -f build/stranded2pp ];
then
	cd build

	valgrind --leak-check=full ./life

	cd ..
fi
