#!/bin/bash

make clean && make
# apply the library to the standard lib path to link with the test packages
sudo cp libsysapi.so /usr/lib/ && ldconfig
python test_build.py clean && python test_build.py build
