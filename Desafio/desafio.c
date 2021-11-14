#include<stdio.h>

int bitCount(int n, int length) {
    int ones = 0, i, num = n;

    for(i=0; i < length; i++)
    {
        if(num & 1)
            ones++;

        num >>= 1;
    }

    return ones;
}

int codigoValido(unsigned int n, int tamanho) {
    /* Esse método de avaliação de codigo valido se baseia na sequência de Catalan.

       A referência para a origem da solução se encontra no link abaixo:
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
                num = n&(3<<i);
                num >>= i;
                if(num == 0) {
                    validStart_sum++;
                }
                else if(num == 3) {
                    validStart_sum--;
                }
                if(validStart_sum < 0)
                    return 0;
            }
            if(validStart_sum == 0)
                return 1;
        }
    }
    return 0;
}

