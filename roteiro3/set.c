
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct set {
    SET_TYPE *item;
    int size;
};

struct set_iterator {
    struct set *target_set;
    int index;
};

static int set_get_pos(struct set *s, SET_TYPE value);

struct set *set_create_empty()
{
    struct set *s = malloc(sizeof(struct set));
    s->item = NULL;
    s->size = 0;
    return s;
}

struct set *set_create_from(SET_TYPE *base_arr, int base_arr_size)
{
    struct set *s = set_create_empty();
    if(base_arr) 
        for(int i = 0; i < base_arr_size; i++) {
            set_insert(s,base_arr[i]);
        }
    return s;
}

struct set *set_union(struct set *s, struct set *t)
{
    struct set *union_set = set_copy(s);
    for(int i = 0; i < t->size; i++)
        set_insert(union_set,t->item[i]);
    return union_set;
}

struct set *set_interction(struct set *s, struct set *t)
{
    struct set *inter_set = set_copy(s);
    for(int i = 0; i < s->size; i++)
        if(!set_contains(t,s->item[i])) {
            set_remove(inter_set,s->item[i]);
        }
    return inter_set;
}

struct set *set_difference(struct set *s, struct set *t)
{
    struct set *diff_set = set_copy(s);
    for(int i = 0; i < t->size; i++) {
        set_remove(diff_set,t->item[i]);
    }
    return diff_set;
}

struct set *set_copy(struct set *s)
{
    struct set *t = set_create_empty();
    for(int i = 0; i < s->size; i++) {
        set_insert(t,s->item[i]);
    }
    return t;
}

void set_print(struct set *s)
{
    if(set_is_empty(s)) printf(" _ \n");
    for(int i = 0; i < s->size; i++) {
        printf("%d ",s->item[i]);
    }
    printf("\n");
}

void set_destroy(struct set *s)
{
    if(s->item) free(s->item);
    free(s);
}

void set_insert(struct set *s, SET_TYPE value)
{
    if(s->item == NULL) {
        s->item = malloc(sizeof(SET_TYPE));
        *s->item = value;
    }
    else {
        int i = set_get_pos(s,value);
        if(s->item[i] == value) return;
    
        s->item = realloc(s->item, (s->size+1)*sizeof(SET_TYPE));
        s->item[s->size] = value;
        while(i < s->size) {
            if(s->size > 0 && 
               s->item[s->size] < s->item[i]) {
                SET_TYPE tmp = s->item[i];
                s->item[i] = s->item[s->size];
                s->item[s->size] = tmp;
            }
            i++;
        }
    }
    s->size++;
}

void set_remove(struct set *s, SET_TYPE value) {
    if(s->item == NULL) return;

    int i = set_get_pos(s,value);
    if(s->item[i] != value) return;

    while(i < s->size - 1) {
        s->item[i] = s->item[i+1];
        i++;
    }
    s->item = realloc(s->item, (s->size-1)*sizeof(SET_TYPE));
    s->size--;
}

bool set_equal(struct set *s, struct set *t)
{
    if(set_size(s) != set_size(t)) return false; 
    for(int i = 0; i < s->size; i++) {
        if(s->item[i] != t->item[i]) return false;
    }
    return true;
}

bool set_contains(struct set *s, SET_TYPE value)
{
    int i = set_get_pos(s,value);
    return (s->item[i] == value);
}

bool set_is_empty(struct set *s) 
{
    return !(s->size); 
}

size_t set_size(struct set *s)
{ 
    return s->size; 
}

SET_TYPE set_min(struct set *s) 
{ 
    return s->item[0]; 
}

SET_TYPE set_max(struct set *s) 
{ 
    return s->item[s->size-1]; 
}

/* Static implementations */

static int set_get_pos(struct set *s, SET_TYPE value)
{
    int i = 0;
    while(i < s->size - 1 && s->item[i] < value) i++;
    return i;
}