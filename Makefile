main: point.o building.o dictionary_building.o specialtown.o LL_specialtown.o dictionary_specialtown.o main.o
	gcc -Wall -g -o main point.o building.o dictionary_building.o specialtown.o LL_specialtown.o dictionary_specialtown.o main.o

main.o: main.c
	gcc -Wall -g -c -o main.o main.c

dictionary_specialtown.o: dictionary_specialtown.c dictionary_specialtown.h
	gcc -Wall -g -c -o dictionary_specialtown.o dictionary_specialtown.c

LL_specialtown.o: LinkedList_specialtown.c LinkedList_specialtown.h
	gcc -Wall -g -c -o LL_specialtown.o LinkedList_specialtown.c

specialtown.o: specialtown.c specialtown.h
	gcc -Wall -g -c -o specialtown.o specialtown.c

dictionary_building.o: dictionary_building.c dictionary_building.h
	gcc -Wall -g -c -o dictionary_building.o dictionary_building.c

building.o: building.c building.h
	gcc -Wall -g -c -o building.o building.c

point.o: point.c point.h
	gcc -Wall -g -c -o point.o point.c

clean: 
	rm point.o building.o specialtown.o LL_specialtown.o dictionary_specialtown.o main.o
