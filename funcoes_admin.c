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

void excluirCripto(Criptomoeda criptomoedas[], int *nummoedas) {
    if (*nummoedas == 0) {
        printf("Não há criptomoedas cadastradas para excluir.\n");
        return;
    }

    char nome[50];
    printf("Digite o nome da criptomoeda a ser excluída: ");
    scanf(" %[^\n]", nome);

    int encontrado = -1;
    for (int i = 0; i < *nummoedas; i++) {
        if (strcmp(criptomoedas[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Criptomoeda %s não encontrada.\n", nome);
        return;
    }

    printf("Detalhes da criptomoeda:\n");
    printf("Nome: %s\n", criptomoedas[encontrado].nome);
    printf("Cotação: %.2f\n", criptomoedas[encontrado].cotacao);
    printf("Taxa de Compra: %.2f%%\n", criptomoedas[encontrado].taxaCompra);
    printf("Taxa de Venda: %.2f%%\n", criptomoedas[encontrado].taxaVenda);

    printf("Tem certeza que deseja excluir esta criptomoeda? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        for (int i = encontrado; i < *nummoedas - 1; i++) {
            criptomoedas[i] = criptomoedas[i + 1];
        }
        (*nummoedas)--;
        salvacriptos(criptomoedas, *nummoedas);
        printf("Criptomoeda %s excluída com sucesso.\n", nome);
    } else {
        printf("Exclusão cancelada.\n");
    }
}

void consultarSaldo(Usuario usuarios[], int numusers) {
    char cpf[TAM_CPF];
    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);

    for (int i = 0; i < numusers; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("Saldo do investidor %s (%s):\n", usuarios[i].nome, usuarios[i].cpf);
            printf("Saldo em Reais: R$ %.2f\n", usuarios[i].saldoreal);
            printf("Saldo em Bitcoin: %.6f BTC\n", usuarios[i].saldobit);
            printf("Saldo em Ethereum: %.6f ETH\n", usuarios[i].saldoeth);
            printf("Saldo em Ripple: %.2f XRP\n", usuarios[i].saldoxrp);
            return;
        }
    }

    printf("Investidor com CPF %s não encontrado.\n", cpf);
}

void consultarExtrato(Usuario usuarios[], int numusers) {
    char cpf[TAM_CPF];
    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);

    for (int i = 0; i < numusers; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("=== Extrato do Investidor %s (%s) ===\n", usuarios[i].nome, usuarios[i].cpf);
            for (int j = 0; j < usuarios[i].quanttrans; j++) {
                printf("Data: %s | Tipo: %s | Valor: R$ %.2f | Taxa: R$ %.2f\n",
                       usuarios[i].transacoes[j].date,
                       usuarios[i].transacoes[j].tipomov,
                       usuarios[i].transacoes[j].valor,
                       usuarios[i].transacoes[j].taxamov);
            }
            return;
        }
    }

    printf("Investidor com CPF %s não encontrado.\n", cpf);
}