#ifndef PREDIO_H
#define PREDIO_H

#include<stdio.h>
#include"geometria.h"

typedef void* ItemPredio;

/*  Esse TAD tem como base o hidante.h, para qualquer dúvida, consultar o mesmo
//  Qaulquer função com aplicação diferente estará comentada aqui
*/

ItemPredio predioNew(char* cep, char face, double num, double frente, double profundidade, double margem, ItemQuadra quadra, int* sizeofItem);

void predioDraw(ItemPredio, FILE*);

//  Retorna a reta equivalente ao lado do prédio desejado
Reta getPredioCima(ItemPredio);
Reta getPredioEsquerda(ItemPredio);
Reta getPredioDireita(ItemPredio);
Reta getPredioBaixo(ItemPredio);
//  Retorna a face do prédio
char getPredioFace(ItemPredio);
char* getPredioCep(ItemPredio);
double getPredioNum(ItemPredio);

#endif
