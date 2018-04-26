#!/usr/bin/python

import os
import sys

core_lib="core"
tests_dir="tests"
base_lib="../"
core_build_cmd="make clean && make"
test_build_cmd="make clean && make all"
install_lib="sudo cp libsysapi.so /usr/lib/ && sudo ldconfig"

os.chdir(core_lib)

ret = os.system(core_build_cmd);
if ret != 0:
    return 1

ret = os.system(install_lib)
if ret != 0:
    return 1

os.chdir(base_lib);
os.chdir(tests_dir);

ret = os.system(test_build_cmd);
if ret != 0:
    return 1

return 0
