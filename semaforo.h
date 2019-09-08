#ifndef SEMAFORO_H
#define SEMAFORO_H

#include<stdio.h>

typedef void* ItemSemaforo;

/*  Esse TAD tem como base o hidante.h, para qualquer dúvida, consultar o mesmo
//  Qaulquer função com aplicação diferente estará comentada aqui
*/

ItemSemaforo semaforoNew(char[], double, double, int*);

void semaforoDraw(ItemSemaforo, FILE*);

void semaforoSetCorstroke(char[]);
void semaforoSetCorfill(char[]);
void semaforoSetStroke(double);

char* semaforoGetId(ItemSemaforo);
double semaforoGetX(ItemSemaforo);
double semaforoGetY(ItemSemaforo);

void semaforoSetID(ItemSemaforo, char[]);
void semaforoSetStrokeW(ItemSemaforo, double);
void semaforoSetX(ItemSemaforo, double);
void semaforoSetY(ItemSemaforo, double);
void semaforoSetCorStrokeItem(ItemSemaforo, char[]);

#endif
