#ifndef MURO_H
#define MURO_H

#include<stdio.h>

typedef void* ItemMuro;

/*  Esse TAD tem como base o hidante.h, para qualquer dúvida, consultar o mesmo
//  Qaulquer função com aplicação diferente estará comentada aqui
*/

ItemMuro muroNew(Ponto a, Ponto b, int* sizeofItem);

void muroDraw(ItemMuro muro, FILE* out);

#endif
