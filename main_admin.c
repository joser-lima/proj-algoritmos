#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>   
#include "funcoes_admin.h"
#include "funcoes_usuario.h"

#define ADMIN_USER "admin" 
#define ADMIN_PASS "123456" 

int loginAdmin() {
    char username[50], password[50];

    printf("=== Login do Administrador ===\n");
    printf("Digite o nome de usuário: ");
    scanf("%s", username);

    printf("Digite a senha: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USER) == 0 && strcmp(password, ADMIN_PASS) == 0) {
        printf("Login bem-sucedido! Bem-vindo, administrador.\n");
        return 1;
    } else {
        printf("Nome de usuário ou senha incorretos.\n");
        return 0;
    }
}

int main() {
    Usuario usuarios[MAX_USUARIOS];
    Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
    int numusers = 0, nummoedas = 0;

    srand(time(NULL));

    abreuser(usuarios, &numusers);
    abrecriptos(criptomoedas, &nummoedas);

    if (!loginAdmin()) {
        printf("Acesso negado. Encerrando programa.\n");
        return 0;
    }

    int opcaoAdmin;
    while (1) {
        printf("\nMenu do Administrador:\n");
        printf("1. Adicionar Usuário\n");
        printf("2. Excluir Usuário\n");
        printf("3. Cadastrar Criptomoeda\n");
        printf("4. Excluir Criptomoeda\n");
        printf("5. Consultar Saldo de Investidor\n");
        printf("6. Consultar Extrato de Investidor\n");
        printf("7. Atualizar Cotações de Criptomoedas\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoAdmin);

        if (opcaoAdmin == 1) {
            adicionarUsuario(usuarios, &numusers);
        } else if (opcaoAdmin == 2) {
            excluirUsuario(usuarios, &numusers);
        } else if (opcaoAdmin == 3) {
            cadastrarCripto(criptomoedas, &nummoedas);
        } else if (opcaoAdmin == 4) {
            excluirCripto(criptomoedas, &nummoedas);
        } else if (opcaoAdmin == 5) {
            consultarSaldo(usuarios, numusers);
        } else if (opcaoAdmin == 6) {
            consultarExtrato(usuarios, numusers);
        } else if (opcaoAdmin == 7) {
            cotacao(criptomoedas, nummoedas);
            salvacriptos(criptomoedas, nummoedas);
        } else if (opcaoAdmin == 8) {
            printf("Saindo...\n");
            salvauser(usuarios, numusers);
            salvacriptos(criptomoedas, nummoedas);
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}