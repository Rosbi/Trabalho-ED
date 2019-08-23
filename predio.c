#include<stdlib.h>
#include<string.h>
#include"geometria.h"
#include"quadra.h"
#include"formasBase.h"
#include"predio.h"

struct predio{
  char cep[20];
  char face;
  double num;
  Reta cima;
  Reta direita;
  Reta esquerda;
  Reta baixo;
};

ItemPredio predioNew(char cep[], char face, double num, double frente, double profundidade, double margem, ItemQuadra quad, int* sizeofItem){
  struct predio *essa = malloc(sizeof(struct predio));
  *sizeofItem = sizeof(struct predio);
  strcpy(essa->cep, cep);
  essa->face = face;
  essa->num = num;

  double qx = quadraGetX(quad);
  double qy = quadraGetY(quad);
  double qw = quadraGetW(quad);
  double qh = quadraGetH(quad);
  double x, y, w, h;

  if(face == 'N' || face == 'S'){
    x = qx + (num - (frente/2));
    if(face == 'N')
      y = qy + margem;
    else
      y = qy + qh - (margem + profundidade);
    w = frente;
    h = profundidade;
  }
  else{
    y = qy + (num - (frente/2));
    if(face == 'L')
      x = qx + qw - (margem + profundidade);
    else
      x = qx + margem;
    w = profundidade;
    h = frente;
  }

  essa->cima = criarReta(criarPonto(x, y), criarPonto(x+w, y));
  essa->esquerda = criarReta(criarPonto(x, y), criarPonto(x, y+h));
  essa->direita = criarReta(criarPonto(x+w, y), criarPonto(x+w, y+h));
  essa->baixo = criarReta(criarPonto(x, y+h), criarPonto(x+w, y+h));
  return essa;
}

void predioDraw(ItemPredio item, FILE* out){
  struct predio *essa = item;
  double x, y, w, h;
  char num[10];
  sprintf(num, "%d", (int)essa->num);
  x = getPontoX(getRetaA(essa->cima));
  y = getPontoY(getRetaA(essa->cima));
  w = getRetaTamanho(essa->cima);
  h = getRetaTamanho(essa->esquerda);
  draw_r(w, h, x, y, "black", "blue", 2, 1, out);
  draw_t(x+w/2, y+h/2, num, out);
}
Reta getPredioCima(ItemPredio pp){
  struct predio *essa = pp;
  return essa->cima;
}
Reta getPredioEsquerda(ItemPredio pp){
  struct predio *essa = pp;
  return essa->esquerda;
}
Reta getPredioDireita(ItemPredio pp){
  struct predio *essa = pp;
  return essa->direita;
}
Reta getPredioBaixo(ItemPredio pp){
  struct predio *essa = pp;
  return essa->baixo;
}
char getPredioFace(ItemPredio pp){
  struct predio *essa = pp;
  return essa->face;
}
