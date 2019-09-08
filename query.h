#ifndef QUERY_H
#define QUERY_H

#include"lista.h"

/*  Esse .h trata de todas as consultas do arquivo .qry, e alguns calculos basicos
*/

//  Retorna o menor entre a e b
double func_min(double a, double b);
//  Retorna o maior entre a e b
double func_max(double a, double b);

//  Cria os arquivos .svg e .txt de consulta, e realiza as mesmas
// quanto aos parametros da função, ó Senhor ajudai-nos, pois somente tu sabes a utilidade de cada parametro
void qry_start(char[], char[], char[], char[], char[], Lista[]);

//  Cada uma das funções a seguir realiza um caso de teste
//  NOTA: todos os itens solicidados no .qry DEVEM existir
void qry_bb(char[], Lista[], char[], char[], FILE*);
void qry_i(FILE*, FILE*, FILE*, Lista);
void qry_o(FILE*, FILE*, FILE*, Lista);
void qry_d(FILE*, FILE*, FILE*, Lista);
void qry_dq(FILE*, FILE*, FILE*, Lista[]);
void qry_del(FILE*, FILE*, Lista[]);
void qry_cbq(FILE*, FILE*, Lista[]);
void qry_crd(FILE*, FILE*, Lista[]);
void qry_trns(FILE*, FILE*, Lista[]);
void qry_brl(FILE*, FILE*, FILE*, Lista[]);
void qry_fi(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listasObjetos[]);
void qry_fh(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listasObjetos[]);
void qry_fs(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Lista listasObjetos[]);

#endif
