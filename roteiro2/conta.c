#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta {
    int numero;
    double saldo;
    char *titular;
} ContaBancaria;

void criarConta(ContaBancaria* c, int numero, char *titular)  {
    c->numero = numero;
    c->saldo = 0;
    c->titular = malloc(strlen(titular)+1);
    strcpy(c->titular,titular);
}

void excluirConta(ContaBancaria* c) {
    if(c->titular) free(c->titular);
}

void depositar(ContaBancaria *c, double valor) { 
    c->saldo += valor; 
}

void sacar(ContaBancaria *c, double valor) {
    if(c->saldo < valor) return;
    c->saldo -= valor;
}

double consultarSaldo(ContaBancaria *c) { 
    return c->saldo;
}

void imprimirInfo(ContaBancaria *c) {
    printf("Conta %d:\n", c->numero);
    printf("\tTitular: %s\n", c->titular);
    printf("\tSaldo: %.2lf\n", consultarSaldo(c));
}

int main() {
    ContaBancaria conta;
    criarConta(&conta,222050010,"Giancarlo");
    depositar(&conta,150.0f);
    sacar(&conta,75.4f);
    imprimirInfo(&conta);
    excluirConta(&conta);
    return 0;
}