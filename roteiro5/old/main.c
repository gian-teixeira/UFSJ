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
int fila_alvo = -1;

void
selecionar_fila(size_t index)
{
    fila_alvo = index - 1;
    printf("%s\n",nome_fila[fila_alvo]);
}

void
menu_mostrar_filas(size_t index)
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
menu_adicionar_fila(size_t index)
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
    if(fila_alvo == -1) fila_alvo = 0;
}

void
menu_enfileirar(size_t index)
{
    int item;

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag |= (ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    if(fila_alvo == -1) printf("Ainda nao foi adicionada nenhuma fila!\n");
    else {
        scanf("%d",&item);
        setbuf(stdin,NULL);
        printf("%s\n",nome_fila[fila_alvo]);
        enfileirar(fila[fila_alvo],item);
        imprime(fila[fila_alvo]);
    }

    setbuf(stdin,NULL);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void 
menu_imprimir(size_t index)
{
    imprime(fila[fila_alvo]);
}

void
menu_desenfileirar(size_t index)
{
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag |= (ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    if(fila_alvo == -1) printf("Ainda nao foi adicionada nenhuma fila!\n");
    else {
        int item;
        verInicio(fila[fila_alvo],&item);
        int op = desenfileirar(fila[fila_alvo]);
        if(op) printf("Item retirado : %d\n",item);
        else printf("Lista vazia!\n");
    }

    imprime(fila[fila_alvo]);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}



char*
header()
{
    if(fila_alvo == -1) return NULL;
    return nome_fila[fila_alvo];
}

int main() {
    menu_t *m = menu_create(true);
    menu_set_header(m,header);

    menu_add_item(m,menu_item_create("selecionar fila",menu_mostrar_filas),-1);
    menu_add_item(m,menu_item_create("adicionar fila",menu_adicionar_fila),-1);
    menu_add_item(m,menu_item_create("enfileirar",menu_enfileirar),-1);
    menu_add_item(m,menu_item_create("enfileirar",menu_desenfileirar),-1);
    menu_add_item(m,menu_item_create("imprimir",menu_imprimir),-1);


    menu_show(m);
    menu_destroy(m);
    return 0;
}