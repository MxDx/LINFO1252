#include <stdlib.h>

int fold(int *arr, size_t len, int acc, int (*f)(int, int)) {
    for (size_t i = 0; i < len; i++)
    {
        acc = f(acc, arr[i]);
    }

    return acc;
}

int *map(int *arr, size_t len, int (*f)(int)) {
    int *new = (int *)malloc(len * sizeof(int));
    
    for (size_t i = 0; i < len; i++)
    {
        new[i] = f(arr[i]);
    }

    return new;
}