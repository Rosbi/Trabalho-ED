#ifndef TORRE_H
#define TORRE_H

#include<stdio.h>

typedef void* ItemTorre;

/*  Esse TAD tem como base o hidante.h, para qualquer dúvida, consultar o mesmo
//  Qaulquer função com aplicação diferente estará comentada aqui
*/

ItemTorre torreNew(char[], double, double, int*);

void torreDraw(ItemTorre, FILE*);

void torreSetCorstroke(char[]);
void torreSetCorfill(char[]);
void torreSetStroke(double);

char* torreGetId(ItemTorre);
double torreGetX(ItemTorre);
double torreGetY(ItemTorre);

void torreSetID(ItemTorre, char[]);
void torreSetX(ItemTorre, double);
void torreSetY(ItemTorre, double);

#endif
