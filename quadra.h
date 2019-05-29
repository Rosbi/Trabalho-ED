#ifndef QUADRA_H
#define QUADRA_H

#include<stdio.h>

typedef void* ItemQuadra;

ItemQuadra quadraNew(float, float, float, float, char[], int*); /*Parametros: coordenadas x e y da quadra, largura, altura e CEP
                                                                Retorno: void* que aponta para uma struct quadra com as especificacoes acima*/

void quadraDraw(ItemQuadra, FILE*);                        //Desenha no svg (FILE*) o ItemQuadra desejado

//setters de variaveis globais. Altera a as cores e bordas das novas quadras
void quadraSetCorstroke(char[]);
void quadraSetCorfill(char[]);
void quadraSetStroke(float);

//getters
char* quadraGetCep(ItemQuadra);
float quadraGetX(ItemQuadra);
float quadraGetY(ItemQuadra);
float quadraGetW(ItemQuadra);
float quadraGetH(ItemQuadra);

//setters
void quadraSetCep(ItemQuadra, char[]);
void quadraSetX(ItemQuadra, float);
void quadraSetY(ItemQuadra, float);
void quadraSetW(ItemQuadra, float);
void quadraSetH(ItemQuadra, float);

#endif
