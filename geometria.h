#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include<stdbool.h>

typedef void* Reta;
typedef void* Ponto;

int retaSizeof(void);

bool nearlyEqual(double a, double b, double epsilon);
double distancia(Ponto a, Ponto b);
Ponto intersecta(Reta r, Reta s);
bool estaEntre(Ponto a, Ponto b, Ponto entre);

Ponto criarPonto(double x, double y);

void printPonto(Ponto);
void setPonto(Ponto a, double x, double y);   //ATENÇÃO: se usado para alterar retas, os coeficientes das mesmas não serão atualizados
double getPontoX(Ponto a);
double getPontoY(Ponto a);

Reta criarReta(Ponto a, Ponto b);

Ponto getRetaA(Reta);
Ponto getRetaB(Reta);
void setRetaA(Reta r, double x, double y);
void setRetaB(Reta r, double x, double y);
double getRetaTamanho(Reta r);

#endif
