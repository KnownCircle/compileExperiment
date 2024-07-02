// test function strdup()
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char str[] = "Hello World";
    char *dup = strdup(str);
    printf("Original string: %s\n", str);
    printf("Duplicated string: %s\n", dup);
    printf("%p\n", str);
    printf("%p\n", dup);
    free(dup);
    return 0;
}