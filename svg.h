#ifndef SVG_H
#define SVG_H
#include"formas.h"

Elemento *novo_elem(FILE* geo, FILE* out, char tipo, Elemento *elem);

Elemento *create_base_svg(char *nArqGeo, char *dDir, int *size);

void draw_svg(Elemento *elem, FILE* out, char tipo);

Elemento *novo_elem(FILE* geo, FILE* out, char tipo, Elemento *elem);

void end_list(Elemento *elem);

#endif
