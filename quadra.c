#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"quadra.h"
#include"formasBase.h"

struct quadra{
  char cep[20];
  char corStroke[22];
  char corFill[22];
  double strkW;
  double x;
  double y;
  double w;
  double h;
};

static char cor1[22] = "magenta";
static char cor2[22] = "black";
static double stroke = 1.0;

ItemQuadra quadraNew(double x, double y, double w, double h, char cep[], int* sizeofItem){
  struct quadra *essa = malloc(sizeof(struct quadra));
  strcpy(essa->cep, cep);
  essa->x = x;
  essa->y = y;
  essa->w = w;
  essa->h = h;
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  essa->strkW = stroke;
  *sizeofItem = sizeof(struct quadra);

  return essa;
}

void quadraDraw(ItemQuadra item, FILE* dir){
  struct quadra *essa = item;
  draw_r(essa->w, essa->h, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
  draw_t(essa->x+(essa->w/2), essa->y+(essa->h/2), essa->cep, dir);
}

void quadraSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void quadraSetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void quadraSetStroke(double pStr){
  stroke = pStr;
}

char* quadraGetCep(ItemQuadra item){
  struct quadra *essa = item;
  return essa->cep;
}
double quadraGetX(ItemQuadra item){
  struct quadra *essa = item;
  return essa->x;
}
double quadraGetY(ItemQuadra item){
  struct quadra *essa = item;
  return essa->y;
}
double quadraGetW(ItemQuadra item){
  struct quadra *essa = item;
  return essa->w;
}
double quadraGetH(ItemQuadra item){
  struct quadra *essa = item;
  return essa->h;
}

void quadraSetCep(ItemQuadra item, char pCep[]){
  struct quadra *essa = item;
  strcpy(essa->cep, pCep);
}
void quadraSetX(ItemQuadra item, double pX){
  struct quadra *essa = item;
  essa->x = pX;
}
void quadraSetY(ItemQuadra item, double pY){
  struct quadra *essa = item;
  essa->y = pY;
}
void quadraSetW(ItemQuadra item, double pW){
  struct quadra *essa = item;
  essa->w = pW;
}
void quadraSetH(ItemQuadra item, double pH){
  struct quadra *essa = item;
  essa->h = pH;
}
void quadraSetThisStroke(ItemQuadra item, char pCor[]){
  struct quadra *essa = item;
  strcpy(essa->corStroke, pCor);
}
