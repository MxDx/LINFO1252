#include <stdio.h>
#include <stdlib.h>

char MY_HEAP[64000];

void init() {
    MY_HEAP[0] = '1';
    MY_HEAP[1] = 0b11111001;
    MY_HEAP[2] = 0b11111101;
}


void *my_malloc(size_t size) {
    int i = 0;
    unsigned int taille;
    while(i < 64000){
        // on récupère la taille de l'espace mémoire
        taille = (unsigned char)MY_HEAP[i+1];
        taille = taille << 8;
        taille = taille | (unsigned char)MY_HEAP[i+2];
  
        if (MY_HEAP[i] == '2'){
            // espace mémoire complet (flag 2) -> on skip l'espace
            i += taille + 3;
        }else{
            // espace mémoire vide
            if (taille < size){
                //espace mémoire insuffisant
                i += taille + 3;
            }else{
                //espace mémoire suffisant
                MY_HEAP[i] = '2';
                MY_HEAP[i+1] = size >> 8;
                MY_HEAP[i+2] = size & 0b11111111;
                if (taille > size+3){
                    // si il reste assez d'espace vide après l'allocation
                    int j = i + size + 3;
                    unsigned int freesize = taille - (size+3);
                    MY_HEAP[j] = '1';
                    MY_HEAP[j+1] = freesize >> 8;
                    MY_HEAP[j+2] = freesize & 0b11111111;
                }
                char* solptr = &MY_HEAP[i+3];
                return solptr;
            }
        }
    }
    return NULL;
}

void my_free(void* pointer) {
    char* flag = pointer -3;
    *flag = '1';
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