#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

#include "../Headers/structs.h"
#include "../Headers/clientes.h"
#include "../Headers/veiculos.h"

// Fun��o para localizar a posi��o de um ve�culo no arquivo
int localiza_veiculo(FILE *arqVeiculo,int codigoV){
    fflush(stdin);
    int posicao=-1,achou=0;
    veiculo v;

    // L� o arquivo de ve�culos
    fseek(arqVeiculo,0,SEEK_SET);
    fread(&v, sizeof(v), 1, arqVeiculo);

    // Confere se o ve�culo est� no arquivo
    while(!feof(arqVeiculo) && !achou){
         posicao++;
        if (v.codigoV==codigoV){
            achou=1;
        }
        fread(&v, sizeof(v),1, arqVeiculo);
    }

    if(achou){
        return posicao;
    } else{
        return -1;
    }
}

// Procedimento para cadastrar um novo ve�culo
void cadastrar_veiculo(FILE *arqVeiculo) {
    fflush(stdin);
    veiculo v;
    int posicao;

    // Verifica se o arquivo n�o est� vazio para atribuir um novo c�digo ao veiculo
    fseek(arqVeiculo, 0, SEEK_END);
    if (ftell(arqVeiculo) > 0) {
        fseek(arqVeiculo, -sizeof(veiculo), SEEK_END);
        fread(&v, sizeof(veiculo), 1, arqVeiculo);
        v.codigoV++;
    } else {
        v.codigoV = 1;
    }

    posicao = localiza_veiculo(arqVeiculo, v.codigoV);

    printf("Descricao do veiculo: ");
    fflush(stdin);
    gets(v.descricao);

    printf("Modelo do ve�culo: ");
    fflush(stdin);
    gets(v.modelo);

    printf("Cor do ve�culo: ");
    fflush(stdin);
    gets(v.cor);

    printf("Placa: ");
    fflush(stdin);
    gets(v.placa);

    v.qtd_ocupante = -1;
    do {
        printf("Quantidade de ocupantes: ");
        fflush(stdin);
        scanf("%i", &v.qtd_ocupante);
    } while ((v.qtd_ocupante <= 0) || (v.qtd_ocupante >= 15));

    strcpy(v.status, "disponivel"); // atualiza status do ve�culo

    printf("Pre�o da di�ria: ");
    fflush(stdin);
    scanf("%f", &v.valor_diaria);

    // Salva as informa��es no arquivo de ve�culos
    fseek(arqVeiculo, 0, SEEK_END);
    fwrite(&v, sizeof(v), 1, arqVeiculo);
    fflush(arqVeiculo);

    printf("\nVe�culo cadastrado com sucesso!\nC�digo: %i", v.codigoV);

    printf("\n\n");
    system("pause");
}

// Procedimento para exibir informa��es de um ve�culo
void informacoes_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    int posicao, codDigitado;
    printf("Digite o c�digo do veiculo que deseja procurar: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_veiculo(arqVeiculo, codDigitado);

    // L� o arquivo de ve�culos
    if (posicao != -1){
        fseek(arqVeiculo,0,SEEK_SET);
        fread(&v, sizeof(v),1,arqVeiculo);

        // Imprime informa��es sobre o ve�culo
        while(!feof (arqVeiculo) ){
            if(codDigitado == v.codigoV){
                printf("\nModelo: %s\n",v.modelo);
                printf("Descri��o: %s \n",v.descricao);
                printf("Cor: %s\n",v.cor);
                printf("Placa: %s\n",v.placa);
                printf("Qtd de ocupantes: %i\n",v.qtd_ocupante);
                printf("Status: %s\n",v.status);
                printf("Valor di�ria: %.2f\n",v.valor_diaria);
            }
            fread(&v, sizeof(v),1, arqVeiculo);
        }
    } else{
        printf("\nC�digo do ve�culo n�o encontrado\n");
    }

    printf("\n");
    system("pause");
}
