#!/bin/bash

error_chk() {
    if [ $? -ne 0 ] ; then
        exit 1
    fi
}

make clean && make
error_chk

# apply the library to the standard lib path to link with the test packages
sudo cp libsysapi.so /usr/lib/ && sudo ldconfig
error_chk

python test_build.py clean && python test_build.py build
error_chk

#cd tests && sudo python test.py
#cat results | grep -q "all success"
#if [ $? -ne 0 ]; then
#	exit 1
#else
#	exit 0
#fi
