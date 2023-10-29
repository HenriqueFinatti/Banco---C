#include "biblioteca.h" //Duas bibliotecas de funções incluidas
#include "Biblioteca_auxiliar.h"
#include <stdio.h>
#include <string.h>

lista_de_clientes usuarios;

void novo_cliente(int tamanho, Cliente *clientes) {//Função de cadastrar clientes
    char temp[20];
    int aux, valido = 0;
    printf("Insira as informacoes a seguir.\n");

    printf("Nome: "); scanf("%100[^\n]s", clientes[tamanho].nome);//Recebe o nome do cliente
    limpa();

    do{// Função do while para pedir CPF até que seja válido

        printf("CPF: "); scanf("%15[^\n]s",temp);
        aux = verificaCPF(tamanho, clientes, temp);//Verifica o CPF
        limpa();

        if(aux != -1){//Caso o CPF seja inválido
            printf("CPF ja existente, por favor insira um CPF diferente\n");
        }
        else{
            //Caso o CPF seja válido o cpf do cliente é inserido na struct a condição de parada do 'do while' é ativa
            strcpy(clientes[tamanho].cpf, temp);
            valido = 1;
        }
    } while(!valido);

    valido = 0;

    do {// Outro 'Do while' para o tipo de conta
        char temp2[20];
        printf("Tipo de Conta: (comum ou plus)"); scanf("%10s", temp2);//É pedido o tipo de conta
        limpa();

        arruma_tipo(tamanho, temp2, clientes);//Função que arruma o tipo de conta (Explicada naestrutura da função)

        if (!strcmp(temp2, "comum") || !strcmp(temp2, "plus"))// verifica caso o tipo não tenha sido bem inserido
        {
            strcpy(clientes[tamanho].tipo, temp2);
            valido = 1; //condição de para do 'do while' ativa
        }
        else
        {
            //Condição caso o tipo da conta não tenha sido bem inserida
            printf("Tipo de conta invalido: %s. Digite 'comum' ou 'plus'.\n", temp2);
        }
    } while (!valido);

    printf("Saldo inicial: ");//É pedido o saldo inicial da conta
    scanf("%lf", &clientes[tamanho].saldo);
    limpa();

    printf("Senha: ");// É pedido a senha da conta
    scanf("%10[^\n]s", clientes[tamanho].senha);
    limpa();
}
