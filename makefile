all: siguel

siguel: main.o formas.o query.o svg.o
	gcc -o siguel main.o formas.o query.o svg.o -lm

main.o: main.c formas.h svg.h query.h
	gcc -o main.o main.c -c -W -std=c99 -pedantic -fstack-protector-all

formas.o: formas.c formas.h
	gcc -o formas.o formas.c -c -W -std=c99 -pedantic -fstack-protector-all

query.o: query.c query.h formas.h svg.h
	gcc -o query.o query.c -c -W -std=c99 -pedantic -fstack-protector-all

svg.o: svg.c svg.h formas.h
	gcc -o svg.o svg.c -c -W -std=c99 -pedantic -fstack-protector-all

clean:
	rm -rf *.o *~ siguel
