#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

// Estrutura para armazenar informa��es de endere�o
struct Tender{
    char rua[50], bairro[30], cidade[50], estado[50], cep[15];
    int num;
};
typedef struct Tender ender;

// Estrutura para armazenar informa��es do cliente
struct Tcliente{
    int codigoC, ponto_Fidelidade;
    char nome[30], telefone[18];
    ender endereco;
    char rank[10];
};
typedef struct Tcliente cliente;

// Estrutura para armazenar informa��es do ve�culo
struct Tveiculo{
    int codigoV;
    char descricao[100];
    char modelo[50];
    char cor[10];
    char placa[8];
    float valor_diaria;
    int qtd_ocupante;
    char status[20];
};
typedef struct Tveiculo veiculo;

// Estrutura para armazenar informa��es de data (dia, m�s, ano)
struct data_retent{
    int dia;
    int mes;
    int ano;
};
typedef struct data_retent dr;

// Estrutura para armazenar informa��es de loca��o
struct Tlocacao{
    unsigned long long int codigo;
    int qnt_dias;
    dr retirada;
    dr entrega;
    char seguro[4];
    int cod_cliente;
    int cod_veiculo;
    char baixa[4];
};
typedef struct Tlocacao locacao;

#endif // STRUCTS_H_INCLUDED
