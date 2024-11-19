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