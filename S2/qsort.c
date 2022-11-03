#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// il vous est demandé de coder une fonction de comparaison compare mettant en œuvre 
// le tri alphabétique de caractères ASCII, non sensible à la casse (e.g. "laura < Laure", "Rob" < "robert")
// int compare(const void* a, const void* b) { 
    // char* a1 = (char*)a;
    // char* b1 = (char*)b; 
    // int ai = (int)*a1;
    // int bi = (int)*b1;
  
    // while (*a1 != '\0' && *b1 != '\0') {
    //     if (ai >= 65 && ai <= 90) ai += 32; // si majuscule, on la met en minuscule        
    //     if (bi >= 65 && bi <= 90) bi += 32; 

    //     if (ai - bi != 0) {
    //         return ai - bi;
    //     }
        
    //     a1++;
    //     b1++;
    //     ai = (int)*a1;
    //     bi = (int)*b1;
        
    // }
    // if (*a1 == '\0' && *b1 == '\0') {
    //     return 0;
    // } else if (*a1 == '\0') {
    //     return -1;
    // } else {
    //     return 1;
    // }
// }

int compare(const void *a, const void *b)  {
    char **first = (char **)a;
    char **second = (char **)b;
   
    int i = 0;
    
    if (tolower(**first) == tolower(**second)){
        return 0;
    }
    
    while (**(first+i) != '\0' || **(second+i) != '\0')
    {
        if (tolower(**(first+i)) - tolower(**(second+i)) != 0)
        {
            return tolower(**(first+i)) - tolower(**(second+i));
        }

        i++;
    }
    if ( **(first+i)=='\0'&&**(second+i)=='\0' ){
        return 0;
    } else{
        if (**(first+i)!='\0'){
            return -1;
        }else{
            return 1;
        }
    }  
}
   


void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    if (base == NULL)
    {
        printf("Erreur");
        return;
    }
    
    if (base+nel*width == NULL)
    {
        printf("Erreur");
        return;
    }

    if (nel<=0)
    {
        printf("Erreur");
        return;
    }
    if (width <= 0)
    {
        printf("Erreur");
        return;
    }
    
    if (compar == NULL)
    {
        printf("Erreur");
        return;
    }
    for (int i = 0; i < nel; ++i) {
        for (int j = 0; j < nel - 1; ++j) {
            if (compar(base + j * width, base + (j + 1) * width) >= 0) {

                char tmp[width];
                memcpy(tmp,base + width*j,width);
                memcpy(base + width*j,base+ width * (j+1), width);
                memcpy(base + width * (j+1),tmp, width);
            }
        }
    }
}


int main() {
    char* a = "Rob";
    char* b = "robert";
    printf("%d \n", compare(a, b));

    char** names = malloc(2 * sizeof(char*));
    names[0] = b;
    names[1] = a;
    printf("%s %s \n", names[0], names[1]);
    sort(names, 2, sizeof(char*), &compare);
    printf("%s %s \n", names[0], names[1]);
}
