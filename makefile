all: siguel

siguel: main.o formasBase.o query.o svg.o
	gcc -o siguel main.o formasBase.o query.o svg.o -lm

main.o: main.c formasBase.h svg.h query.h
	gcc -o main.o main.c -c -W -std=c99 -pedantic -fstack-protector-all

formasBase.o: formasBase.c formasBase.h
	gcc -o formasBase.o formasBase.c -c -W -std=c99 -pedantic -fstack-protector-all

query.o: query.c query.h formasBase.h svg.h
	gcc -o query.o query.c -c -W -std=c99 -pedantic -fstack-protector-all

svg.o: svg.c svg.h formasBase.h
	gcc -o svg.o svg.c -c -W -std=c99 -pedantic -fstack-protector-all

lista.o: lista.c lista.h
	gcc -o lista.o lista.c -c -W -std=c99 -pedantic -fstack-protector-all

clean:
	rm -rf *.o *~ siguel
