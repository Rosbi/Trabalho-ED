#ifndef FORMAS_H
#define FORMAS_H

typedef void* Forma;

Forma retanguleNew(int, float, float, float, float);
Forma circuloNew(int, float, float, float);

void formaDraw(Forma, FILE*);

void formaSetCorstroke(char);
void formaSetCorfill(char);
void formaSetStroke(float);

void formaSetX(Forma, float);
void formaSetY(Forma, float);
void formaSetW(Forma, float);
void formaSetH(Forma, float);
void formaSetR(Forma, float);

void draw_c(float, float, float, char, char, FILE*, float);
void draw_r(float, float, float, float, char, char, FILE*, float);
void draw_t(float, float, char, FILE*);
void draw_e(float, float, float, float, char, char, FILE*, float);
void draw_l(float, float, float, float, char, FILE*);
void draw_r_dash(float, float, float, float, char, FILE*);

#endif
