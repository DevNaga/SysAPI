
[![Build Status](https://travis-ci.org/DevNaga/libsysapi.svg?branch=master)](https://travis-ci.org/DevNaga/libsysapi/)

[![Test Coverage](https://api.codeclimate.com/v1/badges/72dbd4d950e8930ab233/test_coverage)](https://codeclimate.com/github/DevNaga/libsysapi/test_coverage)

# libsysapi

System level APIs to make systems programming simpler.

The library (as of now) provides the following features:

1. Event based function calling mechanism with select
2. Hash tables, Lists, Doubly linked list, Circular Queues, Stacks and Queues as simple but efficient API.
3. File systems interface API, directory list, directory walk (dir in a dir), file read, simple ramfs and some file level API for general purpose file manipulation.
4. Memory controller / accountant (A very simple and basic) that helps restrict your program's memory usage.
5. Network device / interface handling API.
6. Process file system (/proc) API for proc file manipulation for statistics / poll based monitoring applications.
7. Time APIs (very basic and needs more work)
8. Utilities: Printf (but colored output depending on the log level/ priority), daemonizing API (so that you don't have to remember how to setup a daemon), random number and string generators, tty and finding what arch you are running APIs.
9. Basic Threadpools implementation. One thread per work only. Plans for moving to one thread doing multiple work and still
supporting multiple threads doing multiples of work..

For more details about my future works.. please have a look at the TODO file in the repository.

The library only uses pthreads (the pthread support can be hidden via a
macro but that disables the event looping).

When you are using this library use it with ``` -lsysapi ``` and ``` -pthread``` option.

Please note that the library is "not" well tested and it is still in its pre-matured stage.
