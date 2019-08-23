#ifndef SVG_H
#define SVG_H

#include"lista.h"

enum tipoListas{e_formas, e_quadras, e_hidrantes, e_semaforos, e_torres, e_predios, e_muros, e_textos};

void inicializarListas(char*, Lista[]);

void create_svg(char[]);
void finalize_svg(char[]);

void draw_svg(Lista[], FILE*);

#endif
