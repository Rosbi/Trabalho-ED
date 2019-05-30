#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"svg.h"
#include"formasBase.h"
#include"quadra.h"
#include"hidrante.h"
#include"semaforo.h"
#include"torre.h"
#include"lista.h"
#include"query.h"

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

bool SqrTotalOverSqr(float xs, float ys, float ws, float hs, float x, float y, float w, float h){
  if(x>xs && y>ys && (x+w)<(xs+ws) && (y+h)<(ys+hs))
    return true;
  else
    return false;
}
bool CirTotalOverSqr(float xc, float yc, float r, float xs, float ys, float w, float h){
  float dist1, dist2, dist3, dist4, x1, y1;

    dist1 = sqrt(pow(xc-xs, 2)+pow(yc-ys, 2));
    dist2 = sqrt(pow(xc-(xs+w), 2)+pow(yc-ys, 2));
    dist3 = sqrt(pow(xc-xs, 2)+pow(yc-(ys+h), 2));
    dist4 = sqrt(pow(xc-(xs+w), 2)+pow(yc-(ys+h), 2));
    if(dist1 < r && dist2 < r && dist3<r && dist4<r)
      return true;
    else
      return  false;
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
  querryOut = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+10));//printf("%s\n", nConsulta);fflush(stdout);//
  sprintf(querryOut, "%s/%s-%s.svg", dDir, tnArq, nConsulta);
  create_svg(querryOut);
  fQryOutSvg = fopen(querryOut, "a+");
  tempName = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+10));
  sprintf(tempName, "%s/%s-%s.txt", dDir, tnArq, nConsulta);//printf("%s\n", tempName);fflush(stdout);//
  /*tempName = querryOut;
  querryOut = strtok(tempName, ".");
  //strtok(querryOut, ".");
  sprintf(querryOut, "%s.txt", querryOut);*/
  fQryOutTxt = fopen(tempName, "w");

  while(!feof(fQryIn)){
    fscanf(fQryIn, "%s ", qTipo);//printf("%s\n", qTipo);
    if(strcmp(qTipo, "bb")==0){
      qry_bb(dDir, listasObjetos, tnArq, nConsulta, fQryIn);
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
    else if(strcmp(qTipo, "dq")==0){
      qry_dq(fQryOutTxt, fQryOutSvg, fQryIn, listasObjetos);
    }
    else if(strcmp(qTipo, "del")==0){
      qry_del(fQryOutTxt, fQryIn, listasObjetos);
    }
    else if(strcmp(qTipo, "cbq")==0){
      qry_cbq(fQryOutTxt, fQryIn, listasObjetos);
    }
    else if(strcmp(qTipo, "crd?")==0){
      qry_crd(fQryOutTxt, fQryIn, listasObjetos);
    }
    else if(strcmp(qTipo, "trns")==0){
      qry_trns(fQryOutTxt, fQryIn, listasObjetos);
    }
  }

  draw_svg(listasObjetos, fQryOutSvg);

  fclose(fQryOutTxt);
  fclose(fQryOutSvg);
  finalize_svg(querryOut);
  fclose(fQryIn);
}

void qry_bb(char dDir[], Lista listaCR[], char tnArq[], char nConsulta[], FILE* fQryIn){
  Item aux;
  FILE* bbOut;
  char* nOut;
  int contLista = 1;
  float r, w, h, x, y;
  char itemTipo, cor[22], sufixo[21];
  fscanf(fQryIn, "%s %s ", sufixo, cor);

  nOut = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+strlen(sufixo)+5));  //Aloca para nOut o (tamanho de dDir + tnArq + sufixo + sufixo + ".svg" + 1) * sizeof(char)
  sprintf(nOut, "%s/%s-%s-%s.svg", dDir, tnArq, nConsulta, sufixo);
  create_svg(nOut);
  bbOut = fopen(nOut, "a");
  if(!bbOut){
    printf("ERRO AO CRIAR ARQUIVO DE CONSULTA bb\n");
    exit(-1);
  }
  draw_svg(listaCR, bbOut);

  while(1){
    aux = getItem(listaCR[0], contLista);
    if(aux!=NULL)
      formaDraw(aux, bbOut);
    else
      break;
    contLista++;
  }

  contLista = 1;
  while(1){
    aux = getItem(listaCR[0], contLista);
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

  fclose(bbOut);
  finalize_svg(nOut);

  free(nOut);
}
void qry_i(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listaCR){
  Item aux;
  float x, y, dist, xForma, yForma, rForma, wForma, hForma;
  int j, contLista = 1;
  char tipo;

  fscanf(fqIn, "%d %f %f ", &j, &x, &y);
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

  fscanf(fqIn, "%d %d ", &j, &k);
  fprintf(fqOutTxt, "o? %d %d\n", j, k);

  while(1){
    aux1 = getItem(listaCR, contLista);
    if(aux1 != NULL){
      if(formaGetID(aux1) == j)
        break;
    }
    else{
      //printf("i\n");fflush(stdout);
      break;
    }
    contLista++;
  }
  contLista = 1;
  while(1){
    aux2 = getItem(listaCR, contLista);
    if(aux2 != NULL){
      if(formaGetID(aux2) == k)
        break;
    }
    else{
      //printf("j\n");fflush(stdout);
      break;
    }
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
          wForma[1] = formaGetW(aux2);
          hForma[1] = formaGetH(aux2);
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
          }
          x1 = func_min(xForma[0] - rForma[0], xForma[1]);
          y1 = func_min(yForma[0] - rForma[0], yForma[1]);
          x2 = func_max(xForma[0] + rForma[0], xForma[1] + wForma[1]);
          y2 = func_max(yForma[0] + rForma[0], yForma[1] + hForma[1]);
        }
        break;
      case 'r':
        wForma[0] = formaGetW(aux1);
        hForma[0] = formaGetH(aux1);
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
          }
          x1 = func_min(xForma[1] - rForma[1], xForma[0]);
          y1 = func_min(yForma[1] - rForma[1], yForma[0]);
          x2 = func_max(xForma[1] + rForma[1], xForma[0] + wForma[0]);
          y2 = func_max(yForma[1] + rForma[1], yForma[0] + hForma[0]);
        }
        else{                                     //Se as figuras forem dois retangulos
          wForma[1] = formaGetW(aux2);
          hForma[1] = formaGetH(aux2);
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
      draw_r(abs(x1-x2), abs(y1-y2), x1, y1, "green", "black", 1.0, 0.0, fqOutSvg);
      fprintf(fqOutTxt, "SIM\n\n");
    }
    else{                                                             //caso contrário, desenha um retangulo tracejado azul
      draw_r_dash(abs(x1-x2), abs(y1-y2), x1, y1, "blue", fqOutSvg);
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

  fscanf(fqIn, "%d %d ", &j, &k);
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
  contLista = 1;
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
void qry_dq(FILE *fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listasObjetos[]){} //COMING SOON
void qry_del(FILE *fqOutTxt, FILE* fqIn, Lista listasObjetos[]){
  char tipoObjeto[2], cepid[21];
  Item aux;
  int contLista=1;
  float x, y;
  bool encontrado;

  fgets(tipoObjeto, 2, fqIn);
  fseek(fqIn, -1, SEEK_CUR);
  fscanf(fqIn, "%s ", cepid);
  fprintf(fqOutTxt, "del %s\n", cepid);
  switch(tipoObjeto[0]){
    case 'b':
      while(1){
        aux = getItem(listasObjetos[1], contLista);
        if(aux){
          if(strcmp(quadraGetCep(aux), cepid)==0){
            removeItem(listasObjetos[1], contLista);
            x = quadraGetX(aux);
            y = quadraGetY(aux);
            encontrado = true;
            break;
          }
        }
        else{
          encontrado = false;
          break;
        }
        contLista++;
      }
      break;
    case 'h':
      while(1){
        aux = getItem(listasObjetos[2], contLista);
        if(aux){
          if(strcmp(hidranteGetId(aux), cepid)==0){
            removeItem(listasObjetos[2], contLista);
            x = hidranteGetX(aux);
            y = hidranteGetY(aux);
            encontrado = true;
            break;
          }
        }
        else{
          encontrado = false;
        break;
      }
      contLista++;
    }
      break;
    case 's':
      while(1){
        aux = getItem(listasObjetos[3], contLista);
        if(aux){//printf("%s\n", semaforoGetId(aux));
          if(strcmp(semaforoGetId(aux), cepid)==0){
            removeItem(listasObjetos[3], contLista);
            x = semaforoGetX(aux);
            y = semaforoGetY(aux);
            encontrado = true;
            break;
          }
        }
        else{
          encontrado = false;
          break;
        }
        contLista++;
      }
      break;
    case 'r':
      while(1){
        aux = getItem(listasObjetos[4], contLista);
        if(aux){
          if(strcmp(torreGetId(aux), cepid)==0){
            removeItem(listasObjetos[4], contLista);
            x = torreGetX(aux);
            y = torreGetY(aux);
            encontrado = true;
            break;
          }
        }
        else{
          encontrado = false;
          break;
        }
        contLista++;
      }
      break;
  }
  if(encontrado){
    fprintf(fqOutTxt, "OBJETO REMOVIDO\ncoordenadas: %f, %f\n\n", x, y);
  }
  else
    fprintf(fqOutTxt, "OBJETO NAO ENCONTRADO\n\n");
}
void qry_cbq(FILE* fqOutTxt, FILE* fqIn, Lista listasObjetos[]){
  Item aux;
  char cstrk[22], cep[50];
  float x, y, r, xaux, yaux, w, h;
  int contLista=1;

  fscanf(fqIn, "%f %f %f %s ", &x, &y, &r, cstrk);
  fprintf(fqOutTxt, "cbq %f %f %f\n", x, y, r);

  while(1){
    aux = getItem(listasObjetos[1], contLista);
    if(aux){
      xaux = quadraGetX(aux);
      yaux = quadraGetY(aux);
      w = quadraGetW(aux);
      h = quadraGetH(aux);
      if(CirTotalOverSqr(x, y, r, xaux, yaux, w, h)){
        strcpy(cep, quadraGetCep(aux));
        fprintf(fqOutTxt, "%s\n", cep);
        quadraSetThisStroke(aux, cstrk);
      }
    }
    else
      break;
    contLista++;
  }
}
void qry_crd(FILE* fqOutTxt, FILE* fqIn, Lista listasObjetos[]){
  Item aux;
  float x, y;
  int contLista=1;
  char tipoObjeto[2], cepid[50];
  bool encontrado = false;

  fgets(tipoObjeto, 2, fqIn);
  fseek(fqIn, -1, SEEK_CUR);
  fscanf(fqIn, "%s ", cepid);
  fprintf(fqOutTxt, "crd? %s\n", cepid);
  switch(tipoObjeto[0]){
    case 'b':
      while(1){
        aux = getItem(listasObjetos[1], contLista);
        if(aux){
          if(strcmp(quadraGetCep(aux), cepid)==0){
            x = quadraGetX(aux);
            y = quadraGetY(aux);
            fprintf(fqOutTxt, "Quadra: %f %f\n\n", x, y);
            encontrado = true;
            break;
          }
        }
        else{
          break;
        }
        contLista++;
      }
      break;
    case 'h':
      while(1){
        aux = getItem(listasObjetos[2], contLista);
        if(aux){//printf("%s\n", hidranteGetId(aux));
          if(strcmp(hidranteGetId(aux), cepid)==0){
            x = hidranteGetX(aux);
            y = hidranteGetY(aux);
            fprintf(fqOutTxt, "Hidrante: %f %f\n\n", x, y);
            encontrado = true;
            break;
          }
        }
        else{
        break;
      }
      contLista++;
    }
      break;
    case 's':
      while(1){
        aux = getItem(listasObjetos[3], contLista);
        if(aux){//printf("%s\n", semaforoGetId(aux));
          if(strcmp(semaforoGetId(aux), cepid)==0){
            x = semaforoGetX(aux);
            y = semaforoGetY(aux);
            fprintf(fqOutTxt, "Semaforo: %f %f\n\n", x, y);
            encontrado = true;
            break;
          }
        }
        else{
          break;
        }
        contLista++;
      }
      break;
    case 'r':
      while(1){
        aux = getItem(listasObjetos[4], contLista);
        if(aux){
          if(strcmp(torreGetId(aux), cepid)==0){
            x = torreGetX(aux);
            y = torreGetY(aux);
            fprintf(fqOutTxt, "Torre de Radio: %f %f\n\n", x, y);
            encontrado = true;
            break;
          }
        }
        else{
          break;
        }
        contLista++;
      }
      break;
  }
  if(!encontrado)
    fprintf(fqOutTxt, "OBJETO NAO ENCONTRADO\n\n");
}
void qry_trns(FILE* fqOutTxt, FILE* fqIn, Lista listasObjetos[]){
  Item aux;
  int contLista=1;
  float x, y, w, h, dx, dy, ax, ay, aw, ah;

  fscanf(fqIn, "%f %f %f %f %f %f ", &x, &y, &w, &h, &dx, &dy);
  fprintf(fqIn, "trns %f %f %f %f %f %f\n", x, y, w, h, dx, dy);
  while(1){
    aux = getItem(listasObjetos[1], contLista);
    if(aux){
      ax = quadraGetX(aux);
      ay = quadraGetY(aux);
      aw = quadraGetW(aux);
      ah = quadraGetH(aux);
      if(SqrTotalOverSqr(x, y, w, h, ax, ay, aw, ah)){
        quadraSetX(aux, ax+dx);
        quadraSetY(aux, ay+dy);
      }
    }
    else
      break;
    contLista++;
  }
}
