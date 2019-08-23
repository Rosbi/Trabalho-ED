#ifndef MURO_H
#define MURO_H

#include<stdio.h>

typedef void* ItemMuro;

ItemMuro muroNew(Ponto a, Ponto b, int* sizeofItem);

void muroDraw(ItemMuro muro, FILE* out);

#endif
