#include "cube.h"
#include <stdlib.h>

struct cube {
    float side_length;
};

struct cube *cube_create(float side_length)
{
    struct cube *c = malloc(sizeof(struct cube));
    c->side_length = side_length;
    return c;
}

void cube_destroy(struct cube *c)
{
    free(c);
}

float cube_get_side_length(struct cube *c)
{
    return c->side_length;
}

float cube_get_area(struct cube *c)
{
    float side_area = c->side_length * c->side_length;
    return 6*side_area;
}

float cube_get_volume(struct cube *c)
{
    return c->side_length * c->side_length * c->side_length;
}