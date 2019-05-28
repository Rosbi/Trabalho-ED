#ifndef SVG_H
#define SVG_H
#include"lista.h"

void inicializarListas(char*, int[], Lista[]);)

void draw_svg(Lista[], char[]);

Elemento *novo_elem(FILE* geo, FILE* out, char tipo, Elemento *elem);

void end_list(Elemento *elem);

#endif
