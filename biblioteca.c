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

void apagar_cliente(int *tam, Cliente *clientes) { //Função de apagar clientes
    int indice;

    printf("Insira o numero do cliente que deseja apagar: "); scanf("%d", &indice);
    //É pedido o número do cliente

    if (indice >= 1 && indice <= *tam)//Verifica se o numero do cliente existe
    {
        for (int i = indice - 1; i < *tam - 1; i++) {
            usuarios.clientes[i] = usuarios.clientes[i + 1];//Alteração de todos os clientes para posição anterior
        }
        (*tam)--;//Reduz o numero de clientes
        printf("Cliente de numero %d apagado com sucesso.\n", indice);
    }
    else
    {   //Condição caso o numero do cliente não exista
        printf("Numero invalido.\n");
    }
}

void listar_clientes(int tam, Cliente *clientes){//Função de listar clientes

    for(int i = 0; i < tam; i++)
    {
        // Lista cada informação de todos os clientes por ordem de criação de conta
        printf("Cliente %d\n", i+1);
        printf("Nome: %s\n",clientes[i].nome);
        printf("Saldo: %.2lf\n",clientes[i].saldo);
        printf("Senha: %s\n",clientes[i].senha);
        printf("CPF: %s\n",clientes[i].cpf);
        printf("Tipo de Conta: %s\n\n", clientes[i].tipo);
    }
}

void debito(int tam, Cliente *clientes) {//Função de débito
    char cpf[20], senha[20];
    int aux, aux2, valor, confirma = 0, indice;

    printf("Insira o seu CPF: "); scanf("%20[^\n]s", cpf);// É pedido o CPF

    indice = verificaCPF(tam, clientes, cpf);//Aqui verifico o CPF e recebo indice dele

    if (indice == -1)
    {
        //Condição caso o CPF não exista
        printf("CPF nao encontrado.\n");
    }
    else
    {
        do// Função 'Do while' para pedir a senha
        {
            limpa();

            printf("Insira a sua senha: "); scanf("%20[^\n]s", senha);//Peço a senha
            aux = verificaSenha(tam, clientes, senha);//verifico se a senha está correta

            if (aux)
            {
                //Caso seja correta o do while quebra
                confirma = 1;
                aux2 = 1;
            }
            else
            {
                //Caso seja inválida é perguntado se o cliente quer tentar novamente ou sair da função
                printf("Senha invalida. (1 - sair / 0 - tentar novamente)\n");
                scanf("%d", &confirma);
            }
        } while (confirma != 1);

        if (aux2)
        {
            //Caso a senha seja correta é requisitado o valor de débito
            printf("Insira o valor que deseja debitar da sua conta: ");
            scanf("%d", &valor);

            if (valor > 0)//Verifica se o valor é valido
            {
                double taxa;
                int tipo;

                taxa = aplica_taxa(indice, clientes, valor);//Aplica a taxa de acordo com o tipo da conta
                tipo = confere_tipo(indice, clientes);// Verifica o tipo da conta
                //Ambas as funções explicadas na estrutura da função

                if(tipo)//Caso o tipo seja da conta seja Plus
                {
                    if (clientes[indice].saldo - valor - taxa >= -5000.0)//Verifica o limite de saldo negativo
                    {
                        clientes[indice].saldo -= (valor + taxa);//Descontado o valor da conta
                        strcpy(clientes[indice].historico[clientes[indice].num_transacoes].descricao, "Debito");// Aqui estamos a descricao "Débtio" para a categoria descricao da struct de extrato
                        clientes[indice].historico[clientes[indice].num_transacoes].valor = valor;//Registrado o valor da transacao
                        clientes[indice].historico[clientes[indice].num_transacoes].taxa = taxa; //Registrado a taxa da transacao
                        clientes[indice].num_transacoes++; //Numero de transações alterado

                        printf("Debito de %d realizado com sucesso. Taxa cobrada de: %.2lf. Novo saldo: %.2lf\n", valor, taxa, clientes[indice].saldo);
                        //Confirmação do valor do valor removido, taxa cobrada e o saldo atual
                    }
                    else
                    {
                        //Caso o saldo seja insuficiente
                        printf("Saldo insuficiente ou limite de saldo negativo excedido.\n");
                    }
                }
                else//Caso o tipo da conta seja comum
                {
                    if (clientes[indice].saldo - valor - taxa >= -1000.0)//Verifica o limite de saldo negativo
                    {
                        clientes[indice].saldo -= (valor + taxa);//Descontado o valor da conta
                        strcpy(clientes[indice].historico[clientes[indice].num_transacoes].descricao, "Debito");// Aqui estamos a descricao "Débtio" para a categoria descricao da struct de extrato
                        clientes[indice].historico[clientes[indice].num_transacoes].valor = valor;// Registrado o valor da transacao
                        clientes[indice].historico[clientes[indice].num_transacoes].taxa = taxa; //Registrado a taxa da transacao
                        clientes[indice].num_transacoes++;

                        printf("Debito de %d realizado com sucesso. Taxa cobrada de: %.2lf. Novo saldo: %.2lf\n", valor, taxa, clientes[indice].saldo);
                        //Confirmação do valor removido, taxa cobrado e saldo atual
                    }
                    else
                    {
                        //Caso o saldo seja insuficiente
                        printf("Saldo insuficiente ou limite de saldo negativo excedido.\n");
                    }
                }
            }
            else
            {
                //Caso o valor inserido seja inválido
                printf("O valor do debito deve ser maior que zero.\n");
            }
        }
    }
}