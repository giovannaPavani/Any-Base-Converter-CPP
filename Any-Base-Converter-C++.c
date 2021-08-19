#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//GIOVANNA PAVANI MARTELLI - 19173
//MARIA LUIZA SPERANCIN MANCEBO - 19186
//VINÍCIUS MARTINS COTRIM - 19040

//DECLARACAO DE FUNCOES
int verificar(char *numero, unsigned int tam, unsigned int baseInicial, unsigned int baseFinal);
float converterParaDec(char *numero, unsigned int tam, unsigned int baseInicial);
void converterInteira(float numero, unsigned int baseFinal, char *ret);
void converterFracao(float numero, unsigned int baseFinal, char *ret);
void converterParaBase(float numero, unsigned int baseFinal, char *numeroPronto);

//DEFINICAO DE FUNCOES
int verificar(char *numero, unsigned int tam, unsigned int baseInicial, unsigned int baseFinal)
{
    int i;

    if(baseInicial > 36 || baseFinal > 36 || baseInicial < 2 || baseFinal < 2) // verifica o tamanho da base
    {
        printf("\nO numero inserido nao esta na base %d! Tente novamente.\n", baseInicial);
	fflush(stdout);
        return -1;
    }

    if(baseInicial <= 10) // se for menor que 10
    {
        for(i = 0; i < tam; i++)
        {
            if((!isdigit(numero[i]) || (numero[i]-'0') >= baseInicial) && numero[i] != ',') // verifica se há dígitos maiores que a base digitiada
            {
                printf("\nO numero inserido nao esta na base %d! Tente novamente.\n", baseInicial);
		fflush(stdout);
                return -1;
            }
        }
    }
    else //base > 10
    {
        for(i = 0; i < tam; i++)
        {
            if(isalpha(numero[i])) // verifica se é letra
            {
                char letra = toupper(numero[i]); // maiuscula
                int num = letra - 55; // converte para o valor numérico na base 10

                if(num >= baseInicial)
                {
                    printf("\nO numero inserido nao esta na base %d! Tente novamente.\n", baseInicial);
		    fflush(stdout);
                    return -1;
                }
                numero[i] = letra; // salva
            }

            if(!isdigit(numero[i]) && !isalpha(numero[i]) && !(numero[i] == ',')) // verifica se n tem caracter especial (apenas número, letra e virgula)
            {
                printf("\nO numero inserido nao esta na base %d! Tente novamente.\n", baseInicial);
		fflush(stdout);
                return -1;
            }
        }
    }

    return 0;
}


float converterParaDec(char *numero, unsigned int tam, unsigned int baseInicial)
{
    int i, f = tam-1, num;
    float dec = 0;

    if(numero[tam-1] == ',') // se escrever '345,', por exemplo
        numero[tam-1] = '\000'; // necerra a string

    for(i=0; i< tam; i++)
        if(numero[i] == ',')
            f = tam-strlen(strchr(numero, ','))-1; // pega exponente (tamanho da parte inteira -1)

    for(i = 0; // f = o tamanho da parte inteira
        i < tam;
        i++, f--)
    {
        if(numero[i] == ',') // se for vírgula, essa casa é pulada
            i++;

        if(!isdigit(numero[i]))
            num = ((int)numero[i]) - 55; // converte em numero se for letra (valor maior que 9)
        else
            num = numero[i]-'0'; // tranforma em int

        dec = dec + (num * pow(baseInicial, f)); // soma o resultado de cada casa
    }

    return dec;
}

void converterInteira(float numero, unsigned int baseFinal, char *ret)
{
    int i = 0, x = numero, resto, quociente;
    char numeroChar[100], parte[100], num;

    do // vai dividindo o número pela base
    {
        resto = x % baseFinal;
        quociente = (x - resto) / baseFinal;

        if(resto > 9) // deu alguma letra
            num = (55 + resto);
        else // número < 10 --> apenas converte para char
            num = resto+'0';

        ret[i] = num; // guarda valor
        x = quociente; // atualiza
        i = i+1; // i++
    }
    while(quociente != 0);

    strrev(ret); // inverte o vetor
}

void converterFracao(float numero, unsigned int baseFinal, char *ret)
{
    int i = 0, num, x;
    float fracionaria = numero - (int)numero; // pega parte fracionaria
    char valor;

    while(x != 0 && i<11) // tamanho max da parte fracionaria=10
    {
        float aux = fracionaria * baseFinal;
        num = (int)aux; // parte inteira

        if(num > 9) // letra
            valor = (55 + num); // converte
        else // valor normal do numero
            valor = num+'0';

        ret[i] = valor; // guarda valor

        fracionaria = aux - num; // parte fracionaria do resultado
        i = i + 1;
    }
}

void converterParaBase(float numero, unsigned int baseFinal, char *numeroPronto)
{
    char parteInteira[100];
    char parteFracao[100];
    converterInteira(numero, baseFinal, parteInteira);
    strcat(numeroPronto, parteInteira);
    if(numero - (int)numero != 0.0) // se tiver parte fracionaria
    {
        converterFracao(numero, baseFinal, parteFracao);
        strcat(numeroPronto, ",");
        strcat(numeroPronto, parteFracao);
    }
}
//---------------------------------------------------------------------------//
//                              PROGRAMA - MAIN
//---------------------------------------------------------------------------//

int main()
{
    char numero[100], neg = ' ';
    char* numeroConvertido[100];
    int i;
    unsigned int baseInicial;
    unsigned int baseFinal;
    unsigned int tamanho = 0;
    float numeroEmDecimal;

    printf("-=-=-=-=-=-=-=-=-=-PROJETO CONVERSOR DE BASES-=-=-=-=-=-=-=-=-=-\n");
    printf("Giovanna, Maria Luiza e Vinicius - PD19\n\n");
    fflush(stdout);

        do {
            printf("\nDigite o numero a ser convertido: ");
            fflush(stdout);
            scanf("%s",numero);
            fflush(stdin);

            printf("Digite a base do numero inserido: ");
            fflush(stdout);
            scanf("%u", &baseInicial);
            fflush(stdin);

            printf("Digite a nova base para a qual converteremos o numero: ");
            fflush(stdout);
            scanf("%u", &baseFinal);
            fflush(stdin);

            tamanho = strlen(numero);

            if(numero[0] == '-')
            {
                for(i=0; i<tamanho; i++)
                    numero[i] = numero[i+1];

                neg = '-';
                tamanho = strlen(numero);
            }
        }
        while(verificar(numero, tamanho, baseInicial, baseFinal) != 0);

        numeroEmDecimal = converterParaDec(numero, strlen(numero), baseInicial);
        converterParaBase(numeroEmDecimal, baseFinal, numeroConvertido);
        printf("\n    O numero convertido vale: %c%s\n\n", neg, &numeroConvertido);
	fflush(stdout);

    return 0;
}
