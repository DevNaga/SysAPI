SHELL = /bin/sh
STRIPCMD = strip
CC    = gcc
# Remove -g when releasing the library
CFLAGS       = -Wall -Wmissing-prototypes -Wstrict-prototypes -fstack-protector-all -fPIC -g
LDFLAGS = -shared

TARGET  = libsysapi.so
SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)

PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	    $(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)
	    # For the release purposes - no debug, less library size
	    #$(STRIPCMD) $(TARGET)
clean:
	rm -rf *.o ${TARGET}
