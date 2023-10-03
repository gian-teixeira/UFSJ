#include <stdio.h>
#include "LCSE.h"

int main() {
    int a[] = {10, 7, 3, 8, 3, 1, 4, 6, 8, 17};

    Lista *li = criaLista();

    printf("Inserindo no fim: ");
    for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%d ",a[i]);
        insereFim(li,a[i]);
    }
    printf("\n");
    imprimeLista(li);
    printf("Tamanho: %d\n", tamanho(li));
    printf("\n");

    printf("7 esta presente na lista? %s\n",
            procura(li,7) ? "sim" : "nao");
    printf("81 esta presente na lista? %s\n",
            procura(li,81) ? "sim" : "nao");

    /*removeElemento(li,3);
    printf("\nSe removeElemento(li,3), 3 esta presente na lista? %s\n",
            procura(li,3) ? "sim" : "nao");
    imprimeLista(li);

    removeElemento(li,3);
    printf("\nSe removeElemento(li,3), 3 esta presente na lista? %s\n",
            procura(li,3) ? "sim" : "nao");
    imprimeLista(li);*/

    destroiLista(li);

    return 0;
}