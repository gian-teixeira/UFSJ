#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

struct menu_item {
    char *label;
    menu_item_callback_f callback;
    struct menu_item *next;
    struct menu_item *prev;
};

struct menu {
    struct menu_item *items;
    size_t item_count;
    bool persistant;
    char *indicator;
};

struct menu_item*
menu_item_create(char *label, menu_item_callback_f callback)
{
    struct menu_item *mi = malloc(sizeof(struct menu_item));
    mi->callback = callback;
    mi->next = NULL;
    mi->prev = NULL;
    mi->label = malloc(strlen(label)+1);
    strcpy(mi->label,label);
    return mi;
}

void
menu_item_destroy(struct menu_item *mi)
{
    if(mi == NULL) return;
    if(mi->label != NULL) free(mi->label);
    free(mi);
}

struct menu*
menu_create(bool persistant) 
{
    struct menu *m = malloc(sizeof(struct menu));
    m->items = menu_item_create("", NULL);
    m->item_count = 0;
    m->persistant = persistant;
    m->indicator = NULL;
    return m;
}

void 
menu_destroy(struct menu *m)
{
    if(m == NULL) return;
    struct menu_item *tmp;
    do {
        tmp = m->items;
        m->items = m->items->next;
        free(tmp);
    } while(m->items != NULL);
    free(m);
}

bool
menu_add_item(struct menu *m, struct menu_item *mi, int pos)
{
    if(m == NULL ||
       m->items == NULL ||
       mi == NULL) return false;

    if(pos < 0) pos += m->item_count+1;
    if(pos > m->item_count) return false;

    struct menu_item *tmp = m->items;
    while(pos > 0) {
        tmp = tmp->next;
        pos--;
    }
    mi->next = tmp->next;
    mi->prev = (tmp == m->items ? NULL : tmp);
    if(tmp->next != NULL) tmp->next->prev = mi;
    tmp->next = mi;
    m->item_count++;

    return true;
}

bool
menu_remove_item(struct menu *m, int pos)
{
    if(m == NULL || m->items == NULL) return false;

    if(pos < 0) pos += m->item_count+1;
    if(pos > m->item_count+1) return false;

    struct menu_item *tmp, *last = m->items;
    while(pos > 0 && last->next) {
        last = last->next;
        pos--;
    }
    tmp = last->next;
    last->next = tmp->next;
    if(tmp->next) tmp->next->prev = last;
    menu_item_destroy(tmp);
    m->item_count--;
    
    return true;
}

bool 
menu_item_activate(struct menu *m, int pos)
{
    if(m == NULL || m->items == NULL) return false;

    if(pos < 0) pos += m->item_count+1;
    if(pos > m->item_count) return false;

    struct menu_item *tmp = m->items;
    while(pos >= 0) {
        tmp = tmp->next;
        pos--;
    }
    printf("%s\n",tmp->label);

    return true;
}

bool
menu_set_indicator(struct menu *m, char *indicator)
{
    if(m == NULL) return false;
    if(m->indicator) free(m->indicator);
    m->indicator = malloc(strlen(indicator));
    strcpy(m->indicator,indicator);
    return true;
}

#define CURSOR_UP "\e[1A"
#define CURSOR_DOWN "\e[1B"
#define ENTER 10
#define HLINE for(int i = 0; i < 15; i++) printf("="); printf("\n")


void
menu_show(struct menu *m)
{
    if(m == NULL || m->items == NULL || 
       m->item_count == 0) return;

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    do {
        HLINE;
        struct menu_item *tmp = m->items->next;
        int index = 0;
        size_t line_len, max_line_len = 0;
        while(tmp) {
            if(m->indicator) printf("%s",m->indicator);
            printf("%d %s\n", ++index, tmp->label);
            line_len = strlen(tmp->label);
            if(line_len > max_line_len) max_line_len = line_len;
            if(tmp->next == NULL) break;
            tmp = tmp->next;
        }
        if(m->indicator) line_len += strlen(m->indicator);
        HLINE;
        printf(CURSOR_UP CURSOR_UP);

        bool select = false;
        while(!select) {
            char cmd = getchar();
            switch (cmd) {
            case 'j':
                if(tmp->prev == NULL) break;
                tmp = tmp->prev;
                index--;
                printf(CURSOR_UP);
                break;
            case 'k':
                if(tmp->next == NULL) break;
                tmp = tmp->next;
                index++;
                printf(CURSOR_DOWN);
                break;
            default: 
                select = true;
                int down_lines = m->item_count - index + 2;
                while(down_lines--) printf("\r" CURSOR_DOWN);
                if(cmd == ENTER) {
                    if(tmp->callback) tmp->callback(index);
                    //if(m->persistant) system("clear");
                }
            }
        }
    } while(m->persistant);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}