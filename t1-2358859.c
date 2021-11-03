#include "trabalho1.h"
#include<math.h>

unsigned int fourcc (char c1, char c2, char c3, char c4) {
    /*
    A fun��o usa o operador bit a bit Left Shift para multiplicar o n�mero
    hexadecimal por (int) 256 ou 0x100 (para <<8). Isso faz com que seu valor
    seja 'colocado' na n-�sima posi��o, possibilitando que os numeros sejam
    'concatenados' na ordem escolhida
    */
    int numFinal = c1 + (c2<<8) + (c3<<16) + (c4<<24);
    return numFinal;
}


int calculaInterseccao (int n_retangulos) {
    int cantoSE_x = pegaXSE(0), cantoSE_y = pegaYSE(0), cantoID_x = pegaXID(0), cantoID_y = pegaYID(0), i;  //Pega as coordenadas do 1o ret�ngulo e define como a interse��o
    int x_tempSE, y_tempSE, x_tempID, y_tempID;
    int areaTotal;

    for(i = 1; i < n_retangulos; i++) {
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

    areaTotal = (cantoID_x - cantoSE_x)*(cantoID_y - cantoSE_y);

    return fabs(areaTotal);
}


double raizAproximada (double x, double erro_minimo) {
    /*
    Essa fun��o usa o m�todo de Newton para aproximar o valor de uma express�o.
    O m�todo afirma que 'x2 = x1 - f(x1)/f'(x1)', onde x1 � um n�mero qualquer
    e x2 � um numero mais proximo da solu��o do sistema.

    A raiz de um n�mero pode ser expressa como 'x = raiz(n)' --> 'x*x = n', logo
    pode ser considerada como a solu��o do sistema 'x*x - n = 0' (onde n � o
    n�mero de que se quer achar a raiz), usamos esse m�todo para aproximar sua solu��o.


    double numeroAtual = 1;  //x1
    double erroAtual = x*x-numeroAtual*numeroAtual; */

    double numeroAtual = 1, limMinimo = 0, limMaximo = x;
    double erroAtual = x*x-numeroAtual*numeroAtual;

    //Aplica modifica��es para otimizar o tempo de execu��o
    if (x >= 4)
        limMaximo /= 2; //Seguindo os graficos de f(x) = x^0.5 e g(x) = x/2, f � sempre menor que g ap�s x=4


    while (erroAtual > erro_minimo) {
        numeroAtual = (limMaximo+limMinimo)/2.0;  //Pega a m�dia entre o max e min
        erroAtual = fabs(numeroAtual*numeroAtual - x);
        //Retorna o valor positivo da diferen�a dos quadrados - caso contrario o programa pararia mesmo quando o erro fosse grande

        if (numeroAtual*numeroAtual > x) //Define o limite superior ou inferior
            limMaximo = numeroAtual;
        else
            limMinimo = numeroAtual;
    }

    return numeroAtual;
}

