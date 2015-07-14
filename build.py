#!/usr/bin/python

import os
import sys

core_lib="core"
base_lib="../"
core_build_cmd="make clean && make"
test_build_cmd="python test_build.py clean && python test_build.py build"
os.chdir(core_lib)

ret = os.system(core_build_cmd);
if ret != 0:
    exit(1)

os.chdir(base_lib);

ret = os.system(test_build_cmd);
if ret != 0:
    exit(1)

exit(0)
