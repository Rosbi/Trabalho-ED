#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"svg.h"
#include"formasBase.h"
#include"hidrante.h"
#include"quadra.h"
#include"semaforo.h"
#include"torre.h"
#include"lista.h"
#include"geometria.h"
#include"predio.h"
#include"muro.h"

void inicializarListas(char *nArqGeo, Lista listasObjetos[]){
  int listaMax[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000};  //o vetor representa respectivamente o maximo de circulos/retangulos, quadras, hidrantes, semaforos e torres
  char tipo[4], cfill[22], cstroke[22], cep[20], texto[255];
  Item aux;
  double sw, rw;
  int id, sizeofItem;
  double x, y, w, h, r;
  FILE* geo = fopen(nArqGeo, "r");

  if(!geo){
    printf("ERRO AO ABRIR O ARQUIVO GEO\n");
    exit(-1);
  }

  fscanf(geo, "%s ", tipo);//////////////////////////////////
  if(strcmp(tipo, "nx") == 0){
    fscanf(geo, "%d", &listaMax[e_formas]);
    if(fgetc(geo) != '\n'){
      fscanf(geo, "%d %d %d %d", &listaMax[e_quadras], &listaMax[e_hidrantes], &listaMax[e_semaforos], &listaMax[e_torres]);
      if(fgetc(geo) != '\n'){
        fscanf(geo, "%d %d ", &listaMax[e_predios], &listaMax[e_muros]);
      }
    }
  }/////////////////////////////////////
  /*for(int i=0;i<6;i++){
    long int atual = ftell(geo);
    fscanf(geo, "%s ", tipo);
    if(strcmp(tipo, "nx") == 0){
      fscanf(geo, "%d", &listaMax[e_formas]);
      if(fgetc(geo) != '\n'){
        fscanf(geo, "%d %d %d %d", &listaMax[e_quadras], &listaMax[e_hidrantes], &listaMax[e_semaforos], &listaMax[e_torres]);
        if(fgetc(geo) != '\n'){
          fscanf(geo, "%d %d ", &listaMax[e_predios], &listaMax[e_muros]);
        }
      }
    }
    else if(strcmp(tipo, "cq") == 0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      quadraSetCorstroke(cstroke);
      quadraSetCorfill(cfill);
      quadraSetStroke(sw);
    }
    else if(strcmp(tipo, "ch") == 0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      hidranteSetCorstroke(cstroke);
      hidranteSetCorfill(cfill);
      hidranteSetStroke(sw);
    }
    else if(strcmp(tipo, "cr") == 0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      torreSetCorstroke(cstroke);
      torreSetCorfill(cfill);
      torreSetStroke(sw);
    }
    else if(strcmp(tipo, "cs") == 0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      semaforoSetCorstroke(cstroke);
      semaforoSetCorfill(cfill);
      semaforoSetStroke(sw);
    }
    else if(strcmp(tipo, "sw") == 0){
      fscanf(geo, "%lf %lf ", &sw, &rw);
      formaSetStroke(sw, rw);
    }
    else{
      fseek(geo, atual, SEEK_SET);
      break;
    }
  }*/

  for(int i=0;i<7;i++){
    listasObjetos[i] = createList(listaMax[i]);
  }
  listasObjetos[e_textos] = createList(1000);

  while(!feof(geo)){
    fscanf(geo, "%s", tipo);
    if(strcmp(tipo, "c")==0){
      fscanf(geo, "%d %lf %lf %lf %s %s ", &id, &r, &x, &y, cstroke, cfill);
      aux = circuloNew(id, x, y, r, cstroke, cfill, &sizeofItem);
      insertItem(listasObjetos[e_formas], aux, sizeofItem);
    }
    else if(strcmp(tipo, "r")==0){
      fscanf(geo, "%d %lf %lf %lf %lf %s %s ", &id, &w, &h, &x, &y, cstroke, cfill);
      aux = retanguloNew(id, x, y, w, h, cstroke, cfill, &sizeofItem);
      insertItem(listasObjetos[e_formas], aux, sizeofItem);
    }
    else if(strcmp(tipo, "t")==0){
      fscanf(geo, "%lf %lf ", &x, &y);
      fgets(texto, 255, geo);
      aux = textoNew(texto, x, y, &sizeofItem);
      insertItem(listasObjetos[e_textos], aux, sizeofItem);
    }
    else if(strcmp(tipo, "q")==0){
      fscanf(geo, "%s %lf %lf %lf %lf ", cep, &x, &y, &w, &h);
      aux = quadraNew(x, y, w, h, cep, &sizeofItem);
      insertItem(listasObjetos[e_quadras], aux, sizeofItem);
    }
    else if(strcmp(tipo, "h")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = hidranteNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[e_hidrantes], aux, sizeofItem);
    }
    else if(strcmp(tipo, "rb")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = torreNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[e_torres], aux, sizeofItem);
    }
    else if(strcmp(tipo, "s")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = semaforoNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[e_semaforos], aux, sizeofItem);
    }
    else if(strcmp(tipo, "prd")==0){        //seg fault se o cep não existir
      char face, *cep2;
      double num, f, p, mrg;
      fscanf(geo, "%s %c %lf %lf %lf %lf ", cep, &face, &num, &f, &p, &mrg);

      for(int j=0;j<listaMax[e_quadras];j++){
        cep2 = quadraGetCep(getItem(listasObjetos[e_quadras], j));

        if(getItem(listasObjetos[e_quadras], j) == NULL)
          break;

        if(strcmp(cep, cep2)==0){
          aux = predioNew(cep, face, num, f, p, mrg, getItem(listasObjetos[e_quadras], j), &sizeofItem);
          insertItem(listasObjetos[e_predios], aux, sizeofItem);
          break;
        }
      }
    }
    else if(strcmp(tipo, "mur")==0){
      double x1, y1, x2, y2;
      fscanf(geo, "%lf %lf %lf %lf ", &x1, &y1, &x2, &y2);
      aux = muroNew(criarPonto(x1, y1), criarPonto(x2, y2), &sizeofItem);
      insertItem(listasObjetos[e_muros], aux, sizeofItem);
    }
    else if(strcmp(tipo, "cq")==0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      quadraSetCorstroke(cstroke);
      quadraSetCorfill(cfill);
      quadraSetStroke(sw);
    }
    else if(strcmp(tipo, "ch")==0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      hidranteSetCorstroke(cstroke);
      hidranteSetCorfill(cfill);
      hidranteSetStroke(sw);
    }
    else if(strcmp(tipo, "cr")==0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      torreSetCorstroke(cstroke);
      torreSetCorfill(cfill);
      torreSetStroke(sw);
    }
    else if(strcmp(tipo, "cs")==0){
      fscanf(geo, "%s %s %lf ", cfill, cstroke, &sw);
      semaforoSetCorstroke(cstroke);
      semaforoSetCorfill(cfill);
      semaforoSetStroke(sw);
    }
    else if(strcmp(tipo, "sw")==0){
      fscanf(geo, "%lf %lf ", &sw, &rw);
      formaSetStroke(sw, rw);
    }
  }

  fclose(geo);
}

void create_svg(char nameOut[]){
  FILE* svg = fopen(nameOut, "w");
  fprintf(svg, "<svg>\n");
  fclose(svg);
}
void finalize_svg(char nameOut[]){
  FILE* svg = fopen(nameOut, "a");
  fprintf(svg, "</svg>");
  fclose(svg);
}

void draw_svg(Lista listasObjetos[], FILE* out){
  Item temp = getItem(listasObjetos[e_formas], 1);
  int contLista = 1;

  fseek(out, 0, SEEK_END);

  while(temp != NULL){
    formaDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_formas], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_quadras], contLista);
  while(temp != NULL){
    quadraDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_quadras], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_hidrantes], contLista);
  while(temp != NULL){
    hidranteDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_hidrantes], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_semaforos], contLista);
  while(temp != NULL){
    semaforoDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_semaforos], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_torres], contLista);
  while(temp != NULL){
    torreDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_torres], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_predios], contLista);
  while(temp != NULL){
    predioDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_predios], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_muros], contLista);
  while(temp != NULL){
    muroDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_muros], contLista);
  }

  contLista = 1;
  temp = getItem(listasObjetos[e_textos], contLista);
  while(temp != NULL){
    formaDraw(temp, out);
    contLista++;
    temp = getItem(listasObjetos[e_textos], contLista);
  }
}
