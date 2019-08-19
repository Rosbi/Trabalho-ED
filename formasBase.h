#ifndef FORMAS_H
#define FORMAS_H

typedef void* Forma;

Forma retanguloNew(int, double, double, double, double, char[], char[], int*);
Forma circuloNew(int, double, double, double, char[], char[], int*);
Forma textoNew(char[], double, double, int*);

void formaDraw(Forma, FILE*);

void formaSetStroke(double, double);

void formaSetX(Forma, double);
void formaSetY(Forma, double);
void formaSetW(Forma, double);
void formaSetH(Forma, double);
void formaSetR(Forma, double);
void formaSetCorstroke(Forma, char[]);
void formaSetCorfill(Forma, char[]);

double formaGetX(Forma);
double formaGetY(Forma);
double formaGetR(Forma);
double formaGetW(Forma);
double formaGetH(Forma);
char formaGetTipo(Forma);
int formaGetID(Forma);
char* formaGetTexto(Forma);

void draw_r(double w, double h, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir);
void draw_c(double r, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir);
void draw_e(double x, double y, double rx, double ry, char cor1[], char cor2[], double opacity, FILE* dir);
void draw_r_dash(double w, double h, double x, double y, char cor[], FILE* dir);
void draw_l(double x1, double y1, double x2, double y2, char cor[], FILE *dir);
void draw_t(double x, double y, char texto[], FILE* dir);

#endif
