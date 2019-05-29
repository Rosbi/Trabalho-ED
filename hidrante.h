#ifndef HIDRANTE_H
#define HIDRANTE_H

#include<stdio.h>

typedef void* ItemHidrante;

ItemHidrante hidranteNew(char[], float, float, int*);

void hidranteDraw(ItemHidrante, FILE*);

void hidranteSetCorstroke(char[]);
void hidranteSetCorfill(char[]);
void hidranteSetStroke(float);

char* hidranteGetId(ItemHidrante);
float hidranteGetX(ItemHidrante);
float hidranteGetY(ItemHidrante);

void hidranteSetID(ItemHidrante, char[]);
void hidranteSetX(ItemHidrante, float);
void hidranteSetY(ItemHidrante, float);

#endif
