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
  double strkW;
  double x;
  double y;
  double r;
  double w;
  double h;
};

static double strokeC = 1.0;
static double strokeR = 1.0;

Forma retanguloNew(int i, double x, double y, double w, double h, char cor1[], char cor2[], int* sizeofItem){
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
Forma circuloNew(int i, double x, double y, double r, char cor1[], char cor2[], int* sizeofItem){
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
Forma textoNew(char text[], double x, double y, int* sizeofItem){
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

void formaSetStroke(double pStrokeC, double pStrokeR){
  strokeC = pStrokeC;
  strokeR = pStrokeR;
}

void formaSetX(Forma form, double pX){
  struct formaBase *essa = form;
  essa->x = pX;
}
void formaSetY(Forma form, double pY){
  struct formaBase *essa = form;
  essa->y = pY;
}
void formaSetW(Forma form, double pW){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    essa->w = pW;
}
void formaSetH(Forma form, double pH){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    essa->h = pH;
}
void formaSetR(Forma form, double pR){
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

double formaGetX(Forma form){
  struct formaBase *essa = form;
  return essa->x;
}
double formaGetY(Forma form){
  struct formaBase *essa = form;
  return essa->y;
}
double formaGetR(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'c')
    return essa->r;
  else
    return -1;
}
double formaGetW(Forma form){
  struct formaBase *essa = form;
  if(essa->tipo == 'r')
    return essa->w;
  else
    return -1;
}
double formaGetH(Forma form){
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

void draw_r(double w, double h, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", w, h, x, y, cor1, cor2, stroke, opacity);
}
void draw_c(double r, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir){
  fprintf(dir, "\t<circle r=\"%f\" cx=\"%f\" cy=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-opacity=\"%f\"/>\n", r, x, y, cor1, cor2, stroke, opacity);
}
void draw_e(double x, double y, double rx, double ry, char cor1[], char cor2[], double opacity, FILE* dir){
  fprintf(dir, "\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", x, y, rx, ry, cor1, cor2, opacity);
}
void draw_r_dash(double w, double h, double x, double y, char cor[], FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"white\" stroke-width=\"0.5\" stroke-dasharray=\"5,5\" fill-opacity=\"0.0\"/>\n", w, h, x, y, cor);
}
void draw_l(double x1, double y1, double x2, double y2, char cor[], FILE *dir){
  fprintf(dir, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"1\"/>\n", x1, y1, x2, y2, cor);
}
void draw_t(double x, double y, char texto[], FILE* dir){
  fprintf(dir, "\t<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"6\">%s\t</text>\n", x, y, texto);
}
