#include <stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int total_jiao = a * 10 + b;
    int pens = total_jiao / 19;
    printf("%d\n", pens);
    return 0;
}