#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100
#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_SENHA 7


typedef struct {
    float valorbit;
    float valoreht;
    float valorxrp;
} Cotacoes;

typedef struct {
    char date[30];
    char tipomov[30];
    float valor;
    float taxamov;
} Transacao;

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
                        // deposito(&useratual);
                        // salvauser(usuarios, numusers);
                    } else if (respuser == 2) {
                        // compracripto(&useratual, &cotacoes);
                        // salvauser(usuarios, numusers); 
                    } else if (respuser == 3) {
                        // vendacripto(&useratual, &cotacoes);
                        // salvauser(usuarios, numusers); 
                    } else if (respuser == 4) {
                        // extrato(&useratual);
                    } else if (respuser == 5) {
                        // saque(&useratual);
                        // salvauser(usuarios, numusers);
                    } else if (respuser == 6) {
                        // saldo(&useratual);
                    } else if (respuser == 7) {
                        // cotacao(&cotacoes);
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