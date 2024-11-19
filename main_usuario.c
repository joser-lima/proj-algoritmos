#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_usuario.h"
#include "criptomoedas.h"

#define MAX_CRIPTOMOEDAS 100

int main() {
    Usuario usuarios[MAX_USUARIOS];
    Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
    int numusers = 0, nummoedas = 0;
    Usuario useratual;
    int opcaouser;

    srand(time(NULL));
    abreuser(usuarios, &numusers);
    abrecriptos(criptomoedas, &nummoedas);  

    while (1) {
        printf("\n1. Cadastrar\n2. Login\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcaouser);

        if (opcaouser == 1) {
            cadastro(usuarios, &numusers);
        } else if (opcaouser == 2) {
            if (login(usuarios, numusers, &useratual)) {
                int respuser;
                while (1) {
                    printf("\n1. Depósito\n2. Comprar Criptomoeda\n3. Vender Criptomoeda\n4. Ver Extrato\n5. Sacar\n6. Consultar Saldo\n7. Sair\nEscolha uma opção: ");
                    scanf("%d", &respuser);

                    if (respuser == 1) {
                        deposito(&useratual);
                        salvauser(usuarios, numusers);
                    } else if (respuser == 2) {
                        compracripto(&useratual, criptomoedas, nummoedas); 
                        salvauser(usuarios, numusers);
                    } else if (respuser == 3) {
                        vendacripto(&useratual, criptomoedas, nummoedas);
                        salvauser(usuarios, numusers);
                    } else if (respuser == 4) {
                        extrato(&useratual);
                    } else if (respuser == 5) {
                        saque(&useratual);
                        salvauser(usuarios, numusers);
                    } else if (respuser == 6) {
                        saldo(&useratual);
                    } else if (respuser == 7) {
                        break;
                    } else {
                        printf("Opção inválida.\n");
                    }
                }
            } else {
                printf("CPF ou senha incorretos.\n");
            }
        } else if (opcaouser == 3) {
            printf("Saindo...\n");
            salvauser(usuarios, numusers);
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
