#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

Lista *criaLista() {
    Lista *li;
    li = (Lista*)malloc(sizeof(Lista));
    if(li != NULL) li ->qtd = 0;
    return li;
}

void destroiLista(Lista * li) {
    if(li != NULL) free (li);
}

int tamanhoLista(Lista * li) {
    if(li == NULL ) return -1;
    return li -> qtd;
}

int listaCheia(Lista *li) {
    if(li == NULL ) return -1;
    return (li -> qtd == MAX );
}

int listaVazia(Lista * li) {
    if(li == NULL) return -1;
    return (li -> qtd == 0);
}

int insereFim(Lista *li, int elem){
    if(li == NULL ) return 0;
    if (!listaCheia(li)){
        li->dados[li->qtd] = elem;
        li->qtd++;
        printf("Elemento inserido com sucesso !\n"); 
        return 1;
    } else {
        printf ("Elemento nao inserido - Lista Cheia !\n"); 
        return 0;
    }
}

int insereInicio(Lista *li, int elem){
    if(li == NULL ) return 0;
    if (!listaCheia(li)){
        int i;
        for(i = li->qtd-1; i >= 0; i--)
            li->dados[i +1] = li->dados[i];
        li->dados[0] = elem;
        li->qtd++;
        printf("Elemento inserido com sucesso!\n"); 
        return 1;
    } else {
        printf("Elemento nao inserido - Lista Cheia!\n"); 
        return 0;
    }
}

int removeFim(Lista *li){
    if(li == NULL) return 0;
    if(!listaVazia(li)){
        li->qtd--;
        printf("Elemento removido com sucesso!\n"); 
        return 1;
    } else {
        printf("Nenhum elemento removido - Lista Vazia!\n"); 
        return 0;
    }
}

int removeInicio(Lista *li){
    if(li == NULL) return 0;
    if(!listaVazia(li)){
        int i;
        for(i = 0; i < li->qtd-1; i++)
            li->dados[i] = li->dados[i +1];
        li->qtd--;
        printf(" Elemento removido com sucesso!\n"); 
        return 1;
    } else {
        printf("Nenhum elemento removido - Lista Vazia!\n"); 
        return 0;
    }
}

int imprimeLista(Lista * li){
    if(li == NULL) return 0;
    if(listaVazia(li)){
        printf("Lista vazia !\n"); 
        return 0;
    }
    printf("Elementos :\n");
    int i;
    for(i = 0; i < li->qtd; i++)
        printf("%d ", li->dados[i]);
    printf("\n");
    return 1;
}

int procura(Lista * li, int elem) {
    int i;
    for(i = 0; i < li->qtd-1; i++)
        if(li->dados[i] == elem) break;
    if(i < li->qtd) return i;
    return -1;
}

int insereOrdenado(Lista *li, int elem) {
    if(li == NULL ) return 0;
    if(!listaCheia(li)) {
        int i, j;
        for(i = 0; i < li->qtd && li->dados[i] <= elem; i++);
        for(j = li->qtd-1; j >= i; j--)
            li->dados[j+1] = li->dados[j];
        li->dados[i] = elem;
        li->qtd++;
        printf("Elemento inserido com sucesso!\n"); 
        return 1;
    } else {
        printf("Elemento nao inserido - Lista Cheia!\n"); 
        return 0;
    }
}

int removeElemento(Lista *li, int elem) {
    if(li == NULL ) return 0;
    if(!listaVazia(li)) {
        int i;
        for(i = 0; i < li->qtd-1 && li->dados[i] != elem; i++);
        if(i == li->qtd) {
            printf("Elemento nao encontrado!\n"); 
            return 0;
        }
        for(i += 1; i < li->qtd; i++) 
            li->dados[i-1] = li->dados[i];
        li->qtd--;
        printf("Elemento removido com sucesso!\n"); 
        return 1;
    } else {
        printf("Elemento nao encontrado - Lista Vazia!\n"); 
        return 0;
    }
}