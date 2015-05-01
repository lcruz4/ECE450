CC=gcc
DEPS =libBBB.c
SOURCES= main.c
EXECUTABLE = pwm

all: $(EXECUTABLE)

pwm: main.c $(DEPS)
        $(CC) -o $@ $^

.PHONY: clean

clean:
        rm -f *.o *~ $(EXECUTABLE)
