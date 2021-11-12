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
    int i, has0011sum = 0, num;
    int pos0 = n&(1<<(tamanho-1));
    int pos1 = n&(1<<(tamanho-2));
    tamanho -= 2;
    if(pos0 == 0 && pos1 == 0) {
        if(n&1) {
            n >>= 1;
            tamanho--;
            for(i = tamanho-2; i >= 0; i -= 2) {
                num = n&(3<<i);
                num >>= i;
                if(num == 0) {
                    has0011sum++;
                }
                else if(num == 3) {
                    has0011sum--;
                }
                if(has0011sum < 0)
                    return 0;
            }
            if(has0011sum == 0)
                return 1;
        }
    }
    return 0;
}

