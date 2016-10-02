TARGET = prog
LIBS = -lm -lArcaboucoTeste
CC = g++
LIBDIRFLAG = -Ltabelas
CFLAGS = -Wno-write-strings $(LIBDIRFLAG) -I. -Itabelas

OBJECTS := $(patsubst %.C, %.O, $(wildcard *.C))
HEADERS = $(wildcard *.H)

.PHONY: default all clean

default: all

all: $(OBJECTS)
	@echo $(OBJECTS)

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