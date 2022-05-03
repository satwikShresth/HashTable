CC=gcc
OBJ=obj
BIN=bin

all: bin/queueTests bin/josephus

obj/table.o: src/table.c src/interface.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${CC} -c -o obj/table.o src/table.c
bin/wordCount: obj/table.o src/wordCount.c
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${CC} -o bin/wordCount obj/table.o src/wordCount.c

test01: bin/wordCount
bin/wordCount 10 examples/001.txt

test02: bin/wordCount
bin/wordCount 10 examples/345−0.txt

test03: bin/wordCount
bin/wordCount 50 examples/345−0.txt

test04: bin/wordCount
bin/wordCount 200 examples/345−0.txt

test05: bin/wordCount
bin/wordCount 10 examples/1080−0.txt

test06: bin/wordCount
bin/wordCount 50 examples/1080−0.txt

test07: bin/wordCount
bin/wordCount 200 examples/1080−0.txt

test08: bin/wordCount
bin/wordCount 10 examples/pg2265.txt

test09: bin/wordCount
bin/wordCount 50 examples/pgg2265.txt



clean:
	rm -f bin/wordCount
	rm −f −d bin
	rm -f obj/table.o
	rm −f −d obj