.PHONY: tracker tracker.o fakeclient data.o parser.o silent.o

all: tracker fakeclient

tracker: tracker.o data.o parser.o silent.o
	gcc tracker.o data.o parser.o silent.o -o tracker -lpthread -Wall

tracker.o:
	gcc -c tracker.c -lpthread -Wall

data.o:
	gcc -c data.c -Wall

parser.o:
	gcc -c parser.c -Wall

silent.o:
	gcc -c silent.c -Wall

fakeclient:
	gcc fakeclient.c -o fakeclient

clean:
	rm -rf *.o fakeclient tracker
