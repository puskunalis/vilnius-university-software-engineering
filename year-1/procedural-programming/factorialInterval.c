#include <stdio.h>

int main()
{
    int a, b, faktorialas = 1;
    printf("Iveskite faktorialu intervala [a, b]:\n");
    scanf("%d%d", &a, &b);

    for (int i = 1; (faktorialas *= i) <= b; ++i)
    {
        if (a <= faktorialas)
        {
            printf("%d\n", faktorialas);
        }
    }

    return 0;
}
