#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"formasBase.h"
#include"torre.h"

struct torre{
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

ItemTorre torreNew(char id[], double x, double y, int* sizeofItem){
  struct torre *essa = malloc(sizeof(struct torre));
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  strcpy(essa->ID, id);
  essa->strkW = stroke;
  essa->x = x;
  essa->y = y;
  *sizeofItem = sizeof(struct torre);

  return essa;
}

void torreDraw(ItemTorre item, FILE* dir){
  struct torre *essa = item;
  draw_c(radius, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
  draw_l(essa->x, essa->y, essa->x, essa->y+15, essa->corStroke, dir);
}

void torreSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void torreSetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void torreSetStroke(double pStroke){
  stroke = pStroke;
}

char* torreGetId(ItemTorre item){
  struct torre *essa = item;
  return essa->ID;
}
double torreGetX(ItemTorre item){
  struct torre *essa = item;
  return essa->x;
}
double torreGetY(ItemTorre item){
  struct torre *essa = item;
  return essa->y;
}

void torreSetID(ItemTorre item, char pId[]){
  struct torre *essa = item;
  strcpy(essa->ID, pId);
}
void torreSetX(ItemTorre item, double pX){
  struct torre *essa = item;
  essa->x = pX;
}
void torreSetY(ItemTorre item, double pY){
  struct torre *essa = item;
  essa->y = pY;
}
