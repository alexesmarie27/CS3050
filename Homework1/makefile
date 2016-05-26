hw3: main.o distance.o ddistance.o components.o dcomponents.o
	gcc main.o distance.o ddistance.o components.o dcomponents.o -o hw3
main.o: main.c header.h
	gcc -c main.c
distance.o: distance.c header.h
	gcc -c distance.c
ddistance.o: ddistance.c header.h
	gcc -c ddistance.c
components.o: components.c header.h
	gcc -c components.c
dcomponents.o:	dcomponents.c header.h
	gcc -c dcomponents.c
clean:
	rm -f *.o hw3