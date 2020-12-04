all: main.o
	gcc -o forkin main.c

main.o: main.c
	gcc -c main.c

run:
	./forkin

clean:
	rm *.o
