#ifndef QUADRA_H
#define QUADRA_H

#include<stdio.h>

typedef void* ItemQuadra;

ItemQuadra quadraNew(double, double, double, double, char[], int*); /*Parametros: coordenadas x e y da quadra, largura, altura e CEP
                                                                      Retorno: void* que aponta para uma struct quadra com as especificacoes acima*/

void quadraDraw(ItemQuadra, FILE*);                        //Desenha no svg (FILE*) o ItemQuadra desejado

//setters de variaveis globais. Altera a as cores e bordas das novas quadras
void quadraSetCorstroke(char[]);
void quadraSetCorfill(char[]);
void quadraSetStroke(double);

//getters
char* quadraGetCep(ItemQuadra);
double quadraGetX(ItemQuadra);
double quadraGetY(ItemQuadra);
double quadraGetW(ItemQuadra);
double quadraGetH(ItemQuadra);

//setters
void quadraSetCep(ItemQuadra, char[]);
void quadraSetX(ItemQuadra, double);
void quadraSetY(ItemQuadra, double);
void quadraSetW(ItemQuadra, double);
void quadraSetH(ItemQuadra, double);
void quadraSetThisStroke(ItemQuadra, char[]);

#endif
