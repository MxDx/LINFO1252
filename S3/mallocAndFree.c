#include <stdio.h>
#include <stdlib.h>

char MY_HEAP[64000];

void init() {
    MY_HEAP[0] = 0;
    MY_HEAP[1] = 0b11111001;
    MY_HEAP[2] = 0b11111101;
}

void *my_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    int i = 0;
    while (i < 64000) {
        int space_in_front = ((unsigned char)MY_HEAP[i + 1]) * 256 + ((unsigned char)MY_HEAP[i + 2]);
        if (MY_HEAP[i] == 0) {
            if (space_in_front >= size + 3) {
                space_in_front = space_in_front - (size+3);

                MY_HEAP[i] = 1;
                MY_HEAP[i + 1] = size >> 8;
                MY_HEAP[i + 2] = size & 0x00FF;

                if (space_in_front > 0) {
                    MY_HEAP[i + 3 + size] = 0;
                    MY_HEAP[i + 4 + size] = space_in_front >> 8;
                    MY_HEAP[i + 5 + size] = space_in_front & 0x00FF;
                }

                return MY_HEAP + i + 3;
            }
            i += space_in_front + 3;
        } else {
            i += space_in_front + 3;
        }
    }
    return NULL;
}

void my_free(void *pointer) {
    if (pointer == NULL) {
        return;
    }
    void* START_HEAP = MY_HEAP;
    void* END_HEAP = MY_HEAP + 64000;
    if (pointer < START_HEAP || pointer > END_HEAP) {
        return;
    }
    int i = pointer-3-START_HEAP;
    int space_in_front = ((unsigned char)MY_HEAP[i + 1]) * 256 + ((unsigned char)MY_HEAP[i + 2]);

    MY_HEAP[i] = 0;
    if (MY_HEAP[i + space_in_front + 3] == 0) {
        int tmp1 = i + space_in_front + 4;
        int tmp2 = i + space_in_front + 5;
        space_in_front += ((unsigned char)MY_HEAP[i + space_in_front + 4]) * 256 + ((unsigned char)MY_HEAP[i + space_in_front + 5]) + 3;
        MY_HEAP[i + 1] = (space_in_front & 0xFF00) >> 8;
        MY_HEAP[i + 2] = space_in_front & 0x00FF;
        MY_HEAP[tmp1] = 0;
        MY_HEAP[tmp2] = 0;
    }
    return;
}

// 2**16 = 65536
// 10 to binary = 00001010
// 256 to binary = 00000001 00000000 
// 0xFF00 = 11111111 00000000
// 10000000 00000000 = 32768
// 00000000 10000000 = 128
// 128*256 = 32768
// 63997 = 11111111 11111101
// -128*256 = -32768


int main() {
    init();

    printf("MY_HEAP 0 = %d \n", MY_HEAP[0]);
    printf("MY_HEAP 1 = %d \n", (unsigned char) MY_HEAP[1]);
    printf("MY_HEAP 2 = %d \n", (unsigned char) MY_HEAP[2]);

    int *a = my_malloc(sizeof(int));
    if (a == NULL) {
        printf("a is NULL \n");
    } else {
        printf("a is not NULL \n");
    }
    *a = 5;
    printf("a = %d \n \n", *(a));

    printf("MY_HEAP 0 = %d \n", MY_HEAP[0]);
    printf("MY_HEAP 1 = %d \n", (unsigned char) MY_HEAP[1]);
    printf("MY_HEAP 2 = %d \n", (unsigned char) MY_HEAP[2]);
    printf("MY_HEAP 3 (Value) = %d \n", MY_HEAP[3]);
    printf("\n");
    printf("MY_HEAP 7 = %d \n", MY_HEAP[7]);
    printf("MY_HEAP 8 = %d \n", (unsigned char) MY_HEAP[8]);
    printf("MY_HEAP 9 = %d \n", (unsigned char) MY_HEAP[9]);
    printf("\n");

    my_free(a);
    printf("MY_HEAP 0 = %d \n", MY_HEAP[0]);
    printf("MY_HEAP 1 = %d \n", (unsigned char) MY_HEAP[1]);
    printf("MY_HEAP 2 = %d \n", (unsigned char) MY_HEAP[2]);

    // test my_malloc
    int *b = my_malloc(sizeof(int));
    if (b == NULL) {
        printf("b is NULL \n");
    } else {
        printf("b is not NULL \n");
    }
    *b = 5;
    printf("b = %d \n \n", *(b));

    int *c = my_malloc(sizeof(int));
    if (c == NULL) {
        printf("c is NULL \n");
    } else {
        printf("c is not NULL \n");
    }
    *c = 128;
    printf("c = %d \n \n", *(c));

    int *d = my_malloc(4);
    if (d == NULL) {
        printf("d is NULL \n");
    } else {
        printf("d is not NULL \n");
    }

    for (int i = 0; i <= 20; i++) {
        printf("MY_HEAP %d = %d \n", i, (unsigned char) MY_HEAP[i]);
    }
    printf("\n");

    my_free(c);
    // print my heap until 20
    for (int i = 0; i <= 20; i++) {
        printf("MY_HEAP %d = %d \n", i, (unsigned char) MY_HEAP[i]);
    }


}