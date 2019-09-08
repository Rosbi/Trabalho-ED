#include"sort.h"

struct toBeSorted{
  char id[15];
  double distancia;
};

void inverteVetorInt(struct toBeSorted vet[], int tamanho){
    int tam = tamanho-1;
    for(int i=0;i<=tam/2;i++){
        struct toBeSorted aux = vet[i];
        vet[i] = vet[tam-i];
        vet[tam-i] = aux;
    }
}
void heapsort(void* aa, int n, char nearFar) {
    struct toBeSorted* a = aa;
    struct toBeSorted t;
    int i = n / 2, pai, filho;
    int tam = n;
    while(1) {
        if (i > 0) {
            i--;
            t = a[i];
        } else {
            n--;
            if (n <= 0){
                if(nearFar == '-')
                    return;
                else{
                    inverteVetorInt(a, tam);
                    return;
                }
            }
            t = a[n];
            a[n] = a[0];
        }
         pai = i;
         filho = i * 2 + 1;
        while (filho < n) {
            if ((filho + 1 < n)  &&  (a[filho + 1].distancia > a[filho].distancia))
                filho++;
            if (a[filho].distancia > t.distancia) {
                a[pai] = a[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        a[pai] = t;
   }
}
