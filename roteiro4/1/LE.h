/*----------------- File: Lista.h ----------------------+
|Lista Sequencial Estatica                              |
|					      		                        |
|					      		                        |
| Implementado por Guilherme C. Pena em 12/09/2023      |
| Implementacoes extras e modificacao dos comandos      |
|       de impressao feitas por Giancarlo O. Teixeira   |
+-------------------------------------------------------+ */

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
    int qtd;
    int dados[MAX];
}Lista;

Lista* criaLista(){
    Lista* li;
    li = (Lista*) malloc (sizeof(Lista));
    if(li != NULL)
        li->qtd = 0;
    return li;
}

void destroiLista(Lista *li){
    if(li != NULL)
        free(li);
}

int tamanhoLista(Lista *li){
    if(li == NULL)
        return -1;
    return li->qtd;
}

int listaCheia(Lista *li){
    if(li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int listaVazia(Lista *li){
    if(li == NULL)
        return -1;
    return (li->qtd == 0);
}

int insereFim(Lista* li, int elem){
    if(li == NULL) return 0;
    if(!listaCheia(li)){
        li->dados[li->qtd] = elem;
        li->qtd++;
        return 1;
    }else{
        return 0;
    }
}

int insereIni(Lista* li, int elem){
    if(li == NULL) return 0;
    if(!listaCheia(li)){
        int i;
        for(i=li->qtd; i>0; i--){
            li->dados[i] = li->dados[i-1];
        }
        li->dados[0] = elem;
        li->qtd++;
        return 1;
    }else{
        return 0;
    }
}

int imprimeLista(Lista *li){
    if(li == NULL) return 0;
    int i;
    printf("Elementos: ");
    for(i=0; i<li->qtd; i++){
        printf("%d ", li->dados[i]);
    }
    printf("\n");
    return 1;
}

int removeFim(Lista* li){
    if(li == NULL) return 0;
    if(!listaVazia(li)){
        li->qtd--;
        return 1;
    }else return 0;
}

int removeIni(Lista *li){
    if(li == NULL ) return 0;
    if(!listaVazia(li)){
        int i;
        for(i=0; i<li->qtd-1; i++)
            li->dados[i] = li->dados[i+1];
        li->qtd--;
        return 1;
    } else{
        return 0;
    }
}

/* Implementações extras */

int procura(Lista *li, int elem) {
    if(li == NULL ) return 0;
    if(listaVazia(li)) return -1;
    int i;
    for(i = 0; i < li->qtd; i++)
        if(li->dados[i] == elem) return i;
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
        return 1;
    } else {
        return 0;
    }
}

int removeElemento(Lista *li, int elem) {
    if(li == NULL ) return 0;
    if(!listaVazia(li)) {
        int i;
        for(i = 0; i < li->qtd-1 && li->dados[i] != elem; i++);
        if(i == li->qtd) { 
            return 0;
        }
        for(i += 1; i < li->qtd; i++) 
            li->dados[i-1] = li->dados[i];
        li->qtd--;
        return 1;
    } else { 
        return 0;
    }
}

# endif