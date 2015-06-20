#!/bin/bash

make clean && make
# apply the library to the standard lib path to link with the test packages
sudo cp libsysapi.so /usr/lib/ && sudo ldconfig
python test_build.py clean && python test_build.py build
cd tests && sudo python test.py
cat results | grep -q "all success"
if [ $? -ne 0 ]; then
	exit 1
else
	exit 0
fi
