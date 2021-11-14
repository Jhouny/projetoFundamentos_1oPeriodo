/*============================================================================*/
/* CSF13 - 2021-2 - TRABALHO 1                                     14/11/2021 */
/*----------------------------------------------------------------------------*/
/* Jhony Minetto Ara�jo - jhonyminettoaraujo@alunos.utfpr.edu.br              */
/*============================================================================*/

#include "trabalho1.h"
#include<math.h>

/*============================================================================*/

unsigned int fourcc (char c1, char c2, char c3, char c4) {
    /*
    A fun��o usa o operador bit a bit Left Shift para multiplicar o n�mero
    hexadecimal por (int) 256 ou 0x100 ('c << 8'). Isso faz com que seu valor
    seja 'colocado' na n-�sima posi��o, possibilitando que os numeros sejam
    'concatenados' na ordem escolhida
    */
    int numFinal = c1 + (c2<<8) + (c3<<16) + (c4<<24);
    return numFinal;
}

/*============================================================================*/

int calculaInterseccao (int n_retangulos) {
    int cantoSE_x = pegaXSE(0), cantoSE_y = pegaYSE(0), cantoID_x = pegaXID(0), cantoID_y = pegaYID(0), i;  //Pega as coordenadas do 1o ret�ngulo e define como a interse��o
    int x_tempSE, y_tempSE, x_tempID, y_tempID;  //Variaveis temporarias para manejar as coordenadas dos retangulos
    int areaTotal;

    for(i = 1; i < n_retangulos; i++) {
        //Atualiza as coordenadas para o retangulo atual
        x_tempSE = pegaXSE(i);
        y_tempSE = pegaYSE(i);
        x_tempID = pegaXID(i);
        y_tempID = pegaYID(i);

        if (x_tempSE > cantoID_x || y_tempSE < cantoID_y || x_tempID < cantoSE_x || y_tempID > cantoSE_y)
            return 0;  //Se n�o houver interse��o, encerra o programa

        if (x_tempSE > cantoSE_x)  //Se as coordenadas do canto SE estiverem dentro da interse��o, atualiza suas coordenadas
            cantoSE_x = x_tempSE;
        if (y_tempSE < cantoSE_y)
            cantoSE_y = y_tempSE;

        if (x_tempID < cantoID_x)  //Se as coordenadas do canto ID estiverem dentro da interse��o, atualiza suas coordenadas
            cantoID_x = x_tempID;
        if (y_tempID > cantoID_y)
            cantoID_y = y_tempID;

    }

    areaTotal = (cantoID_x - cantoSE_x)*(cantoID_y - cantoSE_y);  //Calcula a �rea

    return fabs(areaTotal);
}

/*============================================================================*/

double raizAproximada (double x, double erro_minimo) {
    double numeroAtual = 1, limMinimo = 0, limMaximo = x;  //Variaveis para manejar os limites, inferior e superior, e o 'chute' atual
    double erroAtual = fabs(numeroAtual*numeroAtual - x);

    //Se o n�mero for menor que 1, o limMaximo deve ser maior que o pr�prio numero...
    if(x < 1)
        limMaximo = 1;


    //Aplica modifica��es para otimizar o tempo de execu��o
    if (x >= 4)
        limMaximo /= 2.0; //Seguindo os graficos de f(x) = x^0.5 e g(x) = x/2, f � sempre menor que g ap�s x=4


    while (erroAtual > erro_minimo) {
        numeroAtual = (limMaximo+limMinimo)/2.0;  //Define o n�mero como a m�dia entre o max e min
        erroAtual = fabs(numeroAtual*numeroAtual - x);
        //Retorna o valor absoluto - fun��o 'fabs' - da diferen�a dos quadrados - caso contrario o programa pararia mesmo quando o erro fosse grande, por�m negativo

        if (numeroAtual*numeroAtual > x) //Define o limite superior ou inferior
            limMaximo = numeroAtual;
        else
            limMinimo = numeroAtual;
    }

    return numeroAtual;
}

/*============================================================================*/

int codigoValido(unsigned int n, int tamanho) {
    /* Esse m�todo de avalia��o de codigo valido se baseia na sequ�ncia de Catalan.

       A refer�ncia para a origem da solu��o se encontra no URL abaixo:
        https://www.researchgate.net/publication/45904772_Coding_objects_related_to_Catalan_numbers
    */

    int i, num;
    int validStart_sum = 0;  //Seguindo os requisitos de codifica��o na 3a pagina (33), a sequencia deve ter quantidades iguais de 00 e 11, e come�ar com 00 (caso a tenha)

    if(n == 0 && tamanho == 1)
        return 1;

    int pos0 = n&(1<<(tamanho-1));  //Vari�veis para separar as sequ�ncias bin�rias iterativamente - 00101 -> (001 e 0), (0 e 010), etc.
    int pos1 = n&(1<<(tamanho-2));  //Inicia a l�gica do programa 'tirando' os zeros iniciais

    tamanho -= 2;

    if(pos0 == 0 && pos1 == 0) {
        if(n&1) {
            n >>= 1;
            tamanho--;

            for(i = tamanho-2; i >= 0; i -= 2) {
                num = n&(3<<i);  //Opera��o AND para checar se tem a sub-sequ�ncia 11 na posi��o i
                num >>= i;

                if(num == 0) {
                    validStart_sum++;  //Se a posi��o for 00, some ao total
                }
                else if(num == 3) {
                    validStart_sum--;  //Se for 11, subtraia
                }

                //Caso a soma chegue a ficar negativa, em qualquer ponto da sequ�ncia, retorna 0, pois significa que come�ou com 11
                if(validStart_sum < 0)
                    return 0;
            }

            //Como o total de 00s e 11s deve ser igual, a soma deve ser 0
            if(validStart_sum == 0)
                return 1;
        }
    }
    return 0;
}

/*============================================================================*/
