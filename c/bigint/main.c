#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //char *bi1 = "12345";
    //char *bi2 = "6789";
    char *bi1 = argv[1];
    char *bi2 = argv[2];

    int l1 = strlen(bi1);
    int l2 = strlen(bi2);

    int l = l1 >= l2 ? l1 : l2;
    int s = l1 < l2 ? l1 : l2;
    char *lbi = l1 >= l2 ? bi1 : bi2;
    char *sbi = l1 < l2 ? bi1 : bi2;

    // for trailing '\0', and extra leading '0'.
    char result[l + 2];
    result[0] = '0';
    result[l + 1] = '\0';

    int saved_carrier = 0;
    int k = l;
    for (int i = l - 1, j = s - 1; i >= 0 || j >= 0; i--, j--, k--)
    {
        int i1 = lbi[i] - '0';
        int i2 = 0;
        if (j >= 0)
        {

            i2 = sbi[j] - '0';
        }
        int sum = i1 + i2 + saved_carrier;
        int carrier = 0;
        if (sum >= 10)
        {
            sum %= 10;
            carrier = 1;
        }
        printf("%d + %d + %d = %d, carrier %d\n", i1, i2, saved_carrier, sum, carrier);
        saved_carrier = carrier;
        result[k] = '0' + sum;
    }
    result[k] = saved_carrier + '0';

    if (result[0] == '0')
    {
        printf("%s + %s = %s\n", bi1, bi2, result + 1);
    }
    else
    {
        printf("%s + %s = %s\n", bi1, bi2, result);
    }

    return 0;
}