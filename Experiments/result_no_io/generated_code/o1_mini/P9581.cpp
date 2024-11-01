#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int step1 = abs(a) + abs(b - a);
    int step2 = abs(b) + abs(a - b);
    int result = step1 < step2 ? step1 : step2;
    printf("%d\n", result);
    return 0;
}