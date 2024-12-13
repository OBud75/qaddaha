#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *Buffer;
    Buffer = malloc(sizeof(int));   

    printf("Buffer %ls\n", Buffer);
    printf("&Buffer %p\n", &Buffer);
    printf("*Buffer %d\n", *Buffer);

    *Buffer = 4;
    printf("Buffer %ls\n", Buffer);
    printf("&Buffer %p\n", &Buffer);
    printf("*Buffer %d\n", *Buffer);
    
    return 0;
}