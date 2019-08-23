#include<stdio.h>
#include<stdlib.h>
#include"geometria.h"
#include"muro.h"
#include"formasBase.h"

struct muro{
  Reta parede;
};

ItemMuro muroNew(Ponto a, Ponto b, int* sizeofItem){
  struct muro *m = malloc(sizeof(struct muro));
  *sizeofItem = retaSizeof();
  m->parede = criarReta(a, b);
  return m;
}

void muroDraw(ItemMuro mur, FILE* out){
  struct muro *essa = mur;
  double x1 = getPontoX(getRetaA(essa->parede));
  double y1 = getPontoY(getRetaA(essa->parede));
  double x2 = getPontoX(getRetaB(essa->parede));
  double y2 = getPontoY(getRetaB(essa->parede));
  draw_l(x1, y1, x2, y2, "black", out);
}
