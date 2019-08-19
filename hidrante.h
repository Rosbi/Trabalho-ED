#ifndef HIDRANTE_H
#define HIDRANTE_H

#include<stdio.h>

typedef void* ItemHidrante;

ItemHidrante hidranteNew(char[], double, double, int*);

void hidranteDraw(ItemHidrante, FILE*);

void hidranteSetCorstroke(char[]);
void hidranteSetCorfill(char[]);
void hidranteSetStroke(double);

char* hidranteGetId(ItemHidrante);
double hidranteGetX(ItemHidrante);
double hidranteGetY(ItemHidrante);

void hidranteSetID(ItemHidrante, char[]);
void hidranteSetX(ItemHidrante, double);
void hidranteSetY(ItemHidrante, double);

#endif
