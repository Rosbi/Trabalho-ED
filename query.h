#ifndef QUERY_H
#define QUERY_H
#include"lista.h"

float func_min(float a, float b);
float func_max(float a, float b);

void qry_start(char[], char[], char[], char[], char[], Lista[]);

void qry_bb(char[], Lista[], char[], char[], FILE*);
void qry_i(FILE*, FILE*, FILE*, Lista);
void qry_o(FILE*, FILE*, FILE*, Lista);
void qry_d(FILE*, FILE*, FILE*, Lista);
void qry_dq(FILE*, FILE*, FILE*, Lista[]);
void qry_del(FILE*, FILE*, Lista[]);

#endif
