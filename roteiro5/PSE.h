# ifndef PSE_H
# define PSE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info ;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    struct NO* topo;
} Pilha;

static NO *criaNO(int info) {
    NO *n = (NO*)malloc(sizeof(NO));
    n->info = info;
    n->prox = NULL;
    return n;
}

Pilha *criaPilha() {
    Pilha *pi = (Pilha*)malloc(sizeof(Pilha));
    pi->qtd = 0;
    pi->topo = criaNO(0);
    return pi;
}

int destroiPilha(Pilha *pi) {
    if(pi == NULL) return 0;
    NO *tmp;
    while(pi->topo) {
        tmp = pi->topo;
        pi->topo = pi->topo->prox;
        free(tmp);
    }
    free(pi);
}

int tamanhoPilha(Pilha *pi){
    if(pi == NULL) return -1;
    return pi->qtd;
}

int estaVazia(Pilha *pi){
    if(pi == NULL) return -1;
    return (pi->qtd == 0);
}

int verTopo(Pilha *pi, int *saida) {
    if(pi == NULL || pi->topo->prox == NULL) return 0;
    *saida = pi->topo->prox->info;
    return 1;
}

int empilhar(Pilha *pi, int elem) {
    if(pi == NULL || pi->topo == NULL) return 0;
    NO *n = criaNO(elem);
    if(n == NULL) return 0;
    n->prox = pi->topo->prox;
    pi->topo->prox = n;
    pi->qtd++;
    return 1;
}

int desempilhar(Pilha *pi) {
    if(pi == NULL || pi->topo == NULL || estaVazia(pi)) return 0;
    NO *tmp = pi->topo->prox;
    pi->topo->prox = tmp->prox;
    free(tmp);
    pi->qtd--;
    return 1;
}

void imprime(Pilha* pi) {
  if(pi == NULL) return;
  if(estaVazia(pi)){
    printf("Pilha Vazia!\n");
    return;
  }
  NO *tmp = pi->topo;
  printf("Elementos: \n");
  while(tmp = tmp->prox) printf("%d ", tmp->info);
  printf("\n");
}

# endif