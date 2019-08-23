all: siguel

siguel: main.o lista.o query.o svg.o formasBase.o hidrante.o quadra.o semaforo.o torre.o geometria.o predio.o muro.o
	gcc -o siguel main.o formasBase.o lista.o query.o svg.o hidrante.o quadra.o semaforo.o torre.o geometria.o predio.o muro.o -lm

main.o: main.c formasBase.h svg.h query.h
	gcc -o main.o main.c -c -W -std=c99 -pedantic -fstack-protector-all

formasBase.o: formasBase.c formasBase.h
	gcc -o formasBase.o formasBase.c -c -W -std=c99 -pedantic -fstack-protector-all

query.o: query.c query.h formasBase.h svg.h lista.h
	gcc -o query.o query.c -c -W -std=c99 -pedantic -fstack-protector-all

svg.o: svg.c svg.h formasBase.h hidrante.h semaforo.h quadra.h torre.h lista.h
	gcc -o svg.o svg.c -c -W -std=c99 -pedantic -fstack-protector-all

lista.o: lista.c lista.h
	gcc -o lista.o lista.c -c -W -std=c99 -pedantic -fstack-protector-all

hidrante.o: hidrante.c hidrante.h formasBase.h
	gcc -o hidrante.o hidrante.c -c -W -std=c99 -pedantic -fstack-protector-all

quadra.o: quadra.c quadra.h formasBase.h
	gcc -o quadra.o quadra.c -c -W -std=c99 -pedantic -fstack-protector-all

semaforo.o: semaforo.c semaforo.h formasBase.h
	gcc -o semaforo.o semaforo.c -c -W -std=c99 -pedantic -fstack-protector-all

torre.o: torre.c torre.h formasBase.h
	gcc -o torre.o torre.c -c -W -std=c99 -pedantic -fstack-protector-all

geometria.o: geometria.c geometria.h
	gcc -o geometria.o geometria.c -c -W -std=c99 -pedantic -fstack-protector-all

predio.o: predio.c predio.h
	gcc -o predio.o predio.c -c -W -std=c99 -pedantic -fstack-protector-all

muro.o: muro.c muro.h
	gcc -o muro.o muro.c -c -W -std=c99 -pedantic -fstack-protector-all

clean:
	rm -rf *.o *~ siguel
