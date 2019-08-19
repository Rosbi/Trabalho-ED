#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include<stdbool.h>

typedef void* Reta;
typedef void* Ponto;

double distancia(Ponto a, Ponto b);
bool nearlyEqual(double a, double b, double epsilon);

Ponto criarPonto(double x, double y);
void printPonto(Ponto);
Reta criarReta();

bool estaEntre(Ponto a, Ponto b, Ponto entre);
Ponto intersecta();

void setPonto(Ponto a, double x, double y);   //ATENÇÃO: se usado para alterar retas, os coeficientes das mesmas não serão atualizados
double getPontoX(Ponto a);
double getPontoY(Ponto a);
Ponto getRetaA(Reta);
Ponto getRetaB(Reta);
void setRetaA(Reta r, double x, double y);
void setRetaB(Reta r, double x, double y);
double getRetaTamanho(Reta r);

#endif
