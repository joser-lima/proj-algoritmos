#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes_usuario.h"
#include "criptomoedas.h"

float variacao() {
    return (rand() % 11 - 5) / 100.0;
}

void cadastro(Usuario usuarios[], int *numusers) {
    if (*numusers >= MAX_USUARIOS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }

    Usuario novouser;
    printf("Digite o nome: ");
    scanf(" %[^\n]", novouser.nome);

    printf("Digite o CPF: ");
    scanf("%s", novouser.cpf);

    printf("Digite a senha (6 dígitos): ");
    scanf("%s", novouser.senha);

    novouser.saldoreal = 0.0;
    novouser.saldobit = 0.0;
    novouser.saldoeth = 0.0;
    novouser.saldoxrp = 0.0;
    novouser.quanttrans = 0;

    usuarios[*numusers] = novouser;
    (*numusers)++;

    printf("Usuário cadastrado com sucesso! Bem-vindo %s\n", novouser.nome);
}

int login(Usuario usuarios[], int numusers, Usuario *userlogado) {
    char cpf[TAM_CPF], senha[TAM_SENHA];
    printf("Digite o CPF: ");
    scanf("%s", cpf);

    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < numusers; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            *userlogado = usuarios[i];
            return 1;
        }
    }
    return 0;
}

void saque(Usuario *usuario) {
    float valor;
    printf("Digite o valor que deseja sacar: ");
    scanf("%f", &valor);

    if (usuario->saldoreal < valor) {
        printf("Saldo insuficiente!\n");
        return;
    }

    usuario->saldoreal -= valor;
    salvatrans(usuario, "Saque", valor, 0);
    printf("Saque realizado com sucesso! Saldo atual: R$ %.2f\n", usuario->saldoreal);
}

void deposito(Usuario *usuario) {
    float valor;
    printf("Digite o valor que deseja depositar: ");
    scanf("%f", &valor);
    usuario->saldoreal += valor;
    salvatrans(usuario, "Depósito", valor, 0);
    printf("Depósito realizado com sucesso! Saldo atual: R$ %.2f\n", usuario->saldoreal);
}


void extrato(Usuario *usuario) {
    printf("Extrato de transações de %s:\n", usuario->nome);
    for (int i = 0; i < usuario->quanttrans; i++) {
        printf("Data: %s | Tipo: %s | Valor: R$ %.2f | Taxa: R$ %.2f\n",
               usuario->transacoes[i].date,
               usuario->transacoes[i].tipomov,
               usuario->transacoes[i].valor,
               usuario->transacoes[i].taxamov);
    }
    salvaextrato(usuario);
}

void saldo(Usuario *usuario) {
    printf("Saldo de %s:\n", usuario->nome);
    printf("Saldo em Reais: R$ %.2f\n", usuario->saldoreal);
    printf("Saldo em Bitcoin: %.6f BTC\n", usuario->saldobit);
    printf("Saldo em Ethereum: %.6f ETH\n", usuario->saldoeth);
    printf("Saldo em Ripple: %.2f XRP\n", usuario->saldoxrp);
}

void cotacao(Criptomoeda criptomoedas[], int nummoedas) {
    printf("=== Atualizando Cotações ===\n");
    for (int i = 0; i < nummoedas; i++) {
        float variacao = (rand() % 11 - 5) / 100.0;
        float cotacaoAntiga = criptomoedas[i].cotacao;
        criptomoedas[i].cotacao += criptomoedas[i].cotacao * variacao;

        printf("%s: R$ %.2f -> R$ %.2f (Variação: %.2f%%)\n",
               criptomoedas[i].nome,
               cotacaoAntiga,
               criptomoedas[i].cotacao,
               variacao * 100);
    }
    printf("Cotações atualizadas com sucesso!\n");
}

void salvauser(Usuario usuarios[], int numusers) {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    if (arquivo != NULL) {
        fwrite(usuarios, sizeof(Usuario), numusers, arquivo);
        fclose(arquivo);
        printf("Dados dos usuários salvos com sucesso.\n");
    } else {
        printf("Erro ao salvar os usuários.\n");
    }
}

void abreuser(Usuario usuarios[], int *numusers) {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo != NULL) {
        *numusers = fread(usuarios, sizeof(Usuario), MAX_USUARIOS, arquivo);
        fclose(arquivo);
        printf("Dados dos usuários carregados com sucesso. Total de usuários: %d\n", *numusers);
    } else {
        *numusers = 0;
        printf("Nenhum usuário cadastrado ainda.\n");
    }
}

void abrecriptos(Criptomoeda criptomoedas[], int *nummoedas) {
    FILE *arquivo = fopen("criptomoedas.bin", "rb");
    if (arquivo != NULL) {
        *nummoedas = fread(criptomoedas, sizeof(Criptomoeda), MAX_CRIPTOMOEDAS, arquivo);
        fclose(arquivo);
    } else {
        strcpy(criptomoedas[0].nome, "Bitcoin");
        criptomoedas[0].cotacao = 200.0;
        criptomoedas[0].taxaCompra = 2.0; 
        criptomoedas[0].taxaVenda = 2.0;

        strcpy(criptomoedas[1].nome, "Ethereum");
        criptomoedas[1].cotacao = 100.0;
        criptomoedas[1].taxaCompra = 1.5;
        criptomoedas[1].taxaVenda = 1.5;

        strcpy(criptomoedas[2].nome, "Ripple");
        criptomoedas[2].cotacao = 50.0;
        criptomoedas[2].taxaCompra = 1.0;
        criptomoedas[2].taxaVenda = 1.0;

        *nummoedas = 3;
        salvacriptos(criptomoedas, *nummoedas);
    }
}

void salvacriptos(Criptomoeda criptomoedas[], int nummoedas) {
    FILE *arquivo = fopen("criptomoedas.bin", "wb");
    if (arquivo != NULL) {
        fwrite(criptomoedas, sizeof(Criptomoeda), nummoedas, arquivo);
        fclose(arquivo);
        printf("Criptomoedas salvas com sucesso.\n");
    } else {
        printf("Erro ao salvar as criptomoedas.\n");
    }
}

void compracripto(Usuario *usuario, Criptomoeda criptomoedas[], int nummoedas) {
    if (nummoedas == 0) {
        printf("Não há criptomoedas disponíveis para compra.\n");
        return;
    }

    printf("=== Criptomoedas Disponíveis ===\n");
    for (int i = 0; i < nummoedas; i++) {
        printf("%d. Nome: %s | Cotação: %.2f | Taxa de Compra: %.2f%%\n",
               i + 1, criptomoedas[i].nome, criptomoedas[i].cotacao, criptomoedas[i].taxaCompra);
    }

    int escolha;
    printf("Escolha uma criptomoeda para comprar (1-%d): ", nummoedas);
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > nummoedas) {
        printf("Opção inválida.\n");
        return;
    }

    Criptomoeda escolhida = criptomoedas[escolha - 1];
    float valorCompra;
    printf("Digite o valor em Reais para comprar %s: ", escolhida.nome);
    scanf("%f", &valorCompra);

    float taxa = calctax(valorCompra, escolhida.taxaCompra / 100.0);
    float total = valorCompra + taxa;

    if (usuario->saldoreal < total) {
        printf("Saldo insuficiente! Você precisa de R$ %.2f (incluindo taxa de R$ %.2f).\n", total, taxa);
        return;
    }

    usuario->saldoreal -= total;
    salvatrans(usuario, "Compra de Criptomoeda", valorCompra, taxa);
    printf("Compra de %s realizada com sucesso! Total gasto: R$ %.2f (incluindo taxa de R$ %.2f).\n", escolhida.nome, total, taxa);
}

// Função para vender criptomoedas
void vendacripto(Usuario *usuario, Criptomoeda criptomoedas[], int nummoedas) {
    if (nummoedas == 0) {
        printf("Não há criptomoedas disponíveis para venda.\n");
        return;
    }

    printf("=== Criptomoedas Disponíveis ===\n");
    for (int i = 0; i < nummoedas; i++) {
        printf("%d. Nome: %s | Cotação: %.2f | Taxa de Venda: %.2f%%\n",
               i + 1, criptomoedas[i].nome, criptomoedas[i].cotacao, criptomoedas[i].taxaVenda);
    }

    int escolha;
    printf("Escolha uma criptomoeda para vender (1-%d): ", nummoedas);
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > nummoedas) {
        printf("Opção inválida.\n");
        return;
    }

    Criptomoeda escolhida = criptomoedas[escolha - 1];
    float quantidade;
    printf("Digite a quantidade de %s para vender: ", escolhida.nome);
    scanf("%f", &quantidade);

    float taxa = calctax(quantidade * escolhida.cotacao, escolhida.taxaVenda / 100.0);
    float valorRecebido = (quantidade * escolhida.cotacao) - taxa;

    if (strcmp(escolhida.nome, "Bitcoin") == 0) {
        if (usuario->saldobit < quantidade) {
            printf("Saldo insuficiente de Bitcoin!\n");
            return;
        }
        usuario->saldobit -= quantidade;
    } else if (strcmp(escolhida.nome, "Ethereum") == 0) {
        if (usuario->saldoeth < quantidade) {
            printf("Saldo insuficiente de Ethereum!\n");
            return;
        }
        usuario->saldoeth -= quantidade;
    } else if (strcmp(escolhida.nome, "Ripple") == 0) {
        if (usuario->saldoxrp < quantidade) {
            printf("Saldo insuficiente de Ripple!\n");
            return;
        }
        usuario->saldoxrp -= quantidade;
    } else {
        printf("Saldo insuficiente de %s (moeda não gerenciada diretamente).\n", escolhida.nome);
        return;
    }

    usuario->saldoreal += valorRecebido;
    salvatrans(usuario, "Venda de Criptomoeda", quantidade * escolhida.cotacao, taxa);
    printf("Venda de %s realizada com sucesso! Valor recebido: R$ %.2f (taxa: R$ %.2f).\n", escolhida.nome, valorRecebido, taxa);
}

float calctax(float valor, float taxa) {
    return valor * taxa;
}

void salvatrans(Usuario *usuario, const char *tipomov, float valor, float taxa) {
    if (usuario->quanttrans < MAX_TRANSACOES) {
        Transacao transacatual;
        hora(transacatual.date);
        strcpy(transacatual.tipomov, tipomov);
        transacatual.valor = valor;
        transacatual.taxamov = taxa;

        usuario->transacoes[usuario->quanttrans] = transacatual;
        usuario->quanttrans++;
    }
}

void salvaextrato(Usuario *usuario) {
    char nomeuser[TAM_NOME + 4];
    sprintf(nomeuser, "%s.txt", usuario->nome);
    FILE *arquivo = fopen(nomeuser, "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "Extrato de Transações de %s:\n", usuario->nome);
        for (int i = 0; i < usuario->quanttrans; i++) {
            fprintf(arquivo, "Data: %s | Tipo: %s | Valor: R$ %.2f | Taxa: R$ %.2f\n",
                    usuario->transacoes[i].date,
                    usuario->transacoes[i].tipomov,
                    usuario->transacoes[i].valor,
                    usuario->transacoes[i].taxamov);
        }
        fclose(arquivo);
        printf("Extrato salvo em %s.\n", nomeuser);
    }
}

void hora(char *date) {
    time_t agora = time(NULL);
    strftime(date, 30, "%Y-%m-%d %H:%M:%S", localtime(&agora));
}
