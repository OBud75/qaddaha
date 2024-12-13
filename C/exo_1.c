#include <stdio.h>

int main (){
    int number_1, number_2;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &number_1, &number_2);

    number_1 > number_2 ? printf("le nombre %d est plus grand\n", number_1) : printf("le nombre %d est plus grand\n", number_2);

    return 0;
}