#include<stdio.h>

int bitCount(int num) {
    int count = 0;
    while(num != 0) {
        num = num&(num-1);
        count++;
    }
    return count;
}

int highestPowerof2(int n)
{
    int res = 0;
    for (int i=n; i>=1; i--)
    {
        // If i is a power of 2
        if ((i & (i-1)) == 0)
        {
            res = i;
            break;
        }
    }
    return res;
}

int codigoValido(unsigned int n, int tamanho) {
    int flag_val = 0, num1, num2;
    if(n&1 && n>>(tamanho-2) == 0 && bitCount(n) == tamanho/2) {
        flag_val = 1;
    }
    if(flag_val)
        return 1;
    else
        return 0;
}
