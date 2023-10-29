#ifndef BANCO___C_BIBLIOTECA_H
#define BANCO___C_BIBLIOTECA_H

typedef struct {
    char origem[20];
    char destino[20];
    double valor;
    double taxa;
    char descricao[50];

}Operacoes;

typedef struct {
    char nome[100];
    double saldo;
    char tipo[10];
    char cpf[20];
    char senha[10];
    Operacoes historico[100];
    int num_transacoes;

}Cliente;

typedef struct{
    Cliente clientes[1000];
    int tamanho;
} lista_de_clientes;

void novo_cliente(int tamanho, Cliente *clientes);

#endif //BANCO___C_BIBLIOTECA_H
