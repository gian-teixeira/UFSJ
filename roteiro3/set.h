#ifndef _SET_H_
#define _SET_H_

#define SET_TYPE int

#include <stdbool.h>
#include <stddef.h>

typedef struct set set_t;
struct set;

struct set *set_create_empty();
struct set *set_create_from(SET_TYPE *base_arr, int base_arr_size);
struct set *set_union(struct set *s, struct set *t);
struct set *set_interction(struct set *s, struct set *t);
struct set *set_difference(struct set *s, struct set *t);
struct set *set_copy(struct set *s);

bool set_equal(struct set *s, struct set *t);
bool set_contains(struct set *s, SET_TYPE value);
bool set_is_empty(struct set *s);

void set_print(struct set *s);
void set_destroy(struct set *s);
void set_insert(struct set *s, SET_TYPE value);
void set_remove(struct set *s, SET_TYPE value);

size_t set_size(struct set *s);
SET_TYPE set_max(struct set *s);
SET_TYPE set_min(struct set *s);

#endif