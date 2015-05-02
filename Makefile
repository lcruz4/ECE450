CC=gcc
DEPS =libBBB.c motor.c
SOURCES = pwmwithlib.c
EXECUTABLE = pwmwithlib

all: $(EXECUTABLE)

pwmwithlib: pwmwithlib.c $(DEPS)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ $(EXECUTABLE)
