#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

#include "../Headers/structs.h"

// Fun��o para calcular a quantidade de dias em um m�s
int dias_no_mes(int mes, int ano) {
     // Implementa��o do c�lculo dos dias em um m�s, considerando anos bissextos
    switch (mes) {
        case 2:
            return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            // Retorna o n�mero de dias no m�s informado
            return 30;
        default:
            // Retorna o n�mero de dias no m�s informado
            return 31;
    }
}

// Fun��o para verificar se uma data � v�lida
int data_valida(int dia, int mes, int ano) {
    // Verifica se a data � v�lida, considerando o n�mero de dias em cada m�s
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1 || dia > dias_no_mes(mes, ano)) {
        return 0;
    }
    return 1;
}

// Fun��o para calcular a diferen�a em dias entre duas datas
int conferir_dias(dr *retirada, dr *entrega) {
    int day_diff, mon_diff, year_diff;

    // Solicita a entrada de datas de retirada e entrega
    do {
        printf("Digite a data de retirada [DD/MM/AAAA]: ");
        scanf("%d/%d/%d", &retirada->dia, &retirada->mes, &retirada->ano);
        if (!data_valida(retirada->dia, retirada->mes, retirada->ano)) {
            printf("Data inv�lida!\n");
        }
    } while (!data_valida(retirada->dia, retirada->mes, retirada->ano));

    do {
        printf("Digite a data de entrega [DD/MM/AAAA]: ");
        scanf("%d/%d/%d", &entrega->dia, &entrega->mes, &entrega->ano);
        if (!data_valida(entrega->dia, entrega->mes, entrega->ano)) {
            printf("Data inv�lida!\n");
        }
    } while (!data_valida(entrega->dia, entrega->mes, entrega->ano));

    dr original_entrega = *entrega;

    // Realiza o c�lculo da diferen�a em dias entre as duas datas
    if (entrega->dia < retirada->dia) {
        entrega->dia += dias_no_mes(entrega->mes, entrega->ano);
        entrega->mes -= 1;
    }

    if (entrega->mes < retirada->mes) {
        entrega->mes += 12;
        entrega->ano -= 1;
    }

    day_diff = entrega->dia - retirada->dia;
    mon_diff = entrega->mes - retirada->mes;
    year_diff = entrega->ano - retirada->ano;

    *entrega = original_entrega;

    int daytotal = day_diff + (30 * mon_diff) + (365 * year_diff);

    return daytotal;
}

// Fun��o para calcular a quantidade de dias de juros em uma loca��o
int dias_juros(dr retir, dr entr){
    fflush(stdin);
    int daytotal,save_month,save_day,save_year;

    int day_diff, mon_diff, year_diff,var=0;

    save_day=entr.dia;
    save_month=entr.mes;
    save_year=entr.ano;

    // Receber e validar as datas digitadas pelo usu�rio
    while((!data_valida(retir.dia, retir.mes, retir.ano))||(!data_valida(save_day, save_month, save_year))){
        if(!data_valida(retir.dia, retir.mes, retir.ano)){
            printf("A data � inv�lida.\n");
        }
        if(!data_valida(save_day, save_month, save_year)){
            printf("A data � inv�lida\n");
        }

        printf("\nDigite a data de entrega [DD/MM/AAAA]: ");
        scanf("%d/%d/%d", &entr.dia, &entr.mes, &entr.ano);

        save_day=entr.dia;
        save_month=entr.mes;
        save_year=entr.ano;
    }

    // Corrige as datas de entrega de acordo com o m�s
    if(entr.dia < retir.dia){
        if (entr.mes == 3){
            if ((entr.ano % 4 == 0 && entr.ano % 100 != 0) || (entr.ano % 400 == 0)){
                entr.dia += 29;
            } else{
                entr.dia += 28;
            }
        } else if (entr.mes == 5 || entr.mes == 7 || entr.mes == 10 || entr.mes == 12){
           entr.dia += 30;
        } else{
           entr.dia += 31;
        }
        entr.mes = entr.mes - 1;
    }

    if (entr.mes < retir.mes){
        entr.mes += 12;
        entr.ano -= 1;
    }

    // Realiza o c�lculo da diferen�a em dias entre as duas datas, considerando poss�veis corre��es
    day_diff = entr.dia - retir.dia;
    mon_diff = entr.mes - retir.mes;
    year_diff = entr.ano - retir.ano;
    entr.mes=save_month;
    entr.dia=save_day;
    entr.ano=save_year;
    daytotal=day_diff+(30*mon_diff)+(365*year_diff)+var;

    return daytotal;
}
