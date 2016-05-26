all: hw6
hw6: main.o distance.o ddistance.o mst.o dmst.o
	gcc main.o distance.o ddistance.o mst.o dmst.o -o hw6
main.o: main.c header.h
	gcc -c main.c
distance.o: distance.c header.h
	gcc -c distance.c
ddistance.o: ddistance.c header.h
	gcc -c ddistance.c
mst.o: mst.c header.h
	gcc -c mst.c
dmst.o:	dmst.c header.h
	gcc -c dmst.c
clean:
	rm -f *.o hw6