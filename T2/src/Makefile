TARGET = prog
LIBS = -lm -lArcaboucoTeste
CC = g++
LIBDIRFLAG = -L../lib
CFLAGS = -g -Wall -Wno-write-strings $(LIBDIRFLAG) -I../include

OBJECTS := $(patsubst %.C, %.O, $(wildcard *.C))
HEADERS = $(wildcard *.H)

.PHONY: default all clean

default: all

all: $(OBJECTS)

%.O: %.C $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBDIRFLAG) -Wall $(LIBS) -o $@

%.A: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	-rm -f *.O
	-rm -f $(TARGET)