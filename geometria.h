#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include<stdbool.h>

/*  Aqui se encontram funções relacionadas à pontos, retas, interações entre eles e algumas contas
//  NOTA: os parametros que pedem Reta ou Ponto não podem receber NULL, nem um TAD diferente do requisitado
*/

typedef void* Reta;
typedef void* Ponto;

//  Constante usasda como epsilon na função nearlyEqual
#define double_BAIXO 0.000001

//  Retorna o tamanho em bytes da struct reta
int retaSizeof(void);

//  Verifica se a diferença entre dois a e b é negligenciavel em relação à epsilon
bool nearlyEqual(double a, double b, double epsilon);
//  Retorna a distancia entre dois pontos a e b
double distancia(Ponto a, Ponto b);
//  Retorna o ponto de intersecção entre duas retas, NULL caso não intersectem
Ponto intersecta(Reta r, Reta s);
//  Verifica se um dado ponto está entre outos dois
bool estaEntre(Ponto a, Ponto b, Ponto entre);

//  Retorna o endereço do ponto criado
Ponto criarPonto(double x, double y);

//void printPonto(Ponto);

//  Altera as coordenadas de um ponto
//  ATENÇÃO: se usado para alterar retas, os coeficientes das mesmas não serão atualizados
void setPonto(Ponto a, double x, double y);
//  As funções a seguir retornam uma das coordenadas de um ponto
double getPontoX(Ponto a);
double getPontoY(Ponto a);

//  Retorna o endereço de uma reta criada a partir de dois pontos
Reta criarReta(Ponto a, Ponto b);

//  Retorna um ponto (A ou B) de uma reta
Ponto getRetaA(Reta);
Ponto getRetaB(Reta);
//  Altera um ponto (A ou B) de uma reta
void setRetaA(Reta r, double x, double y);
void setRetaB(Reta r, double x, double y);
//Retorna o tamanho da reta
double getRetaTamanho(Reta r);

#endif
