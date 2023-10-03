#ifndef _CUBE_H_
#define _CUBE_H_

typedef struct cube cube_t;
struct cube;

struct cube *cube_create(float side_length);
void cube_destroy(struct cube *c);
float cube_get_side_length(struct cube *c);
float cube_get_area(struct cube *c);
float cube_get_volume(struct cube *c);

#endif