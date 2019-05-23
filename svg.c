#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"formas.h"

Elemento *novo_elem(FILE* geo, FILE* out, char tipo, Elemento *elem);

Elemento *create_base_svg(char *nArqGeo, char *dDir, int *size){
  Elemento *elem;
  char tipo;
  FILE* out = fopen(dDir, "w");
  FILE* geo = fopen(nArqGeo, "r");

  if (!out || !geo){
    printf("ERRO AO ABRIR O ARQUIVO GEO OU CRIAR O SVG\n");
    exit(-1);
  }

  fscanf(geo, "%s", &tipo);
  if(tipo=='n'){
    fscanf(geo, "%d", size);
  }
  else
    fseek(geo, 0, SEEK_SET);

  fprintf(out, "<svg width=\"%d\" height=\"%d\">\n", 10000, 10000);

  elem = NULL;
  while(!feof(geo)){
    fscanf(geo, "%c", &tipo);
    if(tipo=='c' || tipo=='r' || tipo=='t')
      elem = novo_elem(geo, out, tipo, elem);
  }

  fprintf(out, "</svg>");
  fclose(geo);
  fclose(out);

return elem;
}

void draw_svg(Elemento *elem, FILE* out, char tipo){
  switch (tipo){
    case 'c':
      draw_c(elem->i, elem->r, elem->x, elem->y, elem->cor1, elem->cor2, out, 1);
      break;
    case 'r':
      draw_r(elem->i, elem->w, elem->h, elem->x, elem->y, elem->cor1, elem->cor2, out, 1);
      break;
    case 't':
      draw_t(elem->x, elem->y, elem->texto, out);
      break;
  }
}

Elemento *novo_elem(FILE* geo, FILE* out, char tipo, Elemento *elem){
  Elemento *aux = elem;
  Elemento *aux2;

  if(aux == NULL){
    aux = (Elemento *)malloc(sizeof(Elemento));
    aux2 = aux;
  }
  else{
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux2 = (Elemento *)malloc(sizeof(Elemento));
    aux->prox = aux2;
  }
  aux2->prox = NULL;
  aux2->tipo = tipo;

  switch (tipo){
    case 'c':
      fscanf(geo, "%d %f %f %f %s %s", &aux2->i, &aux2->r, &aux2->x, &aux2->y, aux2->cor1, aux2->cor2);
      aux2->w = aux2->h = -1;
      break;
    case 'r':
      fscanf(geo, "%d %f %f %f %f %s %s", &aux2->i, &aux2->w, &aux2->h, &aux2->x, &aux2->y, aux2->cor1, aux2->cor2);
      aux2->r = -1;
      break;
    case 't':
      fscanf(geo, "%f %f", &aux2->x, &aux2->y);
      fgets(aux2->texto, 255, geo);
      aux2->i = -1;
      break;
  }
  draw_svg(aux2, out, tipo);

  if(!elem)
    elem = aux;

return elem;
}

void end_list(Elemento *elem){
  Elemento *aux, *aux2;

  aux = elem;
  while(aux!=NULL){
    aux2 = aux;
    aux = aux->prox;
    free(aux2);
  }
}
