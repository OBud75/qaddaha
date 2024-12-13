#include <stdio.h>

int manin(ont argc, char const *argv[])
{
    int birthdate;
    printf("Enter your birthdate: ");
    scanf("%i", &birthdate);
    printf("You were born in %i\n", birthdate);
    int age = 2021 - birthdate;
    printf("You are %i years old\n", age);

    char name[20];
    char favoriteColor[20];
    printf("enter your name and favorite color: ");
    fgets("%s %s", name, favoriteColor);
    return 0;
}