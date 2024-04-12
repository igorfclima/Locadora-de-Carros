#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

#include "../Headers/structs.h"
#include "../Headers/clientes.h"

// Procedimento para atribuir o rank do cliente com base nos pontos de fidelidade
void rank_cliente(cliente *c) {
    if (c->ponto_Fidelidade < 500) {
        strcpy(c->rank, "Loca");
    } else if (c->ponto_Fidelidade >= 500 && c->ponto_Fidelidade <= 1000) {
        strcpy(c->rank, "Loca+");
    } else{
        strcpy(c->rank, "Loca++");
    }
}

// Fun��o para encontrar a posi��o de um cliente no arquivo
int achar_cliente(FILE *arqCliente,int codigoC){
    fflush(stdin);
    int posicao=-1, achou=0;
    cliente c;
    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c), 1, arqCliente);

    // Procura o cliente no arquivo
    while(!feof(arqCliente) && !achou){
         posicao++;
        if (c.codigoC==codigoC){
            achou=1;
        }
        fread(&c, sizeof(c),1, arqCliente);
    }

    if(achou){
        return posicao;
    } else{
        return -1;
    }
}

// Procedimento para cadastrar um novo cliente
void cadastrar_cliente(FILE *arqCliente) {
    fflush(stdin);
    cliente c;
    int posicao;

    // Verifica se o arquivo n�o est� vazio para atribuir um novo c�digo ao cliente
    fseek(arqCliente, 0, SEEK_END);
    if (ftell(arqCliente) > 0) {
        fseek(arqCliente, -sizeof(cliente), SEEK_END);
        fread(&c, sizeof(cliente), 1, arqCliente);
        c.codigoC++;
    } else {
        c.codigoC = 1;
    }

    posicao = achar_cliente(arqCliente, c.codigoC);

    printf("Nome: ");
    fflush(stdin);
    gets(c.nome);

    printf("Telefone: ");
    fflush(stdin);
    gets(c.telefone);

    printf("Rua: ");
    fflush(stdin);
    gets(c.endereco.rua);

    printf("Bairro: ");
    fflush(stdin);
    gets(c.endereco.bairro);

    printf("Numero: ");
    scanf("%i", &c.endereco.num);

    printf("Cep: ");
    fflush(stdin);
    gets(c.endereco.cep);

    printf("Cidade: ");
    fflush(stdin);
    gets(c.endereco.cidade);

    printf("Estado: ");
    fflush(stdin);
    gets(c.endereco.estado);

    c.ponto_Fidelidade = 0;

    // Adiciona o cliente no final do arquivo
    fseek(arqCliente, 0, SEEK_END);
    fwrite(&c, sizeof(c), 1, arqCliente);
    fflush(arqCliente);

    printf("\nCliente cadastrado com sucesso!\nC�digo: %i", c.codigoC);

    printf("\n\n");
    system("pause");
}

// Procedimento para exibir informa��es de um cliente
void informacoes_cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int posicao, codDigitado;
    printf("Digite o c�digo do cliente que deseja procurar: ");
    fflush(stdin);
    scanf("%3i", &codDigitado);
    posicao = achar_cliente(arqCliente, codDigitado);

    // L� o arquivo de clientes
    if (posicao != -1){
        fseek(arqCliente, 0, SEEK_SET);
        fread(&c, sizeof(c), 1, arqCliente);

        // Percorre o arquivo at� encontrar o cliente desejado
        while(!feof(arqCliente)){
            if(codDigitado == c.codigoC){
                printf("\nNome: %s \n", c.nome);
                printf("Telefone: %s\n", c.telefone);
                printf("Rua: %s\n", c.endereco.rua);
                printf("Bairro: %s\n", c.endereco.bairro);
                printf("N�: %i\n", c.endereco.num);
                printf("CEP: %s\n", c.endereco.cep);
                printf("Cidade: %s\n", c.endereco.cidade);
                printf("Estado: %s\n", c.endereco.estado);

                // atribui rank ao cliente
                rank_cliente(&c);

                printf("\nRank: %s\n", c.rank);
                printf("Pontos Fidelidade: %i\n", c.ponto_Fidelidade);

                if(c.ponto_Fidelidade >= 500){
                    printf("O cliente � eleg�vel para o KIT LocaMais!\n");
                }

                // Salvar as altera��es no arquivo
                fseek(arqCliente, posicao * sizeof(c), SEEK_SET);
                fwrite(&c, sizeof(c), 1, arqCliente);
                fflush(arqCliente);
            }
            fread(&c, sizeof(c), 1, arqCliente);
        }
    } else{
        printf("\nC�digo do cliente n�o encontrado\n");
    }

    printf("\n");
    system("pause");
}

// Procedimento para exibir loca��es de um cliente
void locacoes_cliente(FILE *arqLocacao, FILE *arqCliente){
    fflush(stdin);
    locacao l;
    int posicao, codDigitado, achou = 0;
    printf("Digite o c�digo do cliente para procurar suas loca��es: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=achar_cliente(arqCliente, codDigitado);

    // L� as loca��es do cliente
    if (posicao != -1){
        fseek(arqLocacao,0,SEEK_SET);
        fread(&l, sizeof(l),1,arqLocacao);

        // Imprime as loca��es do cliente
        while(!feof (arqLocacao) ){
            if(codDigitado == l.cod_cliente){
                achou = 1;
                printf("\nLoca��o c�digo: %llu \n",l.codigo);
                printf("Dias de locacao: %d \n",l.qnt_dias);
                printf("Data da retirada: %d/%d/%d\n",l.retirada.dia,l.retirada.mes,l.retirada.ano);
                printf("Data da entrega: %d/%d/%d\n",l.entrega.dia,l.entrega.mes,l.entrega.ano);
                printf("Seguro? %s\n",l.seguro);
                printf("C�digo do veiculo: %d\n",l.cod_veiculo);
                printf("Concluida? %s\n",l.baixa);
                printf("\n\n");
            }
            fread(&l, sizeof(l),1, arqLocacao);
        }
        if(achou == 0){
            printf("\nN�o foi encontrada nenhuma loca��o no nome do cliente!\n");
        }
    } else{
        printf("\nC�digo do cliente n�o encontrado\n");
    }

    printf("\n");
    system("pause");
}

// Procedimento para listar clientes com direito a um kit LocaMais
void kit_locaMais(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int achou = 0;

    // L� o arquivo de loca��es
    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c),1, arqCliente);

    printf("Clientes com direito � um kit LocaMais:\n");

    // Imprime os clientes que possuem 500 ou mais pontos
    while (!feof(arqCliente)){
        if(c.ponto_Fidelidade>=500){
            printf("\nC�digo: %d \n",c.codigoC);
            printf("Nome: %s \n",c.nome);
            printf("Telefone: %s\n",c.telefone);
            printf("\nPontos Fidelidade: %i\n",c.ponto_Fidelidade);
            achou = 1;
        }
        fread(&c, sizeof(c),1, arqCliente);
    }
    if(achou == 0){
        printf("\nNenhum cliente tem pontos de fidelidade suficiente!\n");
    }
    printf("\n");
    system("pause");
}
