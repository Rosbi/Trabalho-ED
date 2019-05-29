#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"formasBase.h"

struct formaBase{
  char tipo;
  int i;
  char corStroke[22];
  char corFill[22];
  char text[255];
  float strkW;
  float x;
  float y;
  float r;
  float w;
  float h;
};

static float strokeC = 1.0;
static float strokeR = 1.0;

Forma retanguloNew(int i, float x, float y, float w, float h, char cor1[], char cor2[], int* sizeofItem){
  struct formaBase *essa = malloc(sizeof(struct formaBase));
  essa->tipo = 'r';
  essa->i = i;
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  essa->strkW = strokeR;
  essa->x = x;
  essa->y = y;
  essa->w = w;
  essa->h = h;
  *sizeofItem = sizeof(struct formaBase);

  return essa;
}
Forma circuloNew(int i, float x, float y, float r, char cor1[], char cor2[], int* sizeofItem){
  struct formaBase *essa = malloc(sizeof(struct formaBase));
  essa->tipo = 'c';
  essa->i = i;
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  essa->strkW = strokeC;
  essa->x = x;
  essa->y = y;
  essa->r = r;
  *sizeofItem = sizeof(struct formaBase);

  return essa;
}
Forma textoNew(char text[], float x, float y, int* sizeofItem){
  struct formaBase *essa = malloc(sizeof(struct formaBase));
  essa->tipo = 't';
  essa->x = x;
  essa->y = y;
  strcpy(essa->text, text);
  *sizeofItem = sizeof(struct formaBase);

  return essa;
}

void formaDraw(Forma form, FILE* dir){
  struct formaBase *essa = form;
  switch(essa->tipo){
    case 'r':
      draw_r(essa->w, essa->h, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
      break;
    case 'c':
      draw_c(essa->r, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
      break;
    case 't':
      draw_t(essa->x, essa->y, essa->text, dir);
      break;
  }
}

void formaSetStroke(float pStrokeC, float pStrokeR){
  strokeC = pStrokeC;
  strokeR = pStrokeR;
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
void formaSetCorstroke(Forma form, char pCor[]){
  struct formaBase *essa = form;
  strcpy(essa->corStroke, pCor);
}
void formaSetCorfill(Forma form, char pCor[]){
  struct formaBase *essa = form;
  strcpy(essa->corFill, pCor);
}

float formaGetX(Forma form){
  struct formaBase *essa = form;
  return essa->x;
}
float formaGetY(Forma form){
  struct formaBase *essa = form;
  return essa->y;
}
float formaGetR(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'c')
    return essa->r;
  else
    return -1;
}
float formaGetW(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    return essa->w;
  else
    return -1;
}
float formaGetH(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    return essa->h;
  else
    return -1;
}
char formaGetTipo(Forma form){
  struct formaBase *essa = form;
  return essa->tipo;
}
int formaGetID(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'c' || essa->tipo == 'r')
    return essa->i;
  else
    return -1;
}
char* formaGetTexto(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 't')
    return essa->text;
}

void draw_r(float w, float h, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", w, h, x, y, cor1, cor2, stroke, opacity);
}
void draw_c(float r, float x, float y, char cor1[], char cor2[], float stroke, float opacity, FILE* dir){
  fprintf(dir, "\t<circle r=\"%f\" cx=\"%f\" cy=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", r, x, y, cor1, cor2, stroke, opacity);
}
void draw_e(float x, float y, float rx, float ry, char cor1[], char cor2[], float opacity, FILE* dir){
  fprintf(dir, "\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", x, y, rx, ry, cor1, cor2, opacity);
}
void draw_r_dash(float w, float h, float x, float y, char cor[], FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"white\" stroke-width=\"0.5\" stroke-dasharray=\"5,5\" fill-opacity=\"0.0\"/>\n", w, h, x, y, cor);
}
void draw_l(float x1, float y1, float x2, float y2, char cor[], FILE *dir){
  fprintf(dir, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"0.5\"/>\n", x1, y1, x2, y2, cor);
}
void draw_t(float x, float y, char texto[], FILE* dir){
  fprintf(dir, "\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>\n", x, y, texto);
}
