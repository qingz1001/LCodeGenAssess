#include <stdio.h>

int main(){
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int start = a * 60 + b;
    int end = c * 60 + d;
    int diff = end - start;
    int e = diff / 60;
    int f = diff % 60;
    printf("%d %d", e, f);
    return 0;
}