#ifndef MENU_H
#define MENU_H

#include "PSE.h"

Pilha *pi;
int aux, numOpcoes = 7;

void menuCriaPilha() { 
    pi = criaPilha(); 
}

void menuEmpilhar() {  
    scanf("%d",&aux);
    setbuf(stdin,NULL);
    empilhar(pi,aux);
}

void menuVerTopo() { 
    verTopo(pi,&aux);
    printf("Topo: %d\n",aux);
}

void menuDesempilhar() { 
    desempilhar(pi); 
} 

void menuImprimir() { 
    imprime(pi); 
}

void menuDestruir() {
    destroiPilha(pi); 
} 

int menuValido() {
    return (pi != NULL);
}

char *nomeOpcoes[] = { "Criar pilha", "Empilhar um item", 
                       "Ver o topo da pilha", "Desempilhar um item", 
                       "Imprimir a pilha", "Destruir a pilha", "Sair" };
void (*functions[])() = { menuCriaPilha, menuEmpilhar, menuVerTopo,
                          menuDesempilhar, menuImprimir, menuDestruir };


#endif