# ifndef FSE_H
# define FSE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info ;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    struct NO* ini;
    struct NO* fim;
} Fila;

static NO *criaNO(int info) {
    NO *n = (NO*)malloc(sizeof(NO));
    n->info = info;
    n->prox = NULL;
    return n;
}

Fila *criaFila() {
    Fila *fi = (Fila*)malloc(sizeof(Fila));
    fi->qtd = 0;
    fi->ini = criaNO(0);
    fi->fim = fi->ini;
}

int destroiFila(Fila *fi) {
    if(fi == NULL) return 0;
    NO *tmp;
    while(fi->ini) {
        tmp = fi->ini;
        fi->ini = fi->ini->prox;
        free(tmp);
    }
    free(fi);
}

int tamanhoFila(Fila *fi){
    if(fi == NULL) return -1;
    return fi->qtd;
}

int estaVazia(Fila *fi){
    if(fi == NULL) return -1;
    return (fi->qtd == 0);
}

int verInicio(Fila *fi, int *saida) {
    if(fi == NULL || fi->ini->prox == NULL) return 0;
    *saida = fi->ini->prox->info;
    return 1;
}

int enfileirar(Fila *fi, int elem) {
    if(fi == NULL || fi->fim == NULL) return 0;
    NO *n = criaNO(elem);
    if(n == NULL) return 0;
    fi->fim->prox = n;
    fi->fim = n;
    fi->qtd++;
    return 1;
}

int desenfileirar(Fila *fi) {
    if(fi == NULL || fi->ini->prox == NULL) return 0;
    NO *tmp = fi->ini->prox;
    fi->ini->prox = tmp->prox;
    free(tmp);
    fi->qtd--;
    return 1;
}

void imprime(Fila* fi) {
    if(fi == NULL) return;
    if(estaVazia(fi)){
        printf("Fila Vazia!\n");
        return;
    }
    NO *tmp = fi->ini;
    printf("Elementos: \n");
    while(tmp = tmp->prox) printf("%d ", tmp->info);
    printf("\n");
}

# endif