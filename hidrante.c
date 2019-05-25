#include<string.h>
#inclide"formasBase.h"
#include"hidrante.h"

struct hidrante{
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

ItemHidrante hidranteNew(char id[], float x, float y){
  struct hidrante *essa = malloc(sizeof(struct hidrante));
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  strcpy(essa->ID, id);
  essa->strkW = stroke;
  essa->x = x;
  essa->y = y;

  return essa;
}

void hidranteDraw(ItemHidrante item, FILE* dir){
  struct hidrante *essa = item;
  draw_c(-1, radius, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strW, 1, dir);
  draw_t(essa->x, essa->y, "H", dir);
}

void hidranteSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void hidranteSetCorfill(char pCor[]){
  strcpy(cor1, pCor);
}
void hidranteSetStroke(float pStroke){
  stroke = pStroke;
}

char[] hidranteGetId(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->ID;
}
float hidranteGetX(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->x;
}
float hidranteGetY(ItemHidrante item){
  struct hidrante *essa = item;
  return essa->y;
}

void hidranteSetID(ItemHidrante item, char pId[]){
  struct hidrante *essa = item;
  strcpy(essa->ID, pId);
}
void hidranteSetX(ItemHidrante item, float pX){
  struct hidrante *essa = item;
  essa->x = pX;
}
void hidranteSetY(ItemHidrante item, float pY){
  struct hidrante *essa = item;
  essa->y = pY;
}
