#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"lista.h"

#define NULO -1
#define LIVRE -2

bool emptyList(Lista);

struct Elemento{
    int prox, ant;
    Item info;
};

struct ListaImplementada{
    int livre, prim, ult, max;
    struct Elemento *elem;
};

Lista createList(int tamanho){
    struct ListaImplementada *li = malloc(sizeof(struct ListaImplementada));
    li->elem = malloc(tamanho*sizeof(struct Elemento));
    li->max = tamanho;

    for(int i=0;i<tamanho;i++){
        li->elem[i].prox = i+1;
        li->elem[i].ant = i-1;
    }

    li->elem[tamanho-1].prox = NULO;
    li->elem[0].ant = NULO;
    li->prim = 0;
    li->ult = NULO;
    li->livre = 0;
    return li;
}

void insertItem(Lista lis, void* infor, size_t tamanho){
    struct ListaImplementada *li = lis;
    if(!fullList(li)){
        int livre = getLivre(li);
        li->elem[livre].info = malloc(tamanho);
        memcpy(li->elem[livre].info, infor, tamanho);

        if(emptyList(li))
            li->prim = livre;

        li->elem[livre].prox = li->livre;
        li->elem[livre].ant = li->ult;
        if(!emptyList(li))
            li->elem[li->ult].prox = livre;
        li->ult = livre;
        //printf("(Elemento inserido em %d)@@ant: %d  @@  prox: %d\n", livre, li->elem[livre].ant, li->elem[livre].prox);
    }
}

void removeItem(Lista lis, int i){
    struct ListaImplementada *li = lis;
    if(!emptyList(li)){
        int livre = li->livre;
        int index = li->prim;
        for(int j=0;j<i-1;j++){
            index = li->elem[index].prox;
        }

        if(li->elem[index].info){
            free(li->elem[index].info);
            li->elem[index].info = NULL;
            if(li->prim != li->ult){
                if(index == li->ult)
                    li->ult = li->elem[index].ant;
                if(index == li->prim){
                    if(!li->elem[li->elem[index].prox].info){
                        li->ult = li->prim;
                        //printf("oi mae\n\n\n");
                    }
                    li->prim = li->elem[index].prox;
                    li->elem[li->prim].ant = NULO;
                    li->livre = index;
                    li->elem[li->livre].prox = livre;
                }
                else{
                    li->elem[li->elem[index].ant].prox = li->elem[index].prox;
                    li->elem[li->elem[index].prox].ant = li->elem[index].ant;
                    li->livre = index;
                    li->elem[li->livre].prox = livre;
                }
            }
            else{
                li->elem[index].ant = NULO;
            }
            //printf("ITEM %d REMOVIDO COM SUCESSO - NOVO LIVRE: %d\n", index, li->livre);
            //printf("++primeiro: %d++\n", li->prim);
        }
        //else printf("--ITEM %d NAO EXISTE--\n", i);
    }
}

int getLivre(Lista lis){
    struct ListaImplementada *li = lis;
    int livre = li->livre;
    li->livre = li->elem[livre].prox;
    return livre;
}

bool fullList(Lista lis){
    struct ListaImplementada *li = lis;
    int index = li->prim;
    int j;
    //printf("---------------------------------------------\n");
    for(j=0;j<li->max;j++){
        index = li->elem[index].prox;
        //printf("%d\n\n", index);
        if(!li->elem[index].info)
            break;
    }
    //printf("---------------------------------------------\n");
    //printf("j: %d || max: %d", j, li->max);
    if(j >= li->max){
        //printf("LISTACHEIACARALHO¨¨¨¨¨¨¨&¨¨\n");
        return true;
    }
    else
        return false;
}

bool emptyList(Lista lis){
    struct ListaImplementada *li = lis;
    if(!li->elem[li->prim].info)
        return true;
    else
        return false;
}

void insertBefore(Lista lis, void* infor, size_t tamanho, int i){
    struct ListaImplementada *li = lis;
}

Item getItem(Lista lis, int i){
    struct ListaImplementada *li = lis;
    if(emptyList(li)){
        return NULL;
    }

    int index = li->prim;
    for(int j=0;j<i-1;j++){
        index = li->elem[index].prox;
    }

    if(i <= li->max && index != NULO){
        if(li->elem[index].info){
            //printf("---%d---", index);
            //printf("\nant: %d\nprox: %d", li->elem[index].ant, li->elem[index].prox);
            return li->elem[index].info;
        }
    }
    return NULL;
}
