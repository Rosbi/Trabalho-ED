#ifndef LISTA_H
#define LISTA_H
#include<stdbool.h>

typedef void* Item;

typedef void* Lista;

/*  Todas as funções aqui tratam de listas e seu funcionamento
//  Cada elemento da lista é independente do outro, e seu conteudo é irrelevante para esse .h
*/

//  Retorna o endereço de tamanho max
Lista createList(int max);

//  Aloca m bytes para armazenar infor em lis
void insertItem(Lista lis, void* infor, size_t m);

//  NÃO IMPLEMENTADO
void insertAfter(Lista, void*, size_t, int);

//  NÃO IMPLEMENTADO
void insertBefore(Lista, void*, size_t, int);

//  Retorna true se a lista estiver cheia
bool fullList(Lista);

//  Retorna true se a lista estiver vazia
bool emptyList(Lista);

//  Retorna o i-ésimo item da lista lis
Item getItem(Lista lis, int i);

//  Remove o i-ésimo item da lista lis
void removeItem(Lista lis, int i);

//  Retorna a quatidade de itens na lista
int listaLength(Lista);

#endif
