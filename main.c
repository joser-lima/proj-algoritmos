#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100
#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_SENHA 7

//struct das criptomoedas
typedef struct {
    float valorbit;
    float valoreht;
    float valorxrp;
} Cotacoes;

//struct de cada transacao
typedef struct {
    char date[30];
    char tipomov[30];
    float valor;
    float taxamov;
} Transacao;

//struct de cada usuario
typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char senha[TAM_SENHA];
    float saldoreal;
    float saldobit;
    float saldoeth;
    float saldoxrp;
    Transacao transacoes[MAX_TRANSACOES];
    int quanttrans;
} Usuario;


void cadastro(Usuario usuarios[], int *numusers);
int login(Usuario usuarios[], int numusers, Usuario *userlogado);
void saque(Usuario *usuario);
void deposito(Usuario *usuario);
void compracripto(Usuario *usuario, Cotacoes *cotacoes);
void vendacripto(Usuario *usuario, Cotacoes *cotacoes);
void cotacao(Cotacoes *cotacoes);
void saldo(Usuario *usuario);
void extrato(Usuario *usuario);
void salvaextrato(Usuario *usuario);
float calctax(float valor, float taxa);
void hora(char *date);
void salvauser(Usuario usuarios[], int numusers);
void abreuser(Usuario usuarios[], int *numusers);
void salvatrans(Usuario *usuario, const char *tipomov, float valor, float taxa);

float variacao() {
    return (rand() % 11 - 5) / 100.0;
}


int main() {
    Usuario usuarios[MAX_USUARIOS];
    int numusers = 0;
    Usuario useratual;
    Cotacoes cotacoes = {200.0, 100.0, 50.0}; 
    int opcaouser;

    srand(time(NULL));
    abreuser(usuarios, &numusers);

    while (1) {
        printf("\n1. Cadastrar\n2. Login\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcaouser);

        if (opcaouser == 1) {
            cadastro(usuarios, &numusers);
        } else if (opcaouser == 2) {
            if (login(usuarios, numusers, &useratual)) {
                int respuser;
                while (1) {
                    printf(" /$$$$$$$  /$$$$$$ /$$$$$$$$ /$$$$$$$  /$$   /$$ /$$     /$$ \n");
                    printf("| $$__  $$|_  $$_/|__  $$__/| $$__  $$| $$  | $$|  $$   /$$/\n");
                    printf("| $$  \\ $$  | $$     | $$   | $$  \\ $$| $$  | $$ \\  $$ /$$/ \n");
                    printf("| $$$$$$$   | $$     | $$   | $$$$$$$ | $$  | $$  \\  $$$$/  \n");
                    printf("| $$__  $$  | $$     | $$   | $$__  $$| $$  | $$   \\  $$/   \n");
                    printf("| $$  \\ $$  | $$     | $$   | $$  \\ $$| $$  | $$    | $$    \n");
                    printf("| $$$$$$$/ /$$$$$$   | $$   | $$$$$$$/|  $$$$$$/    | $$    \n");
                    printf("|_______/ |______/   |__/   |_______/  \\______/     |__/    \n");
                    printf("\n1. Depósito\n2. Comprar Criptomoeda\n3. Vender Criptomoeda\n4. Ver Extrato\n5. Sacar\n6. Consultar Saldo\n7. Atualizar Cotação\n8. Sair\nEscolha uma opção: ");
                    scanf("%d", &respuser);

                    if (respuser == 1) {
                        deposito(&useratual);
                        salvauser(usuarios, numusers);
                    } else if (respuser == 2) {
                        compracripto(&useratual, &cotacoes);
                        salvauser(usuarios, numusers); 
                    } else if (respuser == 3) {
                        vendacripto(&useratual, &cotacoes);
                        salvauser(usuarios, numusers); 
                    } else if (respuser == 4) {
                        extrato(&useratual);
                    } else if (respuser == 5) {
                        saque(&useratual);
                        salvauser(usuarios, numusers);
                    } else if (respuser == 6) {
                        saldo(&useratual);
                    } else if (respuser == 7) {
                        cotacao(&cotacoes);
                    } else if (respuser == 8) {
                        break;
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

void compracripto(Usuario *usuario, Cotacoes *cotacoes) {
    int respmoeda;
    float valor;
    printf("\n1. Comprar Bitcoin\n2. Comprar Ethereum\n3. Comprar Ripple\nEscolha uma opção: ");
    scanf("%d", &respmoeda);

    printf("Digite o valor da compra: ");
    scanf("%f", &valor);

    float taxa;
    if (respmoeda == 1) {
        taxa = 0.02;
    } else if (respmoeda == 2) {
        taxa = 0.01;
    } else {
        taxa = 0.01;
    }

    float valortaxa = calctax(valor, taxa);
    if (usuario->saldoreal < valortaxa) {
        printf("Saldo insuficiente para cobrir a taxa!\n");
        return;
    }

    usuario->saldoreal -= valortaxa;

    if (respmoeda == 1) {
        usuario->saldobit += valor / cotacoes->valorbit;
        salvatrans(usuario, "Compra de Bitcoin", valor, valortaxa);
        printf("Compra de Bitcoin realizada! Saldo de BTC: %.6f\n", usuario->saldobit);
    } else if (respmoeda == 2) {
        usuario->saldoeth += valor / cotacoes->valoreht;
        salvatrans(usuario, "Compra de Ethereum", valor, valortaxa);
        printf("Compra de Ethereum realizada! Saldo de ETH: %.6f\n", usuario->saldoeth);
    } else if (respmoeda == 3) {
        usuario->saldoxrp += valor / cotacoes->valorxrp;
        salvatrans(usuario, "Compra de Ripple", valor, valortaxa);
        printf("Compra de Ripple realizada! Saldo de XRP: %.2f\n", usuario->saldoxrp);
    }
}

void vendacripto(Usuario *usuario, Cotacoes *cotacoes) {
    int respmoeda;
    float valor;
    printf("\n1. Vender Bitcoin\n2. Vender Ethereum\n3. Vender Ripple\nEscolha uma opção: ");
    scanf("%d", &respmoeda);

    printf("Digite a quantidade a ser vendida: ");
    scanf("%f", &valor);

    float taxa;
    if (respmoeda == 1) {
        taxa = 0.02;
        if (usuario->saldobit < valor) {
            printf("Saldo insuficiente de BTC!\n");
            return;
        }
        usuario->saldobit -= valor;
        usuario->saldoreal += valor * cotacoes->valorbit * (1 - taxa);
        salvatrans(usuario, "Venda de Bitcoin", valor * cotacoes->valorbit, valor * cotacoes->valorbit * taxa);
        printf("Venda de Bitcoin realizada! Saldo de BTC: %.6f\n", usuario->saldobit);
    } else if (respmoeda == 2) {
        taxa = 0.02;
        if (usuario->saldoeth < valor) {
            printf("Saldo insuficiente de ETH!\n");
            return;
        }
        usuario->saldoeth -= valor;
        usuario->saldoreal += valor * cotacoes->valoreht * (1 - taxa);
        salvatrans(usuario, "Venda de Ethereum", valor * cotacoes->valoreht, valor * cotacoes->valoreht * taxa);
        printf("Venda de Ethereum realizada! Saldo de ETH: %.6f\n", usuario->saldoeth);
    } else if (respmoeda == 3) {
        taxa = 0.01;
        if (usuario->saldoxrp < valor) {
            printf("Saldo insuficiente de XRP!\n");
            return;
        }
        usuario->saldoxrp -= valor;
        usuario->saldoreal += valor * cotacoes->valorxrp * (1 - taxa);
        salvatrans(usuario, "Venda de Ripple", valor * cotacoes->valorxrp, valor * cotacoes->valorxrp * taxa);
        printf("Venda de Ripple realizada! Saldo de XRP: %.2f\n", usuario->saldoxrp);
    }
}

void cotacao(Cotacoes *cotacoes) {
    cotacoes->valorbit += cotacoes->valorbit * variacao();
    cotacoes->valoreht += cotacoes->valoreht * variacao();
    cotacoes->valorxrp += cotacoes->valorxrp * variacao();
    printf("Cotações atualizadas:\n");
    printf("Bitcoin: R$ %.2f\n", cotacoes->valorbit);
    printf("Ethereum: R$ %.2f\n", cotacoes->valoreht);
    printf("Ripple: R$ %.2f\n", cotacoes->valorxrp);
}

void saldo(Usuario *usuario) {
    printf("\nSaldo de %s:\n", usuario->nome);
    printf("Saldo em Reais: R$ %.2f\n", usuario->saldoreal);
    printf("Saldo em Bitcoin: %.6f BTC\n", usuario->saldobit);
    printf("Saldo em Ethereum: %.6f ETH\n", usuario->saldoeth);
    printf("Saldo em Ripple: %.2f XRP\n", usuario->saldoxrp);
}

void extrato(Usuario *usuario) {
    printf("\nExtrato de Transações de %s:\n", usuario->nome);
    for (int i = 0; i < usuario->quanttrans; i++) {
        printf("Data: %s | Tipo: %s | Valor: R$ %.2f | Taxa: R$ %.2f\n",
               usuario->transacoes[i].date,
               usuario->transacoes[i].tipomov,
               usuario->transacoes[i].valor,
               usuario->transacoes[i].taxamov);
    }
    salvaextrato(usuario);
}

void salvaextrato(Usuario *usuario) {
    char nomeuser[TAM_NOME + 4]; // espaço para .txt
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


float calctax(float valor, float taxa) {
    return valor * taxa;
}

void salvauser(Usuario usuarios[], int numusers) {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    fwrite(usuarios, sizeof(Usuario), numusers, arquivo);
    fclose(arquivo);
    printf("Dados dos usuários salvos com sucesso.\n");
}

void abreuser(Usuario usuarios[], int *numusers) {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo != NULL) {
        *numusers = fread(usuarios, sizeof(Usuario), MAX_USUARIOS, arquivo);
        fclose(arquivo);
        printf("Dados dos usuários carregados com sucesso. Total de usuários: %d\n", *numusers);
    }
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

void hora(char *date) {
    time_t agora = time(NULL);
    strftime(date, 30, "%Y-%m-%d %H:%M:%S", localtime(&agora));
}