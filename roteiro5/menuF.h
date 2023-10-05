#ifndef MENU_H
#define MENU_H

#include "FSE.h"

Fila *fi;
int aux, numOpcoes = 7;

void menuCriaFila() { 
    fi = criaFila(); 
}

void menuEnfileirar() {  
    scanf("%d",&aux);
    setbuf(stdin,NULL);
    enfileirar(fi,aux);
}

void menuVerInicio() { 
    verInicio(fi,&aux);
    printf("Inicio: %d\n",aux);
}

void menuDesenfileirar() { 
    verInicio(fi,&aux);
    printf("Item removido: %d\n", aux);
    desenfileirar(fi); 
} 

void menuImprimir() { 
    imprime(fi); 
}

void menuDestruir() {
    destroiFila(fi); 
} 

int menuValido() {
    return (fi != NULL);
}

char *nomeOpcoes[] = { "Criar fila", "Enfileirar um item", 
                       "Ver o inicio da fila", "Desenfileirar um item", 
                       "Imprimir a fila", "Destruir a fila", "Sair" };
void (*functions[])() = { menuCriaFila, menuEnfileirar, menuVerInicio,
                          menuDesenfileirar, menuImprimir, menuDestruir };


#endif