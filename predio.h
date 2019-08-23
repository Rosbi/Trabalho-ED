#ifndef PREDIO_H
#define PREDIO_H

#include<stdio.h>
#include"geometria.h"

typedef void* ItemPredio;

ItemPredio predioNew(char* cep, char face, double num, double frente, double profundidade, double margem, ItemQuadra quadra, int* sizeofItem);

void predioDraw(ItemPredio, FILE*);

Reta getPredioCima(ItemPredio);
Reta getPredioEsquerda(ItemPredio);
Reta getPredioDireita(ItemPredio);
Reta getPredioBaixo(ItemPredio);
char getPredioFace(ItemPredio);

#endif
