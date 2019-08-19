#ifndef SEMAFORO_H
#define SEMAFORO_H

#include<stdio.h>

typedef void* ItemSemaforo;

ItemSemaforo semaforoNew(char[], double, double, int*);

void semaforoDraw(ItemSemaforo, FILE*);

void semaforoSetCorstroke(char[]);
void semaforoSetCorfill(char[]);
void semaforoSetStroke(double);

char* semaforoGetId(ItemSemaforo);
double semaforoGetX(ItemSemaforo);
double semaforoGetY(ItemSemaforo);

void semaforoSetID(ItemSemaforo, char[]);
void semaforoSetX(ItemSemaforo, double);
void semaforoSetY(ItemSemaforo, double);

#endif
