#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    srand(time(NULL)); 
    int number_to_guess = rand()%6;
    int number;
    int life =10;
    
    while (life != 0)
    {
        printf("saisir un nombre entre 0 et 6 \n");
        scanf("%d", &number);
        (number > number_to_guess) ? 
        printf("trop grand\n") , life -= 1 : 
        (number > number_to_guess) ?
        (printf("trop petit\n") , life -= 1) :
        (printf("bravo vous avez le bon nombre\n"), life = 0);
    }
    
    return 0;
}
