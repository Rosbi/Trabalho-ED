#ifndef SEMAFORO_H
#define SEMAFORO_H

typedef void* ItemSemaforo;

ItemSemaforo semaforoNew(char[], float, float);

void semaforoDraw(ItemSemaforo, FILE*);

void semaforoSetCorstroke(char[]);
void semaforoSetCorfill(char[]);
void semaforoSetStroke(float);

char[] semaforoGetId(ItemSemaforo);
float semaforoGetX(ItemSemaforo);
float semaforoGetY(ItemSemaforo);

void semaforoSetID(ItemSemaforo, char[]);
void semaforoSetX(ItemSemaforo, float);
void semaforoSetY(ItemSemaforo, float);

#endif
