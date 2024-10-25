#include <stdio.h>

int main(int argc, char const *argv[])
{
    int number_1, number_2;
    scanf("%d %d", &number_1, &number_2);

    number_1 > number_2 ? printf("%d > %d\n", number_1, number_2 ) : printf("%d > %d\n", number_2, number_1 );

    return 0;
}
