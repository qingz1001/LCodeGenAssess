#include <stdio.h>

int main(){
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int start = a * 60 + b;
    int end = c * 60 + d;
    int delta = end - start;
    int e = delta / 60;
    int f = delta % 60;
    printf("%d %d\n", e, f);
    return 0;
}