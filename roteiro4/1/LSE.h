/*----------------- File: Lista.h ----------------------+
|Lista Sequencial Estatica                              |
|					      		                        |
|					      		                        |
| Implementado por Guilherme C. Pena em 12/09/2023      |
| Implementacoes extras e modificacao dos comandos      |
|       de impressao feitas por Giancarlo O. Teixeira   |
+-------------------------------------------------------+ */

#ifndef LISTASE_H
#define LISTASE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int info;
    struct NO* prox;    
}NO;

typedef struct NO* Lista;

Lista* criaLista(){
    Lista *li;
    li = (Lista*) malloc (sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

int listaVazia(Lista *li){
    if(li == NULL) return 1;
    if(*li == NULL) return 1;//True - Vazia!
    return 0;//False - tem elemento!
}

NO* alocarNO(){
    return (NO*) malloc (sizeof(NO));
}

void liberarNO(NO* q){
    free(q);
}

int insereIni(Lista* li, int elem){
    if(li == NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) return 0;
    novo->info = elem;
    novo->prox = *li;
    *li = novo;
    return 1;
}

int insereFim(Lista* li, int elem){
    if(li == NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) return 0;
    novo->info = elem;
    novo->prox = NULL;
    if(listaVazia(li)){
        *li = novo;
    }else{
        NO* aux = *li;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return 1;
}

int removeIni(Lista* li){
    if(li == NULL) return 0;
    if(listaVazia(li)) return 0;
    NO* aux = *li;
    *li = aux->prox;
    liberarNO(aux);
    return 1;
}

int removeFim(Lista* li){
    if(li == NULL) return 0;
    if(listaVazia(li)) return 0;
    NO* ant, *aux = *li;
    while(aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == *li)
        *li = aux->prox;
    else   
        ant->prox = aux->prox;
    liberarNO(aux);
    return 1;
}

void imprimeLista(Lista* li){
    if(li == NULL) return;
    if(listaVazia(li)){
        return;
    }
    printf("Elementos: ");
    NO* aux = *li;
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void destroiLista(Lista* li){
    if(li != NULL){
        NO* aux;
        while((*li) != NULL){
            aux = *li;
            *li = (*li)->prox;
            liberarNO(aux);
        }
        free(li);
    }
}

/* Implementações extras */

int tamanho(Lista *li) {
    if(li == NULL) return 0;
    int tam = 0;
    NO *aux = *li;
    while(aux != NULL) {
        tam++;
        aux = aux->prox;
    }
    return tam;
}

NO *procura(Lista *li, int elem) {
    if(li == NULL) return NULL;
    NO *aux = *li;
    while(aux && aux->info != elem)
        aux = aux->prox;
    return aux;
}

int insereOrdenado(Lista *li, int elem) {
    if(li == NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) return 0;
    novo->info = elem;
    novo->prox = NULL;
    if(listaVazia(li)){
        *li = novo;
    }else{
        NO* aux = *li;
        if(aux->info > elem) {
            novo->prox = *li;
            *li = novo;
        } else {
            while(aux->prox && aux->prox->info < elem)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
    return 1;
}

int removeElemento(Lista *li, int elem) {
    if(li == NULL) return 0;
    if(listaVazia(li)) return 0;
    NO* tmp, *aux = *li;
    while(aux->prox != NULL && aux->prox->info != elem)
        aux = aux->prox;
    if(aux->prox == NULL) return 0;
    tmp = aux->prox;
    aux->prox = tmp->prox;
    liberarNO(tmp);
    return 1;
}

#endif
