#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"formasBase.h"
#include"hidrante.h"
#include"quadra.h"
#include"semaforo.h"
#include"torre.h"
#include"lista.h"
#include"geometria.h"
#include"predio.h"

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

  for(int i=0;i<6;i++){
    long int atual = ftell(geo);
    fscanf(geo, "%s ", tipo);
    if(strcmp(tipo, "nx") == 0){
      fscanf(geo, "%d", &listaMax[0]);
      if(fgetc(geo) != '\n')
        fscanf(geo, "%d %d %d %d %d %d ", &listaMax[1], &listaMax[2], &listaMax[3], &listaMax[4], &listaMax[5], &listaMax[6]);
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
  }

  for(int i=0;i<7;i++){
    listasObjetos[i] = createList(listaMax[i]);
  }
  listasObjetos[7] = createList(1000);

  while(!feof(geo)){
    fscanf(geo, "%s", tipo);//printf("%s\n", tipo);fflush(stdout);
    if(strcmp(tipo, "c")==0){
      fscanf(geo, "%d %lf %lf %lf %s %s ", &id, &r, &x, &y, cstroke, cfill);
      aux = circuloNew(id, x, y, r, cstroke, cfill, &sizeofItem);//printf("_%lf_\n", formaGetX(aux));fflush(stdout);
      insertItem(listasObjetos[0], aux, sizeofItem);
    }
    else if(strcmp(tipo, "r")==0){
      fscanf(geo, "%d %lf %lf %lf %lf %s %s ", &id, &w, &h, &x, &y, cstroke, cfill);
      aux = retanguloNew(id, x, y, w, h, cstroke, cfill, &sizeofItem);
      insertItem(listasObjetos[0], aux, sizeofItem);
    }
    else if(strcmp(tipo, "t")==0){
      fscanf(geo, "%lf %lf ", &x, &y);
      fgets(texto, 255, geo);
      aux = textoNew(texto, x, y, &sizeofItem);//printf("%p\n", aux);fflush(stdout);
      insertItem(listasObjetos[5], aux, sizeofItem);
    }
    else if(strcmp(tipo, "q")==0){
      fscanf(geo, "%s %lf %lf %lf %lf ", cep, &x, &y, &w, &h);
      aux = quadraNew(x, y, w, h, cep, &sizeofItem);
      insertItem(listasObjetos[1], aux, sizeofItem);
    }
    else if(strcmp(tipo, "h")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = hidranteNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[2], aux, sizeofItem);
    }
    else if(strcmp(tipo, "rb")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = torreNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[4], aux, sizeofItem);
    }
    else if(strcmp(tipo, "s")==0){
      fscanf(geo, "%s %lf %lf ", cep, &x, &y);
      aux = semaforoNew(cep, x, y, &sizeofItem);
      insertItem(listasObjetos[3], aux, sizeofItem);
    }
    else if(strcmp(tipo, "prd")==0){      /////////////////////////////////////
      char face, *cep2;
      double num, f, p, mrg;
      fscanf(geo, "%s %c %lf %lf %lf %lf ", cep, &face, &num, &f, &p, &mrg);

      for(int j=0;j<listaMax[1];j++){
        cep2 = quadraGetCep(getItem(listasObjetos[1], j));
        if(strcmp(cep, cep2)==0){
          aux = predioNew(cep, face, num, f, p, mrg, getItem(listasObjetos[1], j), &sizeofItem);
          insertItem(listasObjetos[5], aux, sizeofItem);
          break;
        }
      }
    }                                     //////////////////////////////////////
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
  Item temp;
  int contLista;

  fseek(out, 0, SEEK_END);

  for(int i=0;i<6;i++){
  contLista = 1;
    while(1){
      temp = getItem(listasObjetos[i], contLista);
      if(temp!=NULL){
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
      else
        break;
      contLista++;
    }
  }
}
