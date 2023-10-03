#include <stdio.h>
#include "set.h"

int main() {
    set_t *e = set_create_empty();
    set_t *s = set_create_from((int[]){5,3,1,4,8},5);
    set_t *t = set_create_from((int[]){5,10,3,1,2,9,4},7);

    printf("Set <s>\ttamanho: %ld\n\telementos: ", set_size(s));
    set_print(s); printf("\n");
    printf("Set <t>\ttamanho: %ld\n\telementos: ", set_size(t));
    set_print(t); printf("\n");
    printf("Set <e>\ttamanho: %ld\n\n", set_size(e));

    printf("O set <e> eh vazio? %s\n", set_is_empty(e) ? "sim" : "nao");

    set_t *uni_st = set_union(s,t);
    set_t *int_st = set_interction(s,t);
    set_t *diff_ts = set_difference(t,s);

    printf("s | t: "); set_print(uni_st);
    printf("s & t: "); set_print(int_st);
    printf("t - s: "); set_print(diff_ts);
    printf("s == t: %s\n", set_equal(s,t) ? "sim" : "nao");
    printf("4 in t: %s\n", set_contains(t,4) ? "sim" : "nao");
    
    set_insert(s,19);
    printf("s + 19: "); set_print(s);

    set_remove(s,4);
    printf("s - 4: "); set_print(s);

    printf("max(s): %d\n", set_max(s));
    printf("min(t): %d\n", set_min(t));

    set_destroy(uni_st);
    set_destroy(int_st);
    set_destroy(diff_ts);
    set_destroy(s);
    set_destroy(t);
    set_destroy(e);
    return 0;
}