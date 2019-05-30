#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"lista.h"

#define NULO -1

bool emptyList(Lista);
int getLivre(Lista);

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
        li->elem[i].info = NULL;
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

        if(emptyList(li)){
          li->prim = livre;
          li->ult = livre;
          printf("oio");fflush(stdout);
        }

        li->elem[livre].info = calloc(1, tamanho);
        memcpy(li->elem[livre].info, infor, tamanho);

        li->elem[livre].prox = li->livre;
        li->elem[livre].ant = li->ult;printf("´´%d\n", li->elem[li->ult].prox);fflush(stdout);
        li->elem[li->ult].prox = livre;//printf("``%p\n", li->elem[0].info);fflush(stdout);
        li->ult = livre;
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
        }
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
    /*//int index = li->prim;
    int j;printf("++%d\n", li->prim);fflush(stdout);
    for(j=0;j<li->max;j++){printf("--%d\n", j);fflush(stdout);
        //index = li->elem[index].prox;
        if(!li->elem[j].info){
          break;
        }
    }*/
    if(li->livre == -1){
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

Item getItem(Lista lis, int i){
    struct ListaImplementada *li = lis;
    if(emptyList(li)){
        return NULL;
    }

    int index = li->prim;
    if(i<li->max)
      for(int j=0;j<i-1;j++){
          index = li->elem[index].prox;
      }

    if(i <= li->max && index != NULO){
        if(li->elem[index].info){
            return li->elem[index].info;
        }
    }
    return NULL;
}
