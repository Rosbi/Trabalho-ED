void inverteVetorInt(int vet[], int tamanho){
    int tam = tamanho-1;
    for(int i=0;i<=tam/2;i++){
        int aux = vet[i];
        vet[i] = vet[tam-i];
        vet[tam-i] = aux;
    }
}
void heapsort(int a[], int n, char nearFar) {
    int i = n / 2, pai, filho, t;
    int tam = n;
    while(1) {
        if (i > 0) {
            i--;
            t = a[i];
        } else {
            n--;
            if (n <= 0){
                if(nearFar == 'n')
                    return;
                else
                    return inverteVetorInt(a, tam);
            }
            t = a[n];
            a[n] = a[0];
        }
         pai = i;
         filho = i * 2 + 1;
        while (filho < n) {
            if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
                filho++;
            if (a[filho] > t) {
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