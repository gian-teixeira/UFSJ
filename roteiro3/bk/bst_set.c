

#define _SET_TYPE int 

struct traverser {
    struct traverser *left;
    struct traverser *right;
    _SET_TYPE *child;
};

struct set {
    _SET_TYPE *item;
    struct traverser *bst;
    int used_size;
    int (*value_comp)(_SET_TYPE,_SET_TYPE);
};



void set_insert(struct set *s, _SET_TYPE value)
{
    // TODO : resize
    s->item[s->used_size] = value;
    struct traverser *trav = s->bst;
    while(trav) {
        int comp = s->value_comp(*trav->child, value);
        if(comp == 0) return;
        if(comp < 0) trav = trav->right;
        else trav = trav->left;
    }
    trav->child = &(s->item[s->used_size]);
    s->used_size++;
}