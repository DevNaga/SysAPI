
all:
	gcc -Wall -shared -fPIC sysapi_net.c -o libsysapi.so
clean:
	rm -rf *.o *.so
