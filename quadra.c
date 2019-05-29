#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"quadra.h"
#include"formasBase.h"

struct quadra{
  char cep[15];
  char corStroke[22];
  char corFill[22];
  float strkW;
  float x;
  float y;
  float w;
  float h;
};

static char cor1[22] = "magenta";
static char cor2[22] = "black";
static float stroke = 1.0;

ItemQuadra quadraNew(float x, float y, float w, float h, char cep[], int* sizeofItem){
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
  draw_t(essa->x, essa->y, essa->cep, dir);
}

void quadraSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void quadrasetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void quadraSetStroke(float pStr){
  stroke = pStr;
}

char* quadraGetCep(ItemQuadra item){
  struct quadra *essa = item;
  return essa->cep;
}
float quadraGetX(ItemQuadra item){
  struct quadra *essa = item;
  return essa->x;
}
float quadraGetY(ItemQuadra item){
  struct quadra *essa = item;
  return essa->y;
}
float quadraGetW(ItemQuadra item){
  struct quadra *essa = item;
  return essa->w;
}
float quadraGetH(ItemQuadra item){
  struct quadra *essa = item;
  return essa->h;
}

void quadraSetCep(ItemQuadra item, char pCep[]){
  struct quadra *essa = item;
  strcpy(essa->cep, pCep);
}
void quadraSetX(ItemQuadra item, float pX){
  struct quadra *essa = item;
  essa->x = pX;
}
void quadraSetY(ItemQuadra item, float pY){
  struct quadra *essa = item;
  essa->y = pY;
}
void quadraSetW(ItemQuadra item, float pW){
  struct quadra *essa = item;
  essa->w = pW;
}
void quadraSetH(ItemQuadra item, float pH){
  struct quadra *essa = item;
  essa->h = pH;
}
