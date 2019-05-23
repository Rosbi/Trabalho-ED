#ifndef FORMAS_H
#define FORMAS_H

typedef struct elemento{
  char tipo;
  int i;
  float x;
  float y;
  float r;
  float w;
  float h;
  char cor1[22];
  char cor2[22];
  char texto[255];
  struct elemento *prox;
}Elemento;

float func_min(float a, float b);
float func_max(float a, float b);

void draw_c(int i, float r, float x, float y, char cor1[], char cor2[], FILE* dir, float opacity);

void draw_r(int i, float w, float h, float x, float y, char cor1[], char cor2[], FILE* dir, float opacity);

void draw_t(float x, float y, char texto[], FILE* dir);

void draw_e(float x, float y, float rx, float ry, char cor1[], char cor2[], FILE* dir, float opacity);

void draw_l(float x1, float y1, float x2, float y2, char cor[], FILE *dir);

void draw_r_dash(float w, float h, float x, float y, char cor[], FILE* dir);

#endif
