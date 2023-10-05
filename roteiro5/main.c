//#include "FSE.h"
#include "menuF.h"

extern int numOpcoes;
extern char *nomeOpcoes[];
extern void (*functions[])();

void menu() {
    int opcao;
    do {
        printf("\n");
        for(int i = 0; i < numOpcoes; i++) {
            printf("%d - %s\n", i+1 ,nomeOpcoes[i]);
        }
        printf("Opcao: ");
        scanf("%d",&opcao);
        setbuf(stdin,NULL);
        if(--opcao && !menuValido()) printf("Nenhuma pilha foi criada!\n");
        else functions[opcao]();
    } while(opcao != numOpcoes);    
}

int main() {
    menu();
    return 0;
}
