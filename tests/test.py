#!/usr/bin/python

import os

sysnet_tests=[
        "sudo ./test_sysnet -m eth0",
        "sudo ./test_sysnet -c",
        "sudo ./test_sysnet -M",
        "sudo ./test_sysnet -n",
        ]

syscirque_tests=[
        ]

sysevent_tests=[
        ]

sysfs_tests=[
        ]

sysutil_tests=[
        ]

command_exec=[
        sysnet_tests,
        syscirque_tests,
        sysevent_tests,
        sysfs_tests,
        sysutil_tests,
        ]

output_result="results"

failure = 0

fd = open(output_result, "w")
fd.write("results....\n")
fd.write("===========================\n")

for list_item in command_exec:
    for test in list_item:
        val = os.system(test)
        if val != 0:
            fd.write("failed " + test + " " + "return code " + str(val) + "\n")
            failure = failure + 1

if failure == 0:
    fd.write("all success\n")

fd.close()
