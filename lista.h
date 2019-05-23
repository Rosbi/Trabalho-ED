#ifndef LISTA_H
#define LISTA_H
#include<stdbool.h>

typedef void* Item;

typedef void* Lista;

Lista createList(int);

void insertItem(Lista, void*, size_t);

void insertAfter(Lista, void*, size_t, int);

void insertBefore(Lista, void*, size_t, int);

bool fullList(Lista);

bool emptyList(Lista);

Item getItem(Lista, int);

void removeItem(Lista, int);

#endif
