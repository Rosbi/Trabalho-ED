#ifndef TORRE_H
#define TORRE_H

typedef void* ItemTorre;

ItemTorre torreNew(char[], float, float, int*);

void torreDraw(ItemTorre, FILE*);

void torreSetCorstroke(char[]);
void torreSetCorfill(char[]);
void torreSetStroke(float);

char[] torreGetId(ItemTorre);
float torreGetX(ItemTorre);
float torreGetY(ItemTorre);

void torreSetID(ItemTorre, char[]);
void torreSetX(ItemTorre, float);
void torreSetY(ItemTorre, float);

#endif
