#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"formasBase.h"
#include"hidrante.h"
#include"quadra.h"
#include"semaforo.h"
#include"torre.h"
#include"lista.h"

void inicializarListas(char *nArqGeo, Lista listasObjetos[]){
  int listaMax[] = {1000, 1000, 1000, 1000, 1000};  //o vetor representa respectivamente o maximo de circulos/retangulos, quadras, hidrantes, semaforos e torres
  char tipo[3], cfill[22], cstroke[22], cep[20], texto[255];
  Item aux;
  float sw, rw;
  int id, sizeofItem;
  float x, y, w, h, r;
  FILE* geo = fopen(nArqGeo, "r");

  if(!geo){
    printf("ERRO AO ABRIR O ARQUIVO GEO\n");
    exit(-1);
  }

  for(int i=0;i<6;i++){
    long int atual = ftell(geo);
    fscanf(geo, "%s ", tipo);
    if(strcmp(tipo, "nx") == 0){
      //fscanf(geo, "%d %d %d %d %d ", &listaMax[0], &listaMax[1], &listaMax[2], &listaMax[3], &listaMax[4]);
      fscanf(geo, "%d ", &listaMax[0]);
    }
    else if(strcmp(tipo, "cq") == 0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      quadraSetCorstroke(cstroke);
      quadraSetCorfill(cfill);
      quadraSetStroke(sw);
    }
    else if(strcmp(tipo, "ch") == 0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      hidranteSetCorstroke(cstroke);
      hidranteSetCorfill(cfill);
      hidranteSetStroke(sw);
    }
    else if(strcmp(tipo, "cr") == 0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      torreSetCorstroke(cstroke);
      torreSetCorfill(cfill);
      torreSetStroke(sw);
    }
    else if(strcmp(tipo, "cs") == 0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      semaforoSetCorstroke(cstroke);
      semaforoSetCorfill(cfill);
      semaforoSetStroke(sw);
    }
    else if(strcmp(tipo, "sw") == 0){
      fscanf(geo, "%f %f ", &sw, &rw);
      formaSetStroke(sw, rw);
    }
    else
      fseek(geo, atual, SEEK_SET);
  }

  for(int i=0;i<5;i++){
    listasObjetos[i] = createList(listaMax[i]);
  }
  listasObjetos[5] = createList(1000);

  while(!feof(geo)){
    fscanf(geo, "%s", tipo);printf("%s\n", tipo);fflush(stdout);
    if(strcmp(tipo, "c")==0){
      fscanf(geo, "%d %f %f %f %s %s ", &id, &r, &x, &y, cstroke, cfill);
      aux = circuloNew(id, x, y, r, cstroke, cfill, &sizeofItem);
      insertItem(listasObjetos[0], aux, sizeofItem);
    }
    else if(strcmp(tipo, "r")==0){
      fscanf(geo, "%d %f %f %f %f %s %s ", &id, &w, &h, &x, &y, cstroke, cfill);
      aux = retanguloNew(id, x, y, w, h, cstroke, cfill, &sizeofItem);
      insertItem(listasObjetos[0], aux, sizeofItem);
    }
    else if(strcmp(tipo, "t")==0){
      fscanf(geo, "%f %f ", &x, &y);
      fgets(texto, 255, geo);
      aux = textoNew(texto, x, y, &sizeofItem);//printf("%p\n", aux);fflush(stdout);
      insertItem(listasObjetos[5], aux, sizeofItem);
    }
    else if(strcmp(tipo, "q")==0){
      fscanf(geo, "%s %f %f %f %f ", cep, &x, &y, &w, &h);
      aux = quadraNew(x, y, w, h, cep, &sizeofItem);
      insertItem(listasObjetos[1], aux, sizeofItem);
    }
    else if(strcmp(tipo, "h")==0){
      fscanf(geo, "%s %f %f ", cep, &x, &y);
      aux = hidranteNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[2], aux, sizeofItem);
    }
    else if(strcmp(tipo, "rb")==0){
      fscanf(geo, "%s %f %f ", cep, &x, &y);
      aux = torreNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[3], aux, sizeofItem);
    }
    else if(strcmp(tipo, "s")==0){
      fscanf(geo, "%s %f %f ", cep, &x, &y);
      aux = semaforoNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[4], aux, sizeofItem);
    }
    else if(strcmp(tipo, "cq")==0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      quadraSetCorstroke(cstroke);
      quadraSetCorfill(cfill);
      quadraSetStroke(sw);
    }
    else if(strcmp(tipo, "ch")==0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      hidranteSetCorstroke(cstroke);
      hidranteSetCorfill(cfill);
      hidranteSetStroke(sw);
    }
    else if(strcmp(tipo, "cr")==0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      torreSetCorstroke(cstroke);
      torreSetCorfill(cfill);
      torreSetStroke(sw);
    }
    else if(strcmp(tipo, "cs")==0){
      fscanf(geo, "%s %s %f ", cfill, cstroke, &sw);
      semaforoSetCorstroke(cstroke);
      semaforoSetCorfill(cfill);
      semaforoSetStroke(sw);
    }
    else if(strcmp(tipo, "sw")==0){
      fscanf(geo, "%f %f ", &sw, &rw);
      formaSetStroke(sw, rw);
    }
  }

  fclose(geo);
}

void create_svg(char nameOut[]){
  FILE* svg = fopen(nameOut, "w");
  fprintf(svg, "<svg>\n</svg>");
  fclose(svg);
}

void draw_svg(Lista listasObjetos[], FILE* out){
  Item temp;
  char cc[7];
  int fimLista = 0, contLista;

  fgets(cc, 7, out);

  for(int i=0;i<6;i++){
  contLista = 1;
    while(1){
      temp = getItem(listasObjetos[i], contLista);
      if(temp){
        switch(i){
          case 0:
            formaDraw(temp, out);
            break;
          case 1:
            quadraDraw(temp, out);
            break;
          case 2:
            hidranteDraw(temp, out);
            break;
          case 3:
            semaforoDraw(temp, out);
            break;
          case 4:
            torreDraw(temp, out);
            break;
          case 5:
            formaDraw(temp, out);
            break;
        }
      }
      else break;
    }
  }
}
