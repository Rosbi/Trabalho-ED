#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"formasBase.h"
#include"semaforo.h"

struct semaforo{
  char ID[15];
  char corStroke[22];
  char corFill[22];
  double strkW;
  double x;
  double y;
};

static char cor1[22] = "magenta";
static char cor2[22] = "green";
static double stroke = 1.0;
static double width = 5.0;
static double height = 10.0;

ItemSemaforo semaforoNew(char id[], double x, double y, int* sizeofItem){
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
  draw_t(essa->x+(width/2)-2, essa->y+(height/2)+2, "S", dir);
}

void semaforoSetCorstroke(char pCor[]){
  strcpy(cor1, pCor);
}
void semaforoSetCorfill(char pCor[]){
  strcpy(cor2, pCor);
}
void semaforoSetStroke(double pStroke){
  stroke = pStroke;
}

char* semaforoGetId(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->ID;
}
double semaforoGetX(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->x;
}
double semaforoGetY(ItemSemaforo item){
  struct semaforo *essa = item;
  return essa->y;
}

void semaforoSetID(ItemSemaforo item, char pId[]){
  struct semaforo *essa = item;
  strcpy(essa->ID, pId);
}
void semaforoSetX(ItemSemaforo item, double pX){
  struct semaforo *essa = item;
  essa->x = pX;
}
void semaforoSetY(ItemSemaforo item, double pY){
  struct semaforo *essa = item;
  essa->y = pY;
}
void semaforoSetStrokeW(ItemSemaforo item, double pW){
  struct semaforo *essa = item;
  essa->strkW = pW;
}
void semaforoSetCorStrokeItem(ItemSemaforo item, char* pCor){
  struct semaforo *essa = item;
  strcpy(essa->corStroke, pCor);
}
