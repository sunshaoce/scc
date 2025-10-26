CC:=clang
CFLAGS:=-Iinclude -std=c99 -Wall
SRC=$(wildcard src/*.c)

all: scc

scc: clean
	${CC} ${CFLAGS} ${SRC} -o scc

debug: clean
	${CC} ${CFLAGS} ${SRC} -g -DDEBUG -o scc

.PHONY: test clean
test: scc
	cd test && bash ./run-tests.sh

clean:
	@rm -f scc *.o
