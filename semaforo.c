#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"formasBase.h"
#include"semaforo.h"

struct semaforo{
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
static float width = 15.0;
static float height = 5.0;

ItemSemaforo semaforoNew(char id[], float x, float y, int* sizeofItem){
  struct semaforo *essa = malloc(sizeof(struct semaforo));
  strcpy(essa->corStroke, cor1);
  strcpy(essa->corFill, cor2);
  strcpy(essa->ID, id);
  essa->strkW = stroke;
  essa->x = x;
  essa->y = y;
  *sizeofItem = sizeof(struct semaforo);

  return essa;
}

void semaforoDraw(ItemSemaforo item, FILE* dir){
  struct semaforo *essa = item;
  draw_r(width, height, essa->x, essa->y, essa->corStroke, essa->corFill, essa->strkW, 1, dir);
  draw_t(essa->x+(width/2), essa->y+(height/2), "S", dir);
}

void semaforoSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void semaforoSetCorfill(char pCor[]){
  strcpy(cor1, pCor);
}
void semaforoSetStroke(float pStroke){
  stroke = pStroke;
}

char* semaforoGetId(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->ID;
}
float semaforoGetX(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->x;
}
float semaforoGetY(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->y;
}

void semaforoSetID(ItemSemaforo item, char pId[]){
  struct semaforo *essa = item;
  strcpy(essa->ID, pId);
}
void semaforoSetX(ItemSemaforo item, float pX){
  struct semaforo *essa = item;
  essa->x = pX;
}
void semaforoSetY(ItemSemaforo item, float pY){
  struct semaforo *essa = item;
  essa->y = pY;
}
