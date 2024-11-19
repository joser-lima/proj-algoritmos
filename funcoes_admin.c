#include <stdio.h>
#include <string.h>
#include "funcoes_admin.h"
#include "criptomoedas.h"
#include "funcoes_usuario.h"

void adicionarUsuario(Usuario usuarios[], int *numusers) {
    if (*numusers >= MAX_USUARIOS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }

    Usuario novoUsuario;
    printf("Digite o nome do novo usuário: ");
    scanf(" %[^\n]", novoUsuario.nome);

    printf("Digite o CPF do novo usuário: ");
    scanf("%s", novoUsuario.cpf);

    printf("Digite a senha (6 dígitos): ");
    scanf("%s", novoUsuario.senha);

    novoUsuario.saldoreal = 0.0;
    novoUsuario.saldobit = 0.0;
    novoUsuario.saldoeth = 0.0;
    novoUsuario.saldoxrp = 0.0;

    usuarios[*numusers] = novoUsuario;
    (*numusers)++;
    salvauser(usuarios, *numusers);

    printf("Novo usuário adicionado com sucesso!\n");
}

void excluirUsuario(Usuario usuarios[], int *numusers) {
    if (*numusers == 0) {
        printf("Não há usuários cadastrados para excluir.\n");
        return;
    }

    char cpf[TAM_CPF];
    printf("Digite o CPF do usuário a ser excluído: ");
    scanf("%s", cpf);

    int encontrado = -1;
    for (int i = 0; i < *numusers; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Usuário com CPF %s não encontrado.\n", cpf);
        return;
    }

    printf("Tem certeza que deseja excluir o usuário %s (CPF: %s)? (s/n): ", usuarios[encontrado].nome, usuarios[encontrado].cpf);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        for (int i = encontrado; i < *numusers - 1; i++) {
            usuarios[i] = usuarios[i + 1];
        }

        (*numusers)--;
        salvauser(usuarios, *numusers);
        printf("Usuário com CPF %s excluído com sucesso.\n", cpf);
    } else {
        printf("Exclusão cancelada.\n");
    }
}

void cadastrarCripto(Criptomoeda criptomoedas[], int *nummoedas) {
    if (*nummoedas >= MAX_CRIPTOMOEDAS) {
        printf("Limite máximo de criptomoedas atingido.\n");
        return;
    }

    Criptomoeda novaCripto;
    printf("Digite o nome da criptomoeda: ");
    scanf(" %[^\n]", novaCripto.nome);
    printf("Digite a cotação inicial: ");
    scanf("%f", &novaCripto.cotacao);
    printf("Digite a taxa de compra (em %%): ");
    scanf("%f", &novaCripto.taxaCompra);
    printf("Digite a taxa de venda (em %%): ");
    scanf("%f", &novaCripto.taxaVenda);

    criptomoedas[*nummoedas] = novaCripto;
    (*nummoedas)++;
    salvacriptos(criptomoedas, *nummoedas);

    printf("Criptomoeda %s cadastrada com sucesso!\n", novaCripto.nome);
}