#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "menu.h"
#include "FSE.h"

#define MAX_FILA 10

Fila *fila[MAX_FILA];
char nome_fila[MAX_FILA][100];
int fila_quant = 0;
int fila_alvo;

void
selecionar_fila(size_t index)
{
    fila_alvo = index;
    printf("%s\n",nome_fila[fila_alvo]);
}

void
mostrar_filas(size_t index)
{
    menu_t *menu_fila = menu_create(false);
    for(int i = 0; i < fila_quant; i++)
        menu_add_item(menu_fila,
                      menu_item_create(nome_fila[i], selecionar_fila),
                      -1);
    menu_show(menu_fila);
    menu_destroy(menu_fila);
}

void
adicionar_fila(char *nome)
{
    strcpy(nome_fila[fila_quant],nome);
    fila[fila_quant] = criaFila();
    fila_quant++;
}

int main() {
    menu_t *m = menu_create(true);
    adicionar_fila("teste1");
    adicionar_fila("teste2");
    menu_add_item(m,menu_item_create("teste",mostrar_filas),-1);
    menu_show(m);
    menu_destroy(m);
    return 0;
}