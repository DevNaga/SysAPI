sysutil_tgt:
	gcc -Wall test_sysutil.c test_getline.c test_getdelim.c -o test_sysutil -lsysapi -pthread

all: sysutil_tgt

clean:
	rm -rf test_sysutil
