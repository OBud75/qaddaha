#include <string.h> // Pour memcpy
#include <stddef.h> // Pour size_t

typedef struct Person {
    int age;
} Person;

int are_persons_equals(Person *p1, Person *p2) {
    return p1->age == p2->age;
}

typedef struct Book {
    int pages;
} Book;

int are_books_equals(Book *b1, Book *b2) {
    return b1->pages == b2->pages;
}

int are_equals(void *obj1, void *obj2, int (*compare_fnc)(void *, void *)) {
    return compare_fnc(obj1, obj2);
}

int are_persons_greater(Person *p1, Person *p2) {
    return p1->age > p2->age;
}

int are_books_greater(Book *b1, Book *b2) {
    return b1->pages > b2->pages;
}

void swap(void *obj1, void *obj2, size_t size) {
    char temp[size];
    memcpy(temp, obj1, size);
    memcpy(obj1, obj2, size);
    memcpy(obj2, temp, size);
}


void sort(void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *), void (*swap_fnc)(void *, void *, size_t)) {
    char *arr = (char *)array;
    for (int i = 0; i < nb_of_elems_in_array - 1; i++) {
        for (int j = 0; j < nb_of_elems_in_array - i - 1; j++) {
            if (compare_fnc(arr + j * elem_size, arr + (j + 1) * elem_size)) {
                swap_fnc(arr + j * elem_size, arr + (j + 1) * elem_size, elem_size);
            }
        }
    }
}

int is_in_array(void *obj_to_find, void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *)) {
    char *arr = (char *)array;
    for (int i = 0; i < nb_of_elems_in_array; i++) {
        if (compare_fnc(obj_to_find, arr + i * elem_size)) {
            return 1;
        }
    }
    return 0;
}
