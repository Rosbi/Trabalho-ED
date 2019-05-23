#ifndef QUERY_H
#define QUERY_H
#include"formas.h"

void qry_bb(char dDir[], Elemento *iElem, int size, char cor[], char sufixo[], char tnArq[], char nConsulta[]);

void qry_i(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem);

void qry_o(FILE* fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem);

void qry_d(FILE *fqOutTxt, FILE* fqOutSvg, FILE* fqIn, Elemento *iElem);

#endif
