#include<string.h>
#inclide"formasBase.h"
#include"torre.h"

struct torre{
  char ID[15];
  char corStroke[22];
  char corFill[22];
  float strkW;
  float x;
  float y;
};

static char cor1[22] = "magenta";
static char cor2[22] = "black";
static float stroke = 1.0;
static float radius = 5.0;

ItemTorre torreNew(char id[], float x, float y, int* sizeofItem){
  struct torre *essa = malloc(sizeof(struct torre));
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  strcpy(essa->ID, id);
  essa->strkW = stroke;
  essa->x = x;
  essa->y = y;
  sizeofItem = sizeof(struct torre);

  return essa;
}

void torreDraw(ItemTorre item, FILE* dir){
  struct torre *essa = item;
  draw_c(-1, radius, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strW, 1, dir);
  draw_l(essa->x, essa->y, essa->x, essa->y+15, essa->cor1, dir);
}

void torreSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void torreSetCorfill(char pCor[]){
  strcpy(cor1, pCor);
}
void torreSetStroke(float pStroke){
  stroke = pStroke;
}

char[] torreGetId(ItemTorre item){
  struct torre *essa = item;
  return essa->ID;
}
float torreGetX(ItemTorre item){
  struct torre *essa = item;
  return essa->x;
}
float torreGetY(ItemTorre item){
  struct torre *essa = item;
  return essa->y;
}

void torreSetID(ItemTorre item, char pId[]){
  struct torre *essa = item;
  strcpy(essa->ID, pId);
}
void torreSetX(ItemTorre item, float pX){
  struct torre *essa = item;
  essa->x = pX;
}
void torreSetY(ItemTorre item, float pY){
  struct torre *essa = item;
  essa->y = pY;
}
