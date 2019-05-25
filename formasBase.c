#include<stdio.h>
#include<string.h>
#include"formasBase.h"

struct formaBase{
  char tipo;
  int i;
  char corStroke[22];
  char corFill[22];
  float strkW;
  float x;
  float y;
  float r;
  float w;
  float h;
};

static char cor1[22] = "magenta";
static char cor2[22] = "black";
static float stroke = 1.0;

Forma retanguloNew(int i, float x, float y, float w, float h){
  struct formaBase *essa = malloc(sizeof(struct formaBase));
  essa->tipo = 'r';
  essa->i = i;
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  essa->strW = stroke;
  essa->x = x;
  essa->y = y;
  essa->w = w;
  essa->h = h;
  essa->r = NULL;

  return essa;
}
Forma circuloNew(int i, float x, float y, float r){
  struct formaBase *essa = malloc(sizeof(struct formaBase));
  essa->tipo = 'c';
  essa->i = i;
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  essa->strW = stroke;
  essa->x = x;
  essa->y = y;
  essa->r = r;
  essa->w = NULL;
  essa->h = NULL;

  return essa;
}

void formaDraw(Forma form, FILE* dir){
  struct formaBase *essa = form;
  switch(essa->tipo){
    case 'r':
      draw_r(essa->w, essa->h, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strW, 1, dir);
      break;
    case 'c':
      draw_c(essa->r, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strW, 1, dir);
      break;
  }
}

void formaSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void formaSetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void formaSetStroke(float pStroke){
  stroke = pStroke;
}

void formaSetX(Forma form, float pX){
  struct formaBase *essa = form;
  essa->x = pX;
}
void formaSetY(Forma form, float pY){
  struct formaBase *essa = form;
  essa->y = pY;
}
void formaSetW(Forma form, float pW){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    essa->w = pW;
}
void formaSetH(Forma form, float pH){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    essa->h = pH;
}
void formaSetR(Forma form, float pR){
  struct formaBase *essa = form;
  if(essa->tipo == 'c')
    essa->r = pR;
}

void draw_c(float r, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir){
  fprintf(dir, "\t<circle r=\"%f\" cx=\"%f\" cy=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", r, x, y, cor1, cor2, stroke, opacity);
}
void draw_r(float w, float h, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", w, h, x, y, cor1, cor2, stroke, opacity);
}
void draw_t(float x, float y, char texto[], FILE* dir){
  fprintf(dir, "\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>\n", x, y, texto);
}
void draw_e(float x, float y, float rx, float ry, char cor1[], char cor2[], FILE* dir, float opacity){
  fprintf(dir, "\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", x, y, rx, ry, cor1, cor2, opacity);
}
void draw_l(float x1, float y1, float x2, float y2, char cor[], FILE *dir){
  fprintf(dir, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"0.5\"/>\n", x1, y1, x2, y2, cor);
}
void draw_r_dash(float w, float h, float x, float y, char cor[], FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"white\" stroke-width=\"0.5\" stroke-dasharray=\"5,5\" fill-opacity=\"0.0\"/>\n", w, h, x, y, cor);
}
