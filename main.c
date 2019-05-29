#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"svg.h"
#include"query.h"
#include"lista.h"

int main(int argc, char *argv[]){
  Lista listasObjetos[6];   //o vetor representa respectivamente as listas de circulos/retangulos, quadras, hidrantes, semaforos, e textos
  int i=1;

  char *nArqGeo = NULL; //nome do Arquivo Geo
  char *dPath = NULL;   //diretório de entrada de dados (opcional)
  char *nConsulta = NULL; //nome do arquivo de Comsulta (opcional)
  char *dDir = NULL;    //diretório destino

  char *tnArq = NULL;   //nome temporario do arquivo
  char *tdDir = NULL;   //nome temporário do diretório de saída
  char *tdPath = NULL;  //nome temporário do diretório de entrada
  char *nqIn = NULL;    //nome do arquivo qry de entrada
  char *nqOut = NULL;   //nome do arquivo qry da saída
  char *temp = NULL;
  FILE *out;

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

  if(!dDir){
    printf("DIRETORIO NAO INFORMADO\n");
    exit(-1);
  }
  if(!nArqGeo){
    printf("ARQUIVO NAO INFORMADO\n");
    exit(-1);
  }

  if(dPath){  //Verifica se o diretório foi especificado, ou se o caminho será relativo
    tdPath = (char *)malloc((strlen(nArqGeo)+strlen(dPath)+5)*sizeof(char));
    sprintf(tdPath,"%s/%s",dPath,nArqGeo);
  }
  else{
    tdPath = (char *)malloc((strlen(nArqGeo)+5)*sizeof(char));
    strcpy(tdPath, nArqGeo);
  }

  tnArq = (char *)malloc(sizeof(char)*(strlen(nArqGeo))+5);   //retira o ".geo" do nome e coloca ".svg"
  strcpy(tnArq, nArqGeo);
  temp = tnArq;
  tnArq = strtok(temp, ".");
  //tnArq = strtok(tnArq, ".");
  sprintf(tnArq, "%s.svg", tnArq);

  tdDir = (char *)malloc((sizeof(char)*(strlen(dDir)+strlen(tnArq)))+5);  //coloca o nome do arquivo .svg no diretório destino, e retira o ".svg" do nome do arquivo
  sprintf(tdDir, "%s/%s", dDir, tnArq);
  temp = tnArq;
  tnArq = strtok(temp, ".");
  //tnArq = strtok(tnArq, ".");

  inicializarListas(tdPath, listasObjetos);  //chama a função para criar o svg base
  create_svg(tdDir);
  out = fopen(tdDir, "r+");
  draw_svg(listasObjetos, out);
  fclose(out);

  if(nConsulta){
    qry_start(tnArq, dDir, dPath, nConsulta, nArqGeo, listasObjetos);
  }

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
