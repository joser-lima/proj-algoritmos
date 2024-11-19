#ifndef FUNCOES_ADMIN_H
#define FUNCOES_ADMIN_H

#include "funcoes_usuario.h"

void adicionarUsuario(Usuario usuarios[], int *numusers);
void excluirUsuario(Usuario usuarios[], int *numusers);
int loginAdmin();
void cadastrarCripto(Criptomoeda criptomoedas[], int *nummoedas);
void excluirCripto(Criptomoeda criptomoedas[], int *nummoedas);
void consultarSaldo(Usuario usuarios[], int numusers);
void consultarExtrato(Usuario usuarios[], int numusers); 

#endif
