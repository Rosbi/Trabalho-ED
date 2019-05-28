#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"svg.h"
#include"formasBase.h"
#include"lista.h"

float func_min(float a, float b){
  if(a>b)
    return b;
  else
    return a;
}
float func_max(float a, float b){
  if(a>b)
    return a;
  else
    return b;
}

void qry_start(char tnArq[], char dDir[], char dPath[], char nConsulta[], Lista listasObjetos[]){
  char* querryIn = NULL;  //nome do arquivo de entrada de dados
  char* querryOut = NULL; //nome do arquivo de saída de dados
  char* tempName = NULL;  //string a ser manipulada pela função strtok
  char qTipo[5];      //tipo de consulta a ser feita (o? i? d? bb)
  FILE* fQryIn;
  FILE* fQryOutSvg;
  FILE* fQryOutTxt;

  if(dPath){
    querryIn = (char *)malloc(sizeof(char)*(strlen(dPath)+strlen(nConsulta)+5));
    sprintf(querryIn, "%s/%s", dPath, nConsulta);
    }
    else{
      querryIn = (char *)malloc(sizeof(char)*(strlen(nConsulta)+5));
      strcpy(querryIn, nConsulta);
    }

  fQryIn = fopen(querryIn, "r");
  if(!fqIn){
    printf("ERRO AO ABRIR O ARQUIVO DE CONSULTA\n");
    exit(-1);
  }

  if(strstr(nConsulta, "/")){
    tempName = nConsulta;
    nArqGeo = strtok(tempName, "/");
    //nArqGeo = strtok(nConsulta, "/");
    while(nArqGeo!=NULL){
      strcpy(nConsulta, nArqGeo);
      nArqGeo = strtok(NULL, "/");
    }
    tempName = nConsulta;
    nConsulta = strtok(tempName, ".");
    //strtok(nConsulta, ".");
  }
  else{
    tempName = nConsulta;
    nConsulta = strtok(tempName, ".");
    //strtok(nConsulta, ".");
  }
  querryOut = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+10));
  sprintf(querryOut, "%s/%s-%s.svg", dDir, tnArq, nConsulta);
  fQryOutSvg = fopen(querryOut, "w");
  tempName = querryOut;
  querryOut = strtok(tempName, ".");
  //strtok(querryOut, ".");
  sprintf(querryOut, "%s.txt", querryOut);
  fQryOutTxt = fopen(querryOut, "w");

  while(!feof(fQryIn)){
    fscanf(fQryIn, "%s ", qTipo);
    if(strcmp(qTipo, "bb")==0){
        qry_bb(dDir, listasObjetos[0], bbCor, bbSufixo, tnArq, nConsulta);
    }
    else if(strcmp(qTipo, "i?")==0){
      fprintf(fQryOutTxt, "i? ");
      qry_i(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
    else if(strcmp(qTipo, "o?")==0){
      fprintf(fQryOutTxt, "o? ");
      qry_o(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
    else if(strcmp(qTipo, "d?")==0){
      fprintf(fQryOutTxt, "d? ");
      qry_d(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
  }

  draw_svg(listasObjetos, fQryOutSvg);

  fclose(fQryOutTxt);
  fclose(fQryOutSvg);
  fclose(fQryIn);
}

void qry_bb(char dDir[], Lista listsCR, char tnArq[], char nConsulta[], FILE* fQryIn){
  Item aux;
  FILE* bbOut;
  char* nOut;
  int contLista = 1;
  float r, w, h, x, y;
  char itemTipo, cor[22], sufixo[21];

  nOut = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+strlen(sufixo)+5));  //Aloca para nOut o (tamanho de dDir + tnArq + sufixo + sufixo + ".svg" + 1) * sizeof(char)
  sprintf(nOut, "%s/%s-%s-%s.svg", dDir, tnArq, nConsulta, sufixo);
  bbOut = fopen(nOut, "w");
  if(!bbOut){
    printf("ERRO AO CRIAR ARQUIVO DE CONSULTA bb\n");
    exit(-1);
  }

  fscanf(fQryIn, "%s %s ", sufixo, cor);

  fprintf(bbOut, "<svg>\n");

  while(1){
    aux = getItem(listaCR, contLista);
    if(aux!=NULL)
      formaDraw(aux, bbOut);
    else
      break;
    contLista++;
  }

  contLista = 1;
  while(1){
    aux = getItem(listaCR, contLista);
    if(aux!=NULL){
      itemTipo = formaGetTipo(aux);
      switch(itemTipo){
        case 'c':
          x = formaGetX(aux);
          y = formaGetY(aux);
          r = formaGetR(aux);
          draw_r(2*r, 2*r, x-r, y-r, cor, "black", 1.0, 0.0, bbOut);
          break;
        case 'r':
          x = formaGetX(aux);
          y = formaGetY(aux);
          w = formaGetW(aux);
          h = formaGetH(aux);
          draw_e(x+(w/2), y+(h/2), w/2, h/2, cor, "black", 1.0, 0.0, bbOut);
          break;
      }
    }
    else
      break;
    contLista++;
  }

  fprintf(bbOut, "</svg>");

  free(nOut);
  fclose(bbOut);
}

void qry_i(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem){
  float x, y, dist;
  Elemento *aux;

  fscanf(fqIn, "%d %f %f", &j, &x, &y);
  fprintf(fqOutTxt, "%d %f %f\n", j, x, y);

  aux = iElem;
  while(aux!=NULL){
    if(aux->i != j)
      aux = aux->prox;
    else
      break;
  }

  if(aux!=NULL){
    switch(aux->tipo){
      case 'c':
        dist = sqrt(pow(x-aux->x, 2)+pow(y-aux->y, 2));
        if(aux->r > dist){
          draw_c(-1, 2, x, y, "green", "green", fqOutSvg, 1.0);
          draw_l(aux->x, aux->y, x, y, "green", fqOutSvg);
          fprintf(fqOutTxt, "SIM\n\n");
        }
        else{
          draw_c(-1, 2, x, y, "red", "red", fqOutSvg, 1.0);
          draw_l(aux->x, aux->y, x, y, "red", fqOutSvg);
          fprintf(fqOutTxt, "NAO\n\n");
        }
        break;
      case 'r':
        if((aux->x < x && x < (aux->x+aux->w)) && (aux->y < y && y < (aux->y+aux->h))){
          draw_c(-1, 2, x, y, "green", "green", fqOutSvg, 1.0);
          draw_l(aux->x + (aux->w/2), aux->y + (aux->h/2), x, y, "green", fqOutSvg);
          fprintf(fqOutTxt, "SIM\n\n");
        }
        else{
          draw_c(-1, 2, x, y, "red", "red", fqOutSvg, 1.0);
          draw_l(aux->x + (aux->w/2), aux->y + (aux->h/2), x, y, "red", fqOutSvg);
          fprintf(fqOutTxt, "NAO\n\n");
        }
        break;
    }
  }
  else{
    draw_c(-1, 2, x, y, "black", "black", fqOutSvg, 1.0);
    fprintf(fqOutTxt, "NAO EXISTE ELEMENTO %d\n\n", j);
  }

}

void qry_o(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem){
  Elemento *aux = iElem, *aux2 = iElem;
  int j, k;
  float dist;
  float x1, y1, x2, y2;
  bool sob;

  fscanf(fqIn, "%d %d", &j, &k);
  fprintf(fqOutTxt, "%d %d\n", j, k);

  while(aux!=NULL && aux->i!=j)
    aux = aux->prox;
  while(aux2!=NULL && aux2->i!=k)
    aux2 = aux2->prox;

  if(aux!=NULL && aux2!=NULL){
    switch(aux->tipo){
      case 'c':
        if(aux2->tipo == 'c'){                    //Se as figuras forem dois circulos
          x1 = func_min(aux->x - aux->r, aux2->x - aux2->r);
          y1 = func_min(aux->y - aux->r, aux2->y - aux2->r);
          x2 = func_max(aux->x + aux->r, aux2->x + aux2->r);
          y2 = func_max(aux->y + aux->r, aux2->y + aux2->r);
          dist = sqrt(pow(aux->x-aux2->x, 2) + pow(aux->y-aux2->y, 2));
          if(dist > aux->r+aux2->r)               //Se a distancia entre os centros de massa for maior que a soma dos raios, os circulos não se sobrepõem
            sob = false;
          else
            sob = true;
        }
        else{                                     //Se as figuras forem um circulo e um retangulo
          if((aux->x > aux2->x && aux->x < aux2->x+aux2->w) && (aux->y > aux2->y && aux->y < aux2->y+aux2->h))    //Verifica se o centro do circulo esta dentro do retangulo
            sob = true;
          else{
            x1 = aux->x - func_max(aux2->x, func_min(aux->x, aux2->x + aux2->w));
            y1 = aux->y - func_max(aux2->y, func_min(aux->y, aux2->y + aux2->h));
            dist = sqrt(x1*x1 + y1*y1);
            if(dist < aux->r)
              sob = true;
            else
              sob = false;
            x1 = func_min(aux->x - aux->r, aux2->x);
            y1 = func_min(aux->y - aux->r, aux2->y);
            x2 = func_max(aux->x + aux->r, aux2->x + aux2->w);
            y2 = func_max(aux->y + aux->r, aux2->y + aux2->y);
          }
        }
        break;
      case 'r':
        if(aux2->tipo == 'c'){                    //Se as figuras forem um retangulo e um circulo
          if((aux2->x > aux->x && aux2->x < aux->x+aux->w) && (aux2->y > aux->y && aux2->y < aux->y+aux->h))    //Verifica se o centro do circulo esta dentro do retangulo
            sob = true;
          else{
            x1 = aux2->x - func_max(aux->x, func_min(aux2->x, aux->x + aux->w));
            y1 = aux2->y - func_max(aux->y, func_min(aux2->y, aux->y + aux->h));
            dist = sqrt(x1*x1 + y1*y1);
            if(dist < aux2->r)
              sob = true;
            else
              sob = false;
            x1 = func_min(aux2->x - aux2->r, aux->x);
            y1 = func_min(aux2->y - aux2->r, aux->y);
            x2 = func_max(aux2->x + aux2->r, aux->x + aux->r);
            y2 = func_max(aux2->y + aux2->r, aux->y + aux->r);
          }
        }
        else{                                     //Se as figuras forem dois retangulos
          x1 = func_min(aux->x, aux2->x);
          y1 = func_min(aux->y, aux2->y);
          x2 = func_max(aux->x + aux->w, aux2->x + aux2->w);
          y2 = func_max(aux->y + aux->h, aux2->y + aux2->h);
          if((aux->x < aux2->x+aux2->w && aux->x+aux->w > aux2->x) && (aux->y < aux2->y+aux2->h && aux->y+aux->h > aux2->y)){   //Verifica se os retangulos se sobrepõe
            sob = true;
          }
          else{
            sob = false;
          }
        }
        break;
    }
    if(sob){                                                          //caso as figuras se sobreponham, desenha um retangulo verde ao redor das duas
      draw_r(-1, x1-x2, y1-y2, x1, y1, "green", "black", fqOutSvg, 0.0);
      fprintf(fqOutTxt, "SIM\n\n");
    }
    else{                                                             //caso contrário, desenha um retangulo tracejado azul
      draw_r_dash(x1-x2, y1-y2, x1, y1, "blue", fqOutSvg);
      fprintf(fqOutTxt, "NAO\n\n");
    }
  }
  else                                                                //caso aux ou aux2 seja NULL, os elementos lidos não existem
    fprintf(fqOutTxt, "ELEMENTO J OU K NÃO ENCONTRADO\n\n");
}

void qry_d(FILE *fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem){
  int j, k;
  float dist;
  char dis[10];
  Elemento *aux = iElem, *aux2 = iElem;

  fscanf(fqIn, "%d %d", &j, &k);
  fprintf(fqOutTxt, "%d %d\n", j, k);
  while(aux!=NULL && aux->i!=j)
    aux = aux->prox;
  while(aux2!=NULL && aux2->i!=k)
    aux2 = aux2->prox;

  if(aux!=NULL && aux2!=NULL){
    switch(aux->tipo){
      case 'c':
        if(aux2->tipo == 'c'){
          dist = sqrt(pow(aux->x-aux2->x, 2) + pow(aux->y-aux2->y, 2));
          draw_l(aux->x, aux->y, aux2->x, aux2->y, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((aux->x + aux2->x)/2, (aux->y + aux2->y)/2, dis, fqOutSvg);
        }
        else{
          dist = sqrt(pow(aux->x-(aux2->x+aux2->w/2), 2) + pow(aux->y-(aux2->y+aux2->h/2), 2));
          draw_l(aux->x, aux->y, aux2->x+aux2->w/2, aux2->y+aux2->h/2, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((aux->x + aux2->x+aux2->w/2)/2, (aux->y + aux2->y+aux2->h/2)/2, dis, fqOutSvg);
        }
        fprintf(fqOutTxt, "%f\n\n", dist);
        break;
      case 'r':
        if(aux2->tipo == 'c'){
          dist = sqrt(pow((aux->x+aux->w/2)-aux2->x, 2) + pow((aux->y+aux->h/2)-aux2->y, 2));
          draw_l(aux->x + aux->w/2, aux->y + aux->h/2, aux2->x, aux2->y, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((aux->x+aux->w/2 + aux2->x)/2, (aux->y+aux->h/2 + aux2->y)/2, dis, fqOutSvg);
        }
        else{
          dist = sqrt(pow((aux->x+aux->w/2)-(aux2->x+aux2->w/2), 2) + pow((aux->y+aux->h/2)-(aux2->y+aux2->h/2), 2));
          draw_l(aux->x + aux->w/2, aux->y + aux->h/2, aux2->x+aux2->w/2, aux2->y+aux2->h/2, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((aux->x+aux->w/2 + aux2->x+aux2->w/2)/2, (aux->y+aux->h/2 + aux2->y+aux2->h/2)/2, dis, fqOutSvg);
        }
        fprintf(fqOutTxt, "%f\n\n", dist);
        break;
    }
  }
  else{
    fprintf(fqOutTxt, "ELEMENTO J OU K NÃO ENCONTRADO\n\n");
  }
}
