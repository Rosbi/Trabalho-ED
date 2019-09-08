#ifndef SVG_H
#define SVG_H

#include"lista.h"

/*  Esse .h trata de funções relacionadas diretamente a um arquivo svg
*/

enum tipoListas{e_formas, e_quadras, e_hidrantes, e_semaforos, e_torres, e_predios, e_muros, e_textos};

//  Lê o arquivo .geo, cria as listas de TADs, e cria o arquivo .svg base
void inicializarListas(char*, Lista[]);

//  Cria um arquivo nomeArq.svg e escreve "<svg>" na primeira linha
void create_svg(char nomeArq[]);
//  Escreve "</svg>" no fim do arquivo nomeArq.svg
void finalize_svg(char nomeArq[]);

//  Desenha todos os elementos de listaObjetos no arquivo nomeArq
void draw_svg(Lista listasObjetos[], FILE* nomeArq);

#endif
