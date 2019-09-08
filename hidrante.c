#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"formasBase.h"
#include"hidrante.h"

struct hidrante{
  char ID[15];
  char corStroke[22];
  char corFill[22];
  double strkW;
  double x;
  double y;
};

static char cor1[22] = "magenta";
static char cor2[22] = "black";
static double stroke = 1.0;
static double radius = 5.0;

ItemHidrante hidranteNew(char id[], double x, double y, int* sizeofItem){
  struct hidrante *essa = malloc(sizeof(struct hidrante));
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  strcpy(essa->ID, id);
  essa->strkW = stroke;
  essa->x = x;
  essa->y = y;
  *sizeofItem = sizeof(struct hidrante);

  return essa;
}

void hidranteDraw(ItemHidrante item, FILE* dir){
  struct hidrante *essa = item;
  draw_c(radius, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
  draw_t(essa->x-2, essa->y+2, "H", dir);
}

void hidranteSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void hidranteSetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void hidranteSetStroke(double pStroke){
  stroke = pStroke;
}

char* hidranteGetId(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->ID;
}
double hidranteGetX(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->x;
}
double hidranteGetY(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->y;
}

void hidranteSetStrokeW(ItemHidrante item, double pW){
  struct hidrante *essa = item;
  essa->strkW = pW;
}
void hidranteSetID(ItemHidrante item, char pId[]){
  struct hidrante *essa = item;
  strcpy(essa->ID, pId);
}
void hidranteSetX(ItemHidrante item, double pX){
  struct hidrante *essa = item;
  essa->x = pX;
}
void hidranteSetY(ItemHidrante item, double pY){
  struct hidrante *essa = item;
  essa->y = pY;
}
void hidranteSetCorStrokeItem(ItemHidrante item, char pCor[]){
  struct hidrante *essa = item;
  strcpy(essa->corStroke, pCor);
}
