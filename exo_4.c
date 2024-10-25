#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int monster_1;
    int monster_2;
    srand(time(NULL));
    // Génère un nombre aléatoire :
    int random_number = rand()%10;
    int random_power = rand()%6;
    int random_luck = rand()%64;
    
    (random_number > 5) ? 
    monster_1 == random_power :
    (monster_2 == random_power);

    (random_luck > random_luck + random_number) ?
    monster_1 -= random_number :
    (monster_2 -= random_number);

    (monster_1 > monster_2) ?
    printf("monster 1 win\n") :
    printf("monster 2 win\n");
    
    return 0;
}