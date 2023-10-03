#include <stdio.h>
#include "cube.h"

int main() {
    cube_t *c = cube_create(3);
    printf("CUBO\n");
    printf("Comprimento do lado: %f\n", cube_get_side_length(c));
    printf("Area: %f\n", cube_get_area(c));
    printf("Volume: %f\n", cube_get_volume(c));
    return 0;
}