#!/usr/bin/python

import os
import sys
import glob
builddir = ["tests"]

gcc_command="gcc -Wall"
gcc_ldcommand="-pthread -lsysapi"
ignore_warns=" 1>/dev/null 2>/dev/null"

def build():
    for build_dir in builddir:
        os.chdir(build_dir)
        for file in glob.glob("*.c"):
            binary, ext = os.path.splitext(file)
            print binary
            full_gcc_cmd=gcc_command + " " + file + " -o " + binary + " " + gcc_ldcommand + " " + ignore_warns
            print full_gcc_cmd
            os.system(full_gcc_cmd)
        os.chdir("../")

def clean():
    for build_dir in builddir:
        os.chdir(build_dir)
        for file in glob.glob("*.c"):
            binary, ext = os.path.splitext(file)
            rmcmd="rm -rf " + binary
            os.system(rmcmd)
        os.chdir("../")
if len(sys.argv) != 2:
    print sys.argv[0] + " build / clean"
    exit(0)

print sys.argv[1]
if sys.argv[1] == "build":
    build()
elif sys.argv[1] == "clean":
    clean()

