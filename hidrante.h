#ifndef HIDRANTE_H
#define HIDRANTE_H

#include<stdio.h>

typedef void* ItemHidrante;

/*  Esse .h possui funções relacionadas à TAD hidrante
//  NOTA: não passar o valor NULL ou qualquer outro TAD para as funções aqui
*/

//  Retorna o endereço do hidrante criado
//  sizeofItem é o tamanho em bytes da struct hidrante, o valor int recebido é ignorado
ItemHidrante hidranteNew(char id[], double x, double y, int* sizeofItem);

//  Desenha o hidrante no arquivo dest
void hidranteDraw(ItemHidrante hid, FILE* dest);

//  As funções a seguir alteram as caracteristicas padrão dos hidrantes
void hidranteSetCorstroke(char novaCor[]);
void hidranteSetCorfill(char novaCor[]);
void hidranteSetStroke(double novoStroke);

//  As funções a seguir retornam a caracteristica desejada de um hidrante
char* hidranteGetId(ItemHidrante);
double hidranteGetX(ItemHidrante);
double hidranteGetY(ItemHidrante);

//  As funções a seguir alteram a caracteristica desejada de um hidrante especificado
void hidranteSetID(ItemHidrante, char[]);
void hidranteSetStrokeW(ItemHidrante, double);
void hidranteSetX(ItemHidrante, double);
void hidranteSetY(ItemHidrante, double);
void hidranteSetCorStrokeItem(ItemHidrante, char[]);

#endif
