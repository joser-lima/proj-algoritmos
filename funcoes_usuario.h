#ifndef FUNCOES_USUARIO_H
#define FUNCOES_USUARIO_H

#include "criptomoedas.h"

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100
#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_SENHA 7

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
void saque(Usuario *usuario);
void deposito(Usuario *usuario);
void compracripto(Usuario *usuario, Criptomoeda criptomoedas[], int nummoedas);
void vendacripto(Usuario *usuario, Criptomoeda criptomoedas[], int nummoedas); 
void extrato(Usuario *usuario);
void saldo(Usuario *usuario);
void salvauser(Usuario usuarios[], int numusers);
void abreuser(Usuario usuarios[], int *numusers);
void salvatrans(Usuario *usuario, const char *tipomov, float valor, float taxa);
void cotacao(Criptomoeda criptomoedas[], int nummoedas);
void salvaextrato(Usuario *usuario);
float calctax(float valor, float taxa);
void hora(char *date);

#endif
