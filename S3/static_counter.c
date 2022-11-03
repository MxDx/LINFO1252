#include <stdlib.h>
#include <stdio.h>

unsigned int stexp() {
    static int exp = 0;
    if (exp == 0 || exp == 4096) {
        exp = 1;
    } else {
        exp *= 2;
    }
    return exp;
}

int main() {
    printf("%d \n", stexp());
    printf("%d \n", stexp());
    printf("%d \n", stexp());
}