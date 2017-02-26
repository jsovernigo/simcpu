CFLAGS		=-Wall -ansi -g
TFLAGS		=-Wall -Wextra -Werror -ansi -pedantic -g
OBJECTS		=queue.o processes.o parse.o exec.o

all: build

#
# 	large-scale macros
#
#
build: $(OBJECTS)
	gcc $(CFLAGS) bin/queue.o bin/processes.o bin/parse.o bin/exec.o src/simcpu.c -o simcpu -I./include

setup: bin/
	mkdir bin

#
#	Object rules
#

queue.o: src/queue.c include/queue.h
	gcc $(CFLAGS) src/queue.c -c -o bin/queue.o -I./include

parse.o: src/parse.c include/parse.h processes.o
	gcc $(CFLAGS) src/parse.c -c -o bin/parse.o -I./include

processes.o: src/processes.c include/processes.h
	gcc $(CFLAGS) src/processes.c -c -o bin/processes.o -I./include

exec.o: src/exec.c include/exec.h
	gcc $(CFLAGS) src/exec.c -c -o bin/exec.o -I./include

#
#	Test rules
#
testqueue:
	gcc $(TFLAGS) src/testqueue.c src/queue.c -I./include

testparse:
	gcc $(TFLAGS) src/testparse.c src/parse.c src/processes.c src/queue.c -I./include

#
#	Cleaning rules
#

clean:
	rm simcpu

clobber:
	rm bin/*.o simcpu
