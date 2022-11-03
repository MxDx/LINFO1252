#include <stdio.h>

// Before: a contains the address of x ; b contains the address of y
void exchange_pointers(int** a, int** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}
// After: b contains the address of x ; a contains the address of y

int main() {
    int x = 3;
    int y = 4;

    int * a = &x ;
    int * b = &y ;
    printf("Before: a contains the address of x ; b contains the address of y \n");
    printf("a = %p ; b = %p \n", a, b);
    exchange_pointers(&a, &b);
    printf("After: b contains the address of x ; a contains the address of y \n");
    printf("a = %p ; b = %p \n", a, b);
}