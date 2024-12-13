#include <stdio.h>
#include <exercice.h>
#include <stdlib.h>


void linear_search(){

}

int main(int argc, char *argv[]) {
    // Début du programme
    Person person1 = {50};
    Person person2 = {50};

    int same_age = are_equals(
        &person1.age, &person2.age, (int(*)(void*, void*)) are_persons_equals
    );
    if (same_age) {
        printf("same age");
    } 

    // Person people[] = {20}, {10}};
    Person people[] = {{20}, {50}};
    int founs = is_in_array(
        &person1,
        &person2,
        sizeof(people) / sizeof(Person),
        (int(*)(void*, void*)) are_persons_equals
    );
    if (found == 1) {
        printf("Person 1 is in the people array");
    }

    
    return 0;
}