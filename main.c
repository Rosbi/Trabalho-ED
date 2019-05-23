#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"svg.h"
#include"query.h"

int main(int argc, char *argv[]){
  Elemento *iElem = NULL, *aux = NULL;
  int i=1;
  int size = 1000;
  char *nArqGeo = NULL; //nome do Arquivo Geo
  char *dPath = NULL;   //diretório de entrada de dados (opcional)
  char *nConsulta = NULL; //nome do arquivo de Comsulta (opcional)
  char *dDir = NULL;    //diretório destino

  char *tnArq = NULL;   //nome temporario do arquivo
  char *tdDir = NULL;   //nome temporário do diretório de saída
  char *tdPath = NULL;  //nome temporário do diretório de entrada
  char *nqIn = NULL;    //nome do arquivo qry de entrada
  char *nqOut = NULL;   //nome do arquivo qry da saída
  char qTipo[4];        //tipo de consulta a ser feita (o? i? d? bb)
  char qCor[22];        //cor da bounding box
  char qSufixo[20];     //sufixo do arquivo svg da bounding box
  FILE* fqIn;           //arquivo de entrada de dados de consulta
  FILE* fqOutSvg;       //arquivo destino para consulta svg
  FILE* fqOutTxt;       //arquivo destino para consulta txt

  while(i<argc){
    if(strcmp("-f",argv[i]) == 0){                                  //Nome do arquivo de entrada "a01.geo" (relativo)
      i++;
      nArqGeo = (char *)malloc((strlen(argv[i])+5)*sizeof(char));
      strcpy(nArqGeo, argv[i]);
    }
    else if(strcmp("-o", argv[i]) == 0){                            //Diretório destino (relativo/absoluto)
      i++;
      dDir = (char *)malloc((sizeof(char)*strlen(argv[i]))+5);
      strcpy(dDir, argv[i]);
    }
    else if(strcmp("-e",argv[i]) == 0){                             //Diretório base de Entrada (relativo/absoluto)
      i++;
      dPath = (char *)malloc((strlen(argv[i])+5)*sizeof(char));
      strcpy(dPath, argv[i]);
    }
    else if(strcmp("-q", argv[i]) == 0){                           //Nome do arquivo de consulta "q1.qry" (relativo)
      i++;
      nConsulta = (char *)malloc((strlen(argv[i])+5)*sizeof(char));
      strcpy(nConsulta, argv[i]);
    }
    i++;
  }

  if(!dDir || !nArqGeo){
    printf("DIRETORIO OU ARQUIVO NAO INFORMADO\n");
    exit(-1);
  }

  if(dPath){  //Verifica se o diretório foi especificado, ou se o caminho será relativo
    tdPath = (char *)malloc((strlen(nArqGeo)+strlen(dPath)+5)*sizeof(char));
    sprintf(tdPath,"%s/%s",dPath,nArqGeo);
  }
  else{
    tdPath = (char *)malloc((strlen(nArqGeo)+5)*sizeof(char));
    sprintf(tdPath, "%s", nArqGeo);
  }

  tnArq = (char *)malloc(sizeof(char)*(strlen(nArqGeo))+5);   //retira o ".geo" do nome e coloca ".svg"
  strcpy(tnArq, nArqGeo);
  tnArq = strtok(tnArq, ".");
  sprintf(tnArq, "%s.svg", tnArq);

  tdDir = (char *)malloc((sizeof(char)*(strlen(dDir)+strlen(tnArq)))+5);  //coloca o nome do arquivo .svg no diretório destino, e retira o ".svg" do nome do arquivo
  sprintf(tdDir, "%s/%s", dDir, tnArq);
  tnArq = strtok(tnArq, ".");

  iElem = create_base_svg(tdPath, tdDir, &size);  //chama a função para criar o svg base

  if(nConsulta){
    if(dPath){
      nqIn = (char *)malloc(sizeof(char)*(strlen(dPath)+strlen(nConsulta)+5));
      sprintf(nqIn, "%s/%s", dPath, nConsulta);
      }
      else{
        nqIn = (char *)malloc(sizeof(char)*(strlen(nConsulta)+5));
        sprintf(nqIn, "%s", nConsulta);
      }
    fqIn = fopen(nqIn, "r");
    if(!fqIn){
      printf("ERRO AO ABRIR O ARQUIVO DE CONSULTA\n");
      exit(-1);
    }

    if(strstr(nConsulta, "/")){
      nArqGeo = strtok(nConsulta, "/");
      while(nArqGeo!=NULL){
        strcpy(nConsulta, nArqGeo);
        nArqGeo = strtok(NULL, "/");
      }
      strtok(nConsulta, ".");
    }
    else{
      strtok(nConsulta, ".");
    }
    nqOut = (char *)malloc(sizeof(char)*(strlen(dDir)+strlen(tnArq)+strlen(nConsulta)+10));
    sprintf(nqOut, "%s/%s-%s.svg", dDir, tnArq, nConsulta);
    fqOutSvg = fopen(nqOut, "w");
    strtok(nqOut, ".");
    sprintf(nqOut, "%s.txt", nqOut);
    fqOutTxt = fopen(nqOut, "w");

    fprintf(fqOutSvg, "<svg width=\"%d\" height=\"%d\">\n", 1000, 1000);         //Inicia o svg

    aux = iElem;
    while(aux!=NULL){
      draw_svg(aux, fqOutSvg, aux->tipo);
      aux = aux->prox;
    }

    while(!feof(fqIn)){
      fgets(qTipo, 3, fqIn);
      if(strcmp(qTipo, "bb")==0){
          fscanf(fqIn, "%s %s", qSufixo, qCor);
          qry_bb(dDir, iElem, size, qCor, qSufixo, tnArq, nConsulta);
      }
      else if(strcmp(qTipo, "i?")==0){
        fprintf(fqOutTxt, "i? ");
        qry_i(fqOutTxt, fqOutSvg, fqIn, iElem);
      }
      else if(strcmp(qTipo, "o?")==0){
        fprintf(fqOutTxt, "o? ");
        qry_o(fqOutTxt, fqOutSvg, fqIn, iElem);
      }
      else if(strcmp(qTipo, "d?")==0){
        fprintf(fqOutTxt, "d? ");
        qry_d(fqOutTxt, fqOutSvg, fqIn, iElem);
      }
    }

    fprintf(fqOutSvg, "</svg>");

    fclose(fqOutTxt);
    fclose(fqOutSvg);
    fclose(fqIn);
  }

  end_list(iElem);
  if(!nConsulta)
    free(nArqGeo);
  if(dPath)
    free(dPath);
  if(nConsulta)
    free(nConsulta);
  if(dDir)
    free(dDir);
  if(tnArq)
    free(tnArq);
  if(tdDir)
    free(tdDir);
  if(tdPath)
    free(tdPath);
  if(nqIn)
    free(nqIn);
  if(nqOut)
    free(nqOut);
return 0;
}
