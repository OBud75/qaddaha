#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int A = 12;
    int *a = &A;

    printf("%d\n", A);
    printf("%p\n", &A);
    printf("%d\n", *a);
    printf("%p\n", &a);
    printf("%p\n", a);

    return 0;
}