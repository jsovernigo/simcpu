CFLAGS		=-Wall -ansi -g
TFLAGS		=-Wall -Wextra -Werror -ansi -pedantic -g
OBJECTS		=queue.o processes.o parse.o

all: build

build: $(OBJECTS)
	echo TODO

#
#	Object rules
#

queue.o: src/queue.c include/queue.h
	gcc $(CFLAGS) src/queue.c -c -o bin/queue.o -I./include

parse.o: src/parse.c include/parse.h processes.o
	gcc $(CFLAGS) src/parse.c bin/processes.o -c -o bin/parse.o -I./include

processes.o: src/processes.c include/processes.h
	gcc $(CFLAGS) src/processes.c -c -o bin/processes.o -I./include

#
#	Test rules
#
testqueue:
	gcc $(TFLAGS) src/testqueue.c src/queue.c -I./include

testparse:
	gcc $(TFLAGS) src/testparse.c src/parse.c src/processes.c -I./include

#
#	Cleaning rules
#


clobber:
	rm bin/*.o
