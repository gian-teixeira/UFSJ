#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

struct avl_node {
    struct avl_node *parent;
    struct avl_node *right;
    struct avl_node *left;
    size_t right_height;
    size_t left_height;
    void *value;
};

struct avl_node *avl_node_create(struct avl_node *right,
                                 struct avl_node *left,
                                 struct avl_node *parent,
                                 void *value)
{
    struct avl_node *node = malloc(sizeof(struct avl_node));
    node->parent = parent;
    node->right = right;
    node->left = left;
    node->value = value;
    return node;
}

void avl_node_destroy(struct avl_node *node)
{
    if(node == NULL) return;
    avl_node_destroy(node->right);
    avl_node_destroy(node->left);
    free(node);
}

struct avl {
    struct avl_node *root;
    int (*value_compare)(void*,void*);
};

struct avl *avl_create(int (*value_compare)(void*,void*))
{
    struct avl *a = malloc(sizeof(struct avl));
    a->value_compare = value_compare;
    a->root = NULL;
    return a;
}

void avl_balance(struct avl_node *target)
{
    struct avl_node *tmp;
    if(target->right_height > target->left_height) {
        switch(target->parent->right == target) {
        case 0:
            tmp = target->parent->parent;
            target->parent->parent = target;
            target->parent->right = target->left;
            target->left = target->parent;
            target->parent = tmp;
        case 1:
            tmp = target->parent->parent;
            target->parent->parent = target;
            target->parent->left = target->right;
            target->right = target->parent;
            target->parent = tmp;
        }
    }
    else {
        switch(target->parent->right == target) {
        case 0:
            tmp = target->parent->parent;
            target->parent->parent = target;
            target->parent->left = target->right;
            target->right = target->parent;
            target->parent = tmp;
        case 1:
            tmp = target->parent->parent;
            target->parent->parent = target;
            target->parent->right = target->left;
            target->left = target->parent;
            target->parent = tmp;
        }
    }
}

void avl_backpropagate(struct avl_node *source)
{
    size_t height_diff = source->right_height - source->left_height;
    if(height_diff > 1 || height_diff < -1) avl_balance(source);
    if(source->parent) {
        if(source == source->parent->left) source->parent->left_height++;
        if(source == source->parent->right) source->parent->right_height++;
        avl_backpropagate(source->parent);
    }
}

void avl_insert(struct avl *a,
                void *value)
{
    struct avl_node *t, *p;
    t = a->root;
    while(t != NULL) {
        int comp = a->value_compare(t->value,value);
        if(comp == 0) return;
        if(comp == -1) {
            if(t->right == NULL) 
                t->right = avl_node_create(NULL,NULL,t,value);
            else t = t->right;
        }
        if(comp == 1) {
            if(t->left == NULL) 
                t->left = avl_node_create(NULL,NULL,t,value);
            else t = t->left;
        }
    }
    printf("%p\n",t);
    printf("%p\n",a->root);
    //avl_backpropagate(t);
}

int comp(void *va, void *vb)
{
    int *a = va, *b = vb;
    return (*a < *b);
}



int main() {
    struct avl *a = avl_create(comp);
    int v = 10;
    avl_insert(a,&v);
    int *test = a->root->value;
    //printf("%d\n",*((int*)a->root));
    return 0;
}