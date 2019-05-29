#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"svg.h"
#include"formasBase.h"
#include"lista.h"

void qry_bb(char[], Lista, char[], char[], FILE*);
void qry_i(FILE*, FILE*, FILE*, Lista);
void qry_o(FILE*, FILE*, FILE*, Lista);
void qry_d(FILE*, FILE*, FILE*, Lista);

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

void qry_start(char tnArq[], char dDir[], char dPath[], char nConsulta[], char nArqGeo[], Lista listasObjetos[]){
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
  if(!fQryIn){
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
      qry_bb(dDir, listasObjetos[0], tnArq, nConsulta, fQryIn);
    }
    else if(strcmp(qTipo, "i?")==0){
      qry_i(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
    else if(strcmp(qTipo, "o?")==0){
      qry_o(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
    else if(strcmp(qTipo, "d?")==0){
      qry_d(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos[0]);
    }
  }

  fseek(fQryOutSvg, 0, SEEK_SET);
  draw_svg(listasObjetos, fQryOutSvg);

  fclose(fQryOutTxt);
  fclose(fQryOutSvg);
  fclose(fQryIn);
}

void qry_bb(char dDir[], Lista listaCR, char tnArq[], char nConsulta[], FILE* fQryIn){
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
          draw_e(x+(w/2), y+(h/2), w/2, h/2, cor, "black", 0.0, bbOut);
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

void qry_i(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listaCR){
  Item aux;
  float x, y, dist, xForma, yForma, rForma, wForma, hForma;
  int j, contLista = 1;
  char tipo;

  fscanf(fqIn, "%d %f %f", &j, &x, &y);
  fprintf(fqOutTxt, "i? %d %f %f\n", j, x, y);

  while(1){
    aux = getItem(listaCR, contLista);
    if(aux!=NULL){
      if(formaGetID(aux)==j)
        break;
    }
    else
      break;
    contLista++;
  }

  if(aux!=NULL){
    tipo = formaGetTipo(aux);
    xForma = formaGetX(aux);
    yForma = formaGetY(aux);
    switch(tipo){
      case 'c':
        rForma = formaGetR(aux);
        dist = sqrt(pow(x-xForma, 2)+pow(y-yForma, 2));
        if(rForma > dist){
          draw_c(2, x, y, "green", "green", 1.0, 1.0, fqOutSvg);
          draw_l(xForma, yForma, x, y, "green", fqOutSvg);
          fprintf(fqOutTxt, "SIM\n\n");
        }
        else{
          draw_c(2, x, y, "red", "red", 1.0, 1.0, fqOutSvg);
          draw_l(xForma, yForma, x, y, "red", fqOutSvg);
          fprintf(fqOutTxt, "NAO\n\n");
        }
        break;
      case 'r':
        wForma = formaGetW(aux);
        hForma = formaGetH(aux);
        if((xForma < x && x < (xForma+wForma)) && (yForma < y && y < (yForma+hForma))){
          draw_c(2, x, y, "green", "green", 1.0, 1.0, fqOutSvg);
          draw_l(xForma + (wForma/2), yForma + (hForma/2), x, y, "green", fqOutSvg);
          fprintf(fqOutTxt, "SIM\n\n");
        }
        else{
          draw_c(2, x, y, "red", "red", 1.0, 1.0, fqOutSvg);
          draw_l(xForma + (wForma/2), yForma + (hForma/2), x, y, "red", fqOutSvg);
          fprintf(fqOutTxt, "NAO\n\n");
        }
        break;
    }
  }
  else{
    draw_c(2, x, y, "black", "black", 1.0, 1.0, fqOutSvg);
    fprintf(fqOutTxt, "NAO EXISTE ELEMENTO %d\n\n", j);
  }

}

void qry_o(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listaCR){
  Item aux1, aux2;
  int j, k, contLista=1;
  float dist;
  float x1, y1, x2, y2;
  float xForma[2], yForma[2], rForma[2], wForma[2], hForma[2];
  char tipo[2];
  bool sob;

  fscanf(fqIn, "o? %d %d", &j, &k);
  fprintf(fqOutTxt, "%d %d\n", j, k);

  while(1){
    aux1 = getItem(listaCR, contLista);
    if(aux1 != NULL){
      if(formaGetID(aux1) == j)
        break;
    }
    else
      break;
    contLista++;
  }
  while(1){
    aux2 = getItem(listaCR, contLista);
    if(aux2 != NULL){
      if(formaGetID(aux2) == k)
        break;
    }
    else
      break;
    contLista++;
  }

  if(aux1!=NULL && aux2!=NULL){
    tipo[0] = formaGetTipo(aux1);
    tipo[1] = formaGetTipo(aux2);
    xForma[0] = formaGetX(aux1);
    xForma[1] = formaGetX(aux2);
    yForma[0] = formaGetY(aux1);
    yForma[1] = formaGetY(aux2);
    switch(tipo[0]){
      case 'c':
        rForma[0]= formaGetR(aux1);
        if(tipo[1] == 'c'){                    //Se as figuras forem dois circulos
          rForma[1] = formaGetR(aux2);
          x1 = func_min(xForma[0] - rForma[0], xForma[1] - rForma[1]);
          y1 = func_min(yForma[0] - rForma[0], yForma[1] - rForma[1]);
          x2 = func_max(xForma[0] + rForma[0], xForma[1] + rForma[1]);
          y2 = func_max(yForma[0] + rForma[0], yForma[1] + rForma[1]);
          dist = sqrt(pow(xForma[0]-xForma[1], 2) + pow(yForma[0]-yForma[1], 2));
          if(dist > rForma[0]+rForma[1])               //Se a distancia entre os centros de massa for maior que a soma dos raios, os circulos não se sobrepõem
            sob = false;
          else
            sob = true;
        }
        else{                                     //Se as figuras forem um circulo e um retangulo
          wForma[1] = formaGetR(aux2);
          hForma[1] = formaGetR(aux2);
          if((xForma[0] > xForma[1] && xForma[0] < xForma[1]+wForma[1]) && (yForma[0] > yForma[1] && yForma[0] < yForma[1]+hForma[1]))    //Verifica se o centro do circulo esta dentro do retangulo
            sob = true;
          else{
            x1 = xForma[0] - func_max(xForma[1], func_min(xForma[0], xForma[1] + wForma[1]));
            y1 = yForma[0] - func_max(yForma[1], func_min(yForma[0], yForma[1] + hForma[1]));
            dist = sqrt(x1*x1 + y1*y1);
            if(dist < rForma[0])
              sob = true;
            else
              sob = false;
            x1 = func_min(xForma[0] - rForma[0], xForma[1]);
            y1 = func_min(yForma[0] - rForma[0], yForma[1]);
            x2 = func_max(xForma[0] + rForma[0], xForma[1] + wForma[1]);
            y2 = func_max(yForma[0] + rForma[0], yForma[1] + yForma[1]);
          }
        }
        break;
      case 'r':
        wForma[0] = formaGetR(aux1);
        hForma[0] = formaGetR(aux1);
        if(tipo[1] == 'c'){                    //Se as figuras forem um retangulo e um circulo
          rForma[1] = formaGetR(aux2);
          if((xForma[1] > xForma[0] && xForma[1] < xForma[0]+wForma[0]) && (yForma[1] > yForma[0] && yForma[1] < yForma[0]+hForma[0]))    //Verifica se o centro do circulo esta dentro do retangulo
            sob = true;
          else{
            x1 = xForma[1] - func_max(xForma[0], func_min(xForma[1], xForma[0] + wForma[0]));
            y1 = yForma[1] - func_max(yForma[0], func_min(yForma[1], yForma[0] + hForma[0]));
            dist = sqrt(x1*x1 + y1*y1);
            if(dist < rForma[1])
              sob = true;
            else
              sob = false;
            x1 = func_min(xForma[1] - rForma[1], xForma[0]);
            y1 = func_min(yForma[1] - rForma[1], yForma[0]);
            x2 = func_max(xForma[1] + rForma[1], xForma[0] + wForma[0]);
            y2 = func_max(yForma[1] + rForma[1], yForma[0] + hForma[0]);
          }
        }
        else{                                     //Se as figuras forem dois retangulos
          wForma[1] = formaGetR(aux2);
          hForma[1] = formaGetR(aux2);
          x1 = func_min(xForma[0], xForma[1]);
          y1 = func_min(yForma[0], yForma[1]);
          x2 = func_max(xForma[0] + wForma[0], xForma[1] + wForma[1]);
          y2 = func_max(yForma[0] + hForma[0], yForma[1] + hForma[1]);
          if((xForma[0] < xForma[1]+wForma[1] && xForma[0]+wForma[0] > xForma[1]) && (yForma[0] < yForma[1]+hForma[1] && yForma[0]+hForma[0] > yForma[1])){   //Verifica se os retangulos se sobrepõe
            sob = true;
          }
          else{
            sob = false;
          }
        }
        break;
    }
    if(sob){                                                          //caso as figuras se sobreponham, desenha um retangulo verde ao redor das duas
      draw_r(x1-x2, y1-y2, x1, y1, "green", "black", 1.0, 0.0, fqOutSvg);
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

void qry_d(FILE *fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listaCR){
  int j, k, contLista=1;
  float dist;
  float xForma[2], yForma[2], wForma[2], hForma[2], rForma[2];
  char dis[40], tipo[2];
  Item aux1, aux2;

  fscanf(fqIn, "%d %d", &j, &k);
  fprintf(fqOutTxt, "d? %d %d\n", j, k);

  while(1){
    aux1 = getItem(listaCR, contLista);
    if(aux1 != NULL){
      if(formaGetID(aux1) == j)
        break;
    }
    else
      break;
    contLista++;
  }
  while(1){
    aux2 = getItem(listaCR, contLista);
    if(aux2 != NULL){
      if(formaGetID(aux2) == k)
        break;
    }
    else
      break;
    contLista++;
  }

  if(aux1!=NULL && aux2!=NULL){
    tipo[0] = formaGetTipo(aux1);
    tipo[1] = formaGetTipo(aux2);
    xForma[0] = formaGetX(aux1);
    xForma[1] = formaGetX(aux2);
    yForma[0] = formaGetY(aux1);
    yForma[1] = formaGetY(aux2);
    switch(tipo[0]){
      case 'c':
      rForma[0] = formaGetR(aux1);
        if(tipo[1] == 'c'){
          rForma[1] = formaGetR(aux2);
          dist = sqrt(pow(xForma[0]-xForma[1], 2) + pow(yForma[0]-yForma[1], 2));
          draw_l(xForma[0], yForma[0], xForma[1], yForma[1], "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((xForma[0] + xForma[1])/2, (yForma[0] + yForma[1])/2, dis, fqOutSvg);
        }
        else{
          wForma[1] = formaGetW(aux2);
          hForma[1] = formaGetH(aux2);
          dist = sqrt(pow(xForma[0]-(xForma[1]+wForma[1]/2), 2) + pow(yForma[0]-(yForma[1]+hForma[1]/2), 2));
          draw_l(xForma[0], yForma[0], xForma[1]+wForma[1]/2, yForma[1]+hForma[1]/2, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((xForma[0] + xForma[1]+wForma[1]/2)/2, (yForma[0] + yForma[1]+hForma[1]/2)/2, dis, fqOutSvg);
        }
        fprintf(fqOutTxt, "%f\n\n", dist);
        break;
      case 'r':
        wForma[0] = formaGetW(aux1);
        hForma[0] = formaGetH(aux1);
        if(tipo[1] == 'c'){
          rForma[1] = formaGetR(aux2);
          dist = sqrt(pow((xForma[0]+wForma[0]/2)-xForma[1], 2) + pow((yForma[0]+hForma[0]/2)-yForma[1], 2));
          draw_l(xForma[0] + wForma[0]/2, yForma[0] + hForma[0]/2, xForma[1], yForma[1], "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((xForma[0]+wForma[0]/2 + xForma[1])/2, (yForma[0]+hForma[0]/2 + yForma[1])/2, dis, fqOutSvg);
        }
        else{
          wForma[1] = formaGetW(aux2);
          hForma[1] = formaGetH(aux2);
          dist = sqrt(pow((xForma[0]+wForma[0]/2)-(xForma[1]+wForma[1]/2), 2) + pow((yForma[0]+hForma[0]/2)-(yForma[1]+hForma[1]/2), 2));
          draw_l(xForma[0] + wForma[0]/2, yForma[0] + hForma[0]/2, xForma[1]+wForma[1]/2, yForma[1]+hForma[1]/2, "black", fqOutSvg);
          sprintf(dis, "%f", dist);
          draw_t((xForma[0]+wForma[0]/2 + xForma[1]+wForma[1]/2)/2, (yForma[0]+hForma[0]/2 + yForma[1]+hForma[1]/2)/2, dis, fqOutSvg);
        }
        fprintf(fqOutTxt, "%f\n\n", dist);
        break;
    }
  }
  else{
    fprintf(fqOutTxt, "ELEMENTO J OU K NÃO ENCONTRADO\n\n");
  }
}
