#include<stdio.h>
#include<string.h>

typedef struct elemento{
  char tipo;
  int i;
  float x;
  float y;
  float r;
  float w;
  float h;
  char cor1[22];
  char cor2[22];
  char texto[255];
  struct elemento *prox;
}Elemento;

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

void draw_c(int i, float r, float x, float y, char cor1[], char cor2[], FILE* dir, float opacity){
  fprintf(dir, "\t<circle r=\"%f\" cx=\"%f\" cy=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", r, x, y, cor1, cor2, opacity);
  if(i>0)
    fprintf(dir, "\t\t<text text-anchor=\"middle\" font-size=\"1\" x=\"%f\" y=\"%f\" fill=\"%s\">%d</text>\n", x, y, cor1, i);    //Escreve o número 'i' no centro do círculo
}

void draw_r(int i, float w, float h, float x, float y, char cor1[], char cor2[], FILE* dir, float opacity){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", w, h, x, y, cor1, cor2, opacity);
  if(i>0)
    fprintf(dir, "\t\t<text text-anchor=\"middle\" font-size=\"1\" x=\"%f\" y=\"%f\" fill=\"%s\">%d</text>\n", x+(w/2), y+(h/2), cor1, i);    //Escreve o número 'i' no centro do quadrado
}

void draw_t(float x, float y, char texto[], FILE* dir){
  fprintf(dir, "\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>\n", x, y, texto);
}

void draw_e(float x, float y, float rx, float ry, char cor1[], char cor2[], FILE* dir, float opacity){
  fprintf(dir, "\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\" fill-opacity=\"%f\"/>\n", x, y, rx, ry, cor1, cor2, opacity);
}

void draw_l(float x1, float y1, float x2, float y2, char cor[], FILE *dir){
  fprintf(dir, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"0.5\"/>\n", x1, y1, x2, y2, cor);
}

void draw_r_dash(float w, float h, float x, float y, char cor[], FILE* dir){
  fprintf(dir, "\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"white\" stroke-width=\"0.5\" stroke-dasharray=\"5,5\" fill-opacity=\"0.0\"/>\n", w, h, x, y, cor);
}
