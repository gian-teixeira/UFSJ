#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* strcmp que nao diferencia letras maiusculas e minusculas */
int strcmpi(char *s, char *t) {
    while(*s && tolower(*s) == tolower(*t)) { s++; t++; }
    return *s - *t;
}

typedef struct produto {
    char *nome;
    double preco;
    int quantidade;
} Produto;

typedef struct catalogo {
    Produto produtos[100];
    int nprodutos;
} CatalogoProdutos;

void criarCatalogo(CatalogoProdutos *c)  {
    c->nprodutos = 0;
}

void excluirCatalogo(CatalogoProdutos *c) {
    for(int i = 0; i < c->nprodutos; i++)
        if(c->produtos[i].nome) {
            free(c->produtos[i].nome);
        }
}

void adicionarProduto(CatalogoProdutos *c, 
                      char *nome, double preco, int quantidade) {
    Produto *novoProduto = c->produtos + c->nprodutos;
    novoProduto->preco = preco;
    novoProduto->quantidade = quantidade;
    novoProduto->nome = malloc(strlen(nome)+1);
    strcpy(novoProduto->nome,nome);
    c->nprodutos++;
}

int verificarEstoque(CatalogoProdutos *c, char *nome) {
    for(int i = 0; i < c->nprodutos; i++) {
        if(strcmpi(c->produtos[i].nome,nome)) continue;
        return c->produtos[i].quantidade;
    }
    return 0;
}

void imprimirProduto(Produto *p) {
    printf("- %s:\n", p->nome);
    printf("\tQuantidade : %d\n",p->quantidade);
    printf("\tPreco : %.2lf\n",p->preco);
}

void imprimirCatalogo(CatalogoProdutos *c) {
    for(int i = 0; i < c->nprodutos; i++)
        imprimirProduto(c->produtos + i);
}

int main() {
    CatalogoProdutos c;
    criarCatalogo(&c);
    adicionarProduto(&c,"banana",9.90f,15);
    adicionarProduto(&c,"mamao",14.80f,10);
    imprimirCatalogo(&c);
    printf("\nVerificar estoque [BanAna] = %d\n",
            verificarEstoque(&c,"BanAna"));
    printf("Verificar estoque [mamao] = %d\n",
            verificarEstoque(&c,"mamao"));
    excluirCatalogo(&c);
    return 0;
}