#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "menu.h"
#include "FSE.h"
#include <termios.h>
#include <unistd.h>

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
    menu_set_indicator(menu_fila, ". ");
    for(int i = 0; i < fila_quant; i++)
        menu_add_item(menu_fila,
                      menu_item_create(nome_fila[i], selecionar_fila),-1);
    menu_show(menu_fila);
    menu_destroy(menu_fila);
}

void
adicionar_fila(size_t index)
{
    char nome[100];

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag |= (ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    scanf("%s",nome);
    setbuf(stdin,NULL);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    strcpy(nome_fila[fila_quant],nome);
    fila[fila_quant] = criaFila();
    fila_quant++;
}

int main() {
    menu_t *m = menu_create(true);

    menu_add_item(m,menu_item_create("selecionar fila",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("adicionar fila",adicionar_fila),-1);
    menu_add_item(m,menu_item_create("enfileirar",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("desenfileirar",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("ver inicio",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("imprimir",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("destruir",mostrar_filas),-1);
    menu_add_item(m,menu_item_create("sair",mostrar_filas),-1);

    menu_show(m);
    menu_destroy(m);
    return 0;
}