#ifndef _MENU_H_
#define _MENU_H_

#include <stdbool.h>
#include <stddef.h>

typedef void (*menu_item_callback_f)(size_t index);
typedef char* menu_callback_answer;
typedef struct menu_item menu_item_t;
typedef struct menu menu_t;

struct menu;
struct menu_item;

enum menu_item_status {
    MI_SUCCESS,
    MI_NOCOMMAND,
    MI_EXECERROR
};

struct menu *menu_create(bool persistant);
void menu_destroy(struct menu *m);
bool menu_add_item(struct menu *m, struct menu_item *mi, int pos);
bool menu_remove_item(struct menu *m, int pos);
bool menu_item_activate(struct menu *m, int pos);
bool menu_set_indicator(struct menu *m, char *indicator);
void menu_show(struct menu *m);

struct menu_item *menu_item_create();
void menu_item_destroy(struct menu_item *mi);

#endif