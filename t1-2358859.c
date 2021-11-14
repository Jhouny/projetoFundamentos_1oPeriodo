/*============================================================================*/
/* CSF13 - 2021-2 - TRABALHO 1                                     14/11/2021 */
/*----------------------------------------------------------------------------*/
/* Jhony Minetto Araújo - jhonyminettoaraujo@alunos.utfpr.edu.br              */
/*============================================================================*/

#include "trabalho1.h"
#include<math.h>

/*============================================================================*/

unsigned int fourcc (char c1, char c2, char c3, char c4) {
    /*
    A função usa o operador bit a bit Left Shift para multiplicar o número
    hexadecimal por (int) 256 ou 0x100 ('c << 8'). Isso faz com que seu valor
    seja 'colocado' na n-ésima posição, possibilitando que os numeros sejam
    'concatenados' na ordem escolhida
    */
    int numFinal = c1 + (c2<<8) + (c3<<16) + (c4<<24);
    return numFinal;
}

/*============================================================================*/

int calculaInterseccao (int n_retangulos) {
    int cantoSE_x = pegaXSE(0), cantoSE_y = pegaYSE(0), cantoID_x = pegaXID(0), cantoID_y = pegaYID(0), i;  //Pega as coordenadas do 1o retângulo e define como a interseção
    int x_tempSE, y_tempSE, x_tempID, y_tempID;  //Variaveis temporarias para manejar as coordenadas dos retangulos
    int areaTotal;

    for(i = 1; i < n_retangulos; i++) {
        //Atualiza as coordenadas para o retangulo atual
        x_tempSE = pegaXSE(i);
        y_tempSE = pegaYSE(i);
        x_tempID = pegaXID(i);
        y_tempID = pegaYID(i);

        if (x_tempSE > cantoID_x || y_tempSE < cantoID_y || x_tempID < cantoSE_x || y_tempID > cantoSE_y)
            return 0;  //Se não houver interseção, encerra o programa

        if (x_tempSE > cantoSE_x)  //Se as coordenadas do canto SE estiverem dentro da interseção, atualiza suas coordenadas
            cantoSE_x = x_tempSE;
        if (y_tempSE < cantoSE_y)
            cantoSE_y = y_tempSE;

        if (x_tempID < cantoID_x)  //Se as coordenadas do canto ID estiverem dentro da interseção, atualiza suas coordenadas
            cantoID_x = x_tempID;
        if (y_tempID > cantoID_y)
            cantoID_y = y_tempID;

    }

    areaTotal = (cantoID_x - cantoSE_x)*(cantoID_y - cantoSE_y);  //Calcula a área

    return fabs(areaTotal);
}

/*============================================================================*/

double raizAproximada (double x, double erro_minimo) {
    double numeroAtual = 1, limMinimo = 0, limMaximo = x;  //Variaveis para manejar os limites, inferior e superior, e o 'chute' atual
    double erroAtual = fabs(numeroAtual*numeroAtual - x);

    //Se o número for menor que 1, o limMaximo deve ser maior que o próprio numero...
    if(x < 1)
        limMaximo = 1;


    //Aplica modificações para otimizar o tempo de execução
    if (x >= 4)
        limMaximo /= 2.0; //Seguindo os graficos de f(x) = x^0.5 e g(x) = x/2, f é sempre menor que g após x=4


    while (erroAtual > erro_minimo) {
        numeroAtual = (limMaximo+limMinimo)/2.0;  //Define o número como a média entre o max e min
        erroAtual = fabs(numeroAtual*numeroAtual - x);
        //Retorna o valor absoluto - função 'fabs' - da diferença dos quadrados - caso contrario o programa pararia mesmo quando o erro fosse grande, porém negativo

        if (numeroAtual*numeroAtual > x) //Define o limite superior ou inferior
            limMaximo = numeroAtual;
        else
            limMinimo = numeroAtual;
    }

    return numeroAtual;
}

/*============================================================================*/

int codigoValido(unsigned int n, int tamanho) {
    /* Esse método de avaliação de codigo valido se baseia na sequência de Catalan.

       A referência para a origem da solução se encontra no URL abaixo:
        https://www.researchgate.net/publication/45904772_Coding_objects_related_to_Catalan_numbers
    */

    int i, num;
    int validStart_sum = 0;  //Seguindo os requisitos de codificação na 3a pagina (33), a sequencia deve ter quantidades iguais de 00 e 11, e começar com 00 (caso a tenha)

    if(n == 0 && tamanho == 1)
        return 1;

    int pos0 = n&(1<<(tamanho-1));  //Variáveis para separar as sequências binárias iterativamente - 00101 -> (001 e 0), (0 e 010), etc.
    int pos1 = n&(1<<(tamanho-2));  //Inicia a lógica do programa 'tirando' os zeros iniciais

    tamanho -= 2;

    if(pos0 == 0 && pos1 == 0) {
        if(n&1) {
            n >>= 1;
            tamanho--;

            for(i = tamanho-2; i >= 0; i -= 2) {
                num = n&(3<<i);  //Operação AND para checar se tem a sub-sequência 11 na posição i
                num >>= i;

                if(num == 0) {
                    validStart_sum++;  //Se a posição for 00, some ao total
                }
                else if(num == 3) {
                    validStart_sum--;  //Se for 11, subtraia
                }

                //Caso a soma chegue a ficar negativa, em qualquer ponto da sequência, retorna 0, pois significa que começou com 11
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
