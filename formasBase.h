#ifndef FORMAS_H
#define FORMAS_H

typedef void* Forma;

/*  As funções aqui encontradas são referentes à formas primitivas (qudrados, circulos, linhas e textos),
//  além de tratar a os TADs dessas formas
//  NOTA: nenhum parametro desse .h pode ser NULL
//  NOTA2: todos os parametros Forma devem corresponder a um dos objetos desse .h
*/

//  As 3 funções a seguir retornam um ponteiro para a instancia do objeto criado
//  O ponteiro sizeofItem altera o int passado para o tamanho do objeto criado
Forma retanguloNew(int id, double x, double y, double w, double h, char corStroke[], char corFill[], int* sizeofItem);
Forma circuloNew(int id, double x, double y, double r, char corStoke[], char corFill[], int* sizeofItem);
Forma textoNew(char texto[], double x, double y, int* sizeofItem);

//  Desenha a form no arquivo dest
void formaDraw(Forma form, FILE* dest);

//  Altera a largura do stroke de todos os objetos
void formaSetStroke(double strokeCirculo, double strokeRetangulo);

//  Altera a caracteristica desejada do objeto passado
//  NOTA: caso a Forma não possua a caracteristica desejada, nada ocorrerá
void formaSetX(Forma form, double novoX);
void formaSetY(Forma form, double novoY);
void formaSetW(Forma form, double novoW);
void formaSetH(Forma form, double novoH);
void formaSetR(Forma form, double novoR);
void formaSetCorstroke(Forma form, char novaCor[]);
void formaSetCorfill(Forma form, char novaCor[]);

//  Retorn a caracteristica desejada do objeto passado
//  NOTA: caso a Forma não possua a caracteristica desejada, o retorno será -1 ou NULL
double formaGetX(Forma);
double formaGetY(Forma);
double formaGetR(Forma);
double formaGetW(Forma);
double formaGetH(Forma);
char formaGetTipo(Forma);
int formaGetID(Forma);
char* formaGetTexto(Forma);

//  Todos os comandos a seguir desenham uma forma primitiva no arquivo desejado
void draw_r(double w, double h, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir);
void draw_c(double r, double x, double y, char cor1[], char cor2[], double stroke, double opacity, FILE* dir);
void draw_e(double x, double y, double rx, double ry, char cor1[], char cor2[], double opacity, FILE* dir);
void draw_r_dash(double w, double h, double x, double y, char cor[], FILE* dir);
void draw_l(double x1, double y1, double x2, double y2, char cor[], FILE *dir);
void draw_t(double x, double y, char texto[], FILE* dir);

#endif
