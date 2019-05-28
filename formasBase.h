#ifndef FORMAS_H
#define FORMAS_H

typedef void* Forma;

Forma retanguleNew(int, float, float, float, float, char[], char[], int*);
Forma circuloNew(int, float, float, float, char[], char[], int*);
Fotma textoNew(char[], float, float, int*);

void formaDraw(Forma, FILE*);

void formaSetStroke(float, float);

void formaSetX(Forma, float);
void formaSetY(Forma, float);
void formaSetW(Forma, float);
void formaSetH(Forma, float);
void formaSetR(Forma, float);
void formaSetCorstroke(Forma, char[]);
void formaSetCorfill(Forma, char[]);

float formaGetX(Forma);
float formaGetY(Forma);
float formaGetR(Forma);
float formaGetW(Forma);
float formaGetH(Forma);
char formaGetTipo(Forma);
int formaGetID(Forma);

void draw_r(float w, float h, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir);
void draw_c(float r, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir);
void draw_e(float x, float y, float rx, float ry, char cor1[], char cor2[], float opacity, FILE* dir);
void draw_r_dash(float w, float h, float x, float y, char cor[], FILE* dir);
void draw_l(float x1, float y1, float x2, float y2, char cor[], FILE *dir);
void draw_t(float x, float y, char texto[], FILE* dir);

#endif
