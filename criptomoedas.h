#ifndef CRIPTOMOEDAS_H
#define CRIPTOMOEDAS_H

#define MAX_CRIPTOMOEDAS 100

typedef struct {
    char nome[50];
    float cotacao;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;


void abrecriptos(Criptomoeda criptomoedas[], int *nummoedas);
void salvacriptos(Criptomoeda criptomoedas[], int nummoedas);

#endif
