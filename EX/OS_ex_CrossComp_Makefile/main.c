#include <stdio.h>
#include "function.h"
#define N 5
int main() {
   int a= N-3;
    int  b= N+2;

    int result = add(a, b);
    printf("The result of adding %d and %d is: %d\n", a, b, result);
    return 0;
}
