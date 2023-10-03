
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct set {
    SET_TYPE *item;
    int total_size;
    int used_size;
};

struct set_iterator {
    struct set *target_set;
    int index;
};

/* Private functions */

static int set_is_full(struct set *s);
static void set_resize(struct set *s);
static int set_get_pos(struct set *s, SET_TYPE value);

/* Implementation */

struct set *set_create_empty()
{
    struct set *s = malloc(sizeof(struct set));
    s->item = malloc(sizeof(SET_TYPE));
    printf("%p\n",s->item);
    s->total_size = 1;
    s->used_size = 0;
    return s;
}

struct set *set_create_from(SET_TYPE *base_arr, int base_arr_size)
{
    struct set *s = set_create_empty();
    if(base_arr) 
        while(base_arr_size--) {
            set_insert(s,*(base_arr + base_arr_size));
        }
    return s;
}

struct set *set_union(struct set *s, struct set *t)
{
    struct set *union_set = set_copy(s);
    for(int i = 0; i < t->used_size; i++)
        set_insert(union_set,t->item[i]);
    return union_set;
}

struct set *set_interction(struct set *s, struct set *t)
{
    struct set *inter_set = set_copy(s);
    for(int i = 0; i < s->used_size; i++)
        if(!set_contains(t,s->item[i])) {
            set_remove(inter_set,s->item[i]);
        }
    return inter_set;
}

struct set *set_difference(struct set *s, struct set *t)
{
    struct set *diff_set = set_copy(s);
    for(int i = 0; i < t->used_size; i++) {
        set_remove(diff_set,t->item[i]);
    }
    return diff_set;
}

struct set *set_copy(struct set *s)
{
    struct set *t = set_create_empty();
    for(int i = 0; i < s->used_size; i++) {
        set_insert(t,s->item[i]);
    }
    return t;
}

void set_print(struct set *s)
{
    if(set_is_empty(s)) printf(" _ \n");
    for(int i = 0; i < s->used_size; i++) {
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
    int i = set_get_pos(s,value);
    if(s->item[i] == value) return;
    
    set_resize(s);
    s->item[s->used_size] = value;
    while(i < s->used_size) {
        if(s->item[s->used_size] < s->item[i]) {
            SET_TYPE tmp = s->item[i];
            s->item[i] = s->item[s->used_size];
            s->item[s->used_size] = tmp;
        }
        i++;
    }
    s->used_size++;
}

void set_remove(struct set *s, SET_TYPE value) {
    int i = set_get_pos(s,value);
    if(s->item[i] != value) return;
    
    set_resize(s);
    s->used_size--;
    while(i < s->used_size) {
        s->item[i] = s->item[i+1];
        i++;
    }
}

bool set_equal(struct set *s, struct set *t)
{
    if(set_size(s) != set_size(t)) return false; 
    for(int i = 0; i < s->used_size; i++) {
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
    return !(s->used_size); 
}

size_t set_size(struct set *s)
{ 
    return s->used_size; 
}

SET_TYPE set_min(struct set *s) 
{ 
    return s->item[0]; 
}

SET_TYPE set_max(struct set *s) 
{ 
    return s->item[s->used_size-1]; 
}


struct set_iterator *set_get_iterator(struct set *s)
{
    struct set_iterator *si = malloc(sizeof(struct set_iterator));
    si->target_set = s;
    si->index = 0;
}

SET_TYPE set_iterator_get_value(struct set_iterator *si)
{
    return si->target_set->item[si->index];
}

bool set_iterator_is_valid(struct set_iterator *si)
{
    return (si->index >= 0 && 
            si->index < si->target_set->used_size);
}

void set_iterator_next(struct set_iterator *si)
{
    if(!set_iterator_is_valid(si)) return;
    si->index++;
}

void set_iterator_previous(struct set_iterator *si)
{
    if(!set_iterator_is_valid(si)) return;
    si->index--;
}

void set_iterator_destroy(struct set_iterator *si)
{
    free(si);
}

/* Static implementations */

static int set_is_full(struct set *s) 
{
    return (s->total_size == s->used_size);
}

static void set_resize(struct set *s) 
{
    int needed_size = s->total_size;
    if(s->total_size == s->used_size) needed_size *= 2;
    else if(s->total_size > 3*s->used_size) needed_size -= s->used_size;
    if(needed_size != s->total_size) {
        s->total_size = needed_size;
        s->item = realloc(s->item, s->total_size*sizeof(SET_TYPE));
    }
}

static int set_get_pos(struct set *s, SET_TYPE value)
{
    int i = 0;
    while(i < s->used_size && s->item[i] < value) i++;
    return i;
}